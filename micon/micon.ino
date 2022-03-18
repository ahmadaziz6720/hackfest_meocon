#include <Adafruit_MLX90614.h> //temp sensor
#include <Servo.h>

Servo servo_hs; 
Servo servo_door;
servo_hs.write(0);
servo_door.write(0);

#define relay 2
#define ir_in 4
#define ir_out 7
#define ir_hs 12
#define laser 8

bool idle = true;
bool mask = false;

void setup() {
  servo_hs.attach(3);
  servo_hs.attach(5);

  pinMode(relay, OUTPUT);
  pinMode(ir_in, INPUT);
  pinMode(ir_out, INPUT);
  pinMode(ir_hs, INPUT);
  pinMode(laser, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if(digitalRead(ir_hs)==1){
    digitalWrite(laser, HIGH);
    servo_hs.write(90);
    //baca suhu
    //send data suhu
    
    //read data masker //mask = data masker
    if(mask == true){
      if(digitalRead(ir_in)==HIGH){
        digitalWrite(relay, HIGH);
        servo_door.write(120); //buka pintu

        if(digitalRead(ir_out)==HIGH){
          servo_door.write(0); //tutup pintu
          digitalWrite(relay, LOW); //kunci pintu
        }
      }
    }
    
  }
}
