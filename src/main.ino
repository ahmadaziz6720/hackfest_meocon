#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define relay_pump 4
#define relay_lock 6
#define ir_out 5
#define trig 8
#define echo 7
#define ir_hs 12

int masker = 0;
int state = 0;
boolean masuk =false;
int people_in = 0;
int people_out = 0;
int current_people = 0;
int maximumRange = 200;
int minimumRange = 0;
long duration, distance;
unsigned long timer;
float temp = 0;

void setup() {
  pinMode(relay_pump, OUTPUT);
  pinMode(relay_lock, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ir_out, INPUT);
  pinMode(ir_hs, INPUT);
  Serial.begin(9600);
  Serial.setTimeout(1);
  pinMode(13, OUTPUT);
}
void loop() {
  //Serial communication
  while (!Serial.available());
  masker = Serial.readString().toInt();
  if (masker == 1) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  current_people = people_in - people_out;
  Serial.println(String(current_people) + " " + String(1) + " " + String(digitalRead(people_in)) + " " + String(digitalRead(people_out))+ " " + String(3)+ " " + String(8));
  
  //Ultrasonic
  digitalWrite(trig, LOW);delayMicroseconds(2);
  digitalWrite(trig, HIGH);delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration/58.2;
  if(distance<30){
    masuk = true;
  }else{
    masuk =false;
  }

  //Temperature Sensor
  temp = mlx.readAmbientTempC();
  temp = 3.3; //dummy

  //Mask Detection
  if(masker == 1 && state == 0){
    state =1;
  }
    
  //State Machine
  if(state==1 && digitalRead(ir_hs)==0){
    digitalWrite(relay_pump, LOW);
    timer = millis();
    state = 2;
  }
  if(state==2){
    if(millis()-timer > 500){
      digitalWrite(relay_pump, HIGH);
    }
    if(masuk==true){
      digitalWrite(relay_lock, LOW);
      timer = millis();
      state = 3;
    }
  }
  if(state==3){
    if(millis()-timer > 3000){
      digitalWrite(relay_lock, HIGH);
    }
    if(digitalRead(ir_out)==1){
      state = 4;
    }
  }
  if(ir_out==0 && state==4){
    people_in++;
    state=0;
  }
  if(state==4){
    if(digitalRead(ir_out)==0){
      state=0;
    }
  }
  if(digitalRead(ir_out)==1){
    state=5;
  }
  if(state==5 && masuk==true){
    if(digitalRead(ir_out)==0){
      state=0;
      people_out++;
    }
  }
}
