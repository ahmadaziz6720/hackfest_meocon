from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications import MobileNetV2
from tensorflow.keras.layers import AveragePooling2D, Dropout, Flatten, Input, Dense
from tensorflow.keras.models import Model
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.applications.mobilenet_v2 import preprocess_input
from tensorflow.keras.preprocessing.image import img_to_array, load_img
from tensorflow.keras.utils import to_categorical
from sklearn.preprocessing import LabelBinarizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from imutils import paths
import numpy as np
import os


def preprocessImages(dir, category):
	data = []
	labels = []

	for category in categories:
		path = os.path.join(dir, category)
		for img in os.listdir(path):
			img_path = os.path.join(path, img)
			image = load_img(img_path, target_size=(224, 224))
			image = img_to_array(image)
			image = preprocess_input(image)

			data.append(image)
			labels.append(category)

	labels = LabelBinarizer().fit_transform(labels)
	labels = to_categorical(labels)

	data = np.array(data, dtype="float32")
	labels = np.array(labels)

	return (data, labels)



LEARNINGRATE = 1e-4
EPOCHS = 20
BATCHSIZE = 32

dir = r"datasets"
categories = ["mask", "noMask"]

print("[Loading images...]")
data, labels = preprocessImages(dir, categories)


# split data for train and test
trainX, testX, trainY, testY = train_test_split(data, labels, test_size=0.20, stratify=labels, random_state=42)

# augmentation
aug = ImageDataGenerator(
	rotation_range=20,
	zoom_range=0.15,
	height_shift_range=0.2,
	width_shift_range=0.2,
	shear_range=0.15,
	horizontal_flip=True,
	fill_mode="nearest")

baseModel = MobileNetV2(weights="imagenet", include_top=False, input_tensor=Input(shape=(224, 224, 3)))

# construct the head model
headModel = baseModel.output
headModel = AveragePooling2D(pool_size=(7, 7))(headModel)
headModel = Flatten(name="flatten")(headModel)
headModel = Dense(128, activation="relu")(headModel)
headModel = Dropout(0.5)(headModel)
headModel = Dense(2, activation="softmax")(headModel)

# model to train
model = Model(inputs=baseModel.input, outputs=headModel)

for layer in baseModel.layers:
	layer.trainable = False

# compile model
print("[Compiling model...]")
opt = Adam(lr=LEARNINGRATE, decay=LEARNINGRATE / EPOCHS)
model.compile(loss="binary_crossentropy", optimizer=opt, metrics=["accuracy"])

# train the head of the network
H = model.fit(
	aug.flow(trainX, trainY, batch_size=BATCHSIZE),
	steps_per_epoch=len(trainX) // BATCHSIZE,
	validation_data=(testX, testY),
	validation_steps=len(testX) // BATCHSIZE,
	epochs=EPOCHS)

# make predictions on the testing set
print("[Predicting...")
predIdx = model.predict(testX, batch_size=BATCHSIZE)
predIdx = np.argmax(predIdx, axis=1)

print(classification_report(testY.argmax(axis=1), predIdx, target_names=LabelBinarizer().classes_))

# save trained model
print("[Saving mask detector model...]")
model.save("maskModel\trainedDetection.model", save_format="h5")