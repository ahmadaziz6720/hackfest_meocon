#include <Adafruit_MLX90614.h> //SDA=A4; SCL=A5
#include <Servo.h>

Servo servo_hs; 
Servo servo_door;

#define relay 2
#define ir_in 4
#define ir_out 7
#define ir_hs 12
#define laser 8

bool idle = true;
bool mask = false;
int state = 0;
float suhu = 0;
int count_ppl = 0;

unsigned long timer;

void setup() {
  servo_hs.attach(3);
  servo_hs.attach(5);
  servo_hs.write(0);
  servo_door.write(0);

  pinMode(relay, OUTPUT);
  pinMode(ir_in, INPUT);
  pinMode(ir_out, INPUT);
  pinMode(ir_hs, INPUT);
  pinMode(laser, OUTPUT);

  Serial.begin(9600);
  timer = millis();
}

void loop() {
  if(digitalRead(ir_hs)==1){
    digitalWrite(laser, HIGH);
    servo_hs.write(90); //belum ada matiin servo
    //baca suhu
    //send data suhu
    if(suhu <=37){
      //display silahkan masuk
      ++state;
    }else{
      //display dilarang masuk
      state = 0;
    }
  }
  timer = millis();
  while(millis()-timer <= 10000 && state == 1){
    //read data mask
    if(mask == true){
      ++state;
    }
  }//end while
  
  if(state == 2){
    digitalWrite(relay, HIGH);
    servo_door.write(120);
    timer = millis();
    while(millis()-timer <= 10000 && state == 2){
      if(digitalRead(ir_in) == HIGH){
        ++state;
      }
    }
  }else{
    //diplay dilarang masuk, tidak pake masker
    state = 0;
  }

  if(state == 3){
    if(digitalRead(ir_out)==HIGH){
      servo_door.write(0);
      digitalWrite(relay, LOW);
      ++count_ppl;
      ++state;
    }
  }else{
    //display tidak ada yang masuk
    state = 0;
  }
}
