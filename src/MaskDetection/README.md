## TRAINING
If you want to re-train the model, simply run
```
python train.py
```
It will generate new mask model in ```\maskModel```
Note that it will takes up to 30-40 minutes

## DETECTION
Simply run
```
python maskDetectionOnly.py
```
Make sure there are no restriction to access your camera. You also can change the used camera by change the "0" in `cap = cv2.VideoCapture(0)` to other value.