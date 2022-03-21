from tensorflow.keras.applications.mobilenet_v2 import preprocess_input
from tensorflow.keras.preprocessing.image import img_to_array
from tensorflow.keras.models import load_model
from time import sleep
import numpy as np
import cv2

import serial
import serial.tools.list_ports
import time
arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1)

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data

def detectMask(frame, faceNet, maskNet):
	# set dimensions
	h, w = frame.shape[:2]
	blob = cv2.dnn.blobFromImage(frame, 1.0, (224, 224), (104.0, 177.0, 123.0))

	faceNet.setInput(blob)
	detections = faceNet.forward()

	faces = []
	points = []
	detects = []

	for i in range(0, detections.shape[2]):
		probability = detections[0, 0, i, 2]

		# filter
		if probability > 0.5:
			box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
			x1, y1, x2, y2 = box.astype("int")
			x1, y1 = max(0, x1), max(0, y1)
			x2, y2 = min(w - 1, x2), min(h - 1, y2)

			# preprocess face
			face = frame[y1:y2, x1:x2]
			face = cv2.cvtColor(face, cv2.COLOR_BGR2RGB)
			face = cv2.resize(face, (224, 224))
			face = img_to_array(face)
			face = preprocess_input(face)

			faces.append(face)
			points.append((x1, y1, x2, y2))

	if len(faces) > 0:
		faces = np.array(faces, dtype="float32")
		detects = maskNet.predict(faces, batch_size=32)

	return (points, detects)


# for display
red = (0, 0, 255)
green = (0, 255, 0)
font = cv2.FONT_HERSHEY_SIMPLEX

# face detector model
ProtoPath = r"faceModel\deploy.prototxt"
WeightsPath = r"faceModel\res10_300x300_ssd_iter_140000.caffemodel"
faceNet = cv2.dnn.readNet(ProtoPath, WeightsPath)

# trained mask detection model
maskNet = load_model("maskModel/trainedDetection.model")


print("----------------------START----------------------")

cap = cv2.VideoCapture(0)
width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

while True:
	ret, frame = cap.read()

	points, detects = detectMask(frame, faceNet, maskNet)

	for (box, pred) in zip(points, detects):
		x1, y1, x2, y2 = box
		mask, noMask = pred

		# set label and probability
		label = "Mask" if mask > noMask else "No Mask"
		label = "{}: {:.2f}%".format(label, max(mask, noMask) * 100)
		color = green if mask > noMask else red

		# display
		cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
		cv2.putText(frame, label, (x1, y1 - 10), font, 0.45, color, 2)

	cv2.imshow("Mask Detection", frame)
	# return True if mask > noMask else False
	temp = "1" if mask > noMask else "0"
	write_read(temp)

	pkg = arduino.readline()
	print(pkg.decode("utf").rstrip('\n'))

	if (cv2.waitKey(1) & 0xFF) == ord("q"):
		break

cap.release()
cv2.destroyAllWindows()