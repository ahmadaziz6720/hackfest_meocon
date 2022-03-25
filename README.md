# APPROKES - HACKFEST 2022

## Table of Contents
* [General Information](#general-information)
* [Technology Used](#technology-used)
* [Requirements](#requirements)
* [Setup](#setup)
* [Authors](#authors)


## GENERAL INFORMATION
Approkes are a set of tools that are installed at the entrance of the building/room to ensure that everyone who will enter the building has followed the health protocol. The protocols checked are wearing a mask, normal body temperature, using hand sanitizer, and the available room capacity. Visitor data will also be integrated to firebase.

This product is a solution proposed by the MeoCon Team in Hackfest 2022 By GDSC with a focus on SDG 3 (Good Health and Well-bein) and SDG 9 (Industry, Innovation, and Infrastructure)

![test](docs/maskDetectionTest.jpeg)
![website](docs/preview%20web.jpg)

## TECHNOLOGY USED
This system is build with
- [Python3](https://www.python.org)
- [Tensorflow](https://www.tensorflow.org/)
- [Firebase](https://firebase.google.com/)
- [Arduino IDE](https://www.arduino.cc/en/software)

## REQUIREMENTS
### Software
The requirements are listed in ```requirement.txt```
To install, run
```
pip install -r requirements.txt
```
### Hardware
Electrical component:
- Arduino nano
- ESP32
- IR sensor (2)
- Temperature sensor
- Relay (Pump and Solenoid lock)
- Ultrasonic sensor

### HOW TO RUN
- First, clone this repository
    ```
    git clone https://github.com/ahmadaziz6720/hackfest_meocon.git
    ```
- Set up the electrical component above, you can find the used pin in ```src/main.ino```
- Upload ```main.ino``` to arduino nano via Arduino IDE
- Change terminal directory to src/MaskDetection, then run
    ```
    python realTimeDetection.py
    ```
    (note: both python and arduino code must have the same COM and baudrate)

If you have limitations with electrical components, you can still try the real time mask detection. Just follow the instructions in ```src\MaskDetection\README.md```


## STATUS
Project is: _on development_

## AUTHORS
This program was made by <b>MeoCon<b>
- [Ahmad Aziz](13220034@std.stei.itb.ac.id)
- [Putri Nurhaliza](13520066@std.stei.itb.ac.id)
