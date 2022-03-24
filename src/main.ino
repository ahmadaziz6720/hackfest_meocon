#define relay_pump 2
#define relay_lock 3
#define ir_out 5
#define trig 8
#define echo 7
#define ir_hs 12

int masker = 0;
int state = 0;
boolean masuk =false;
int people = 0;
int maximumRange = 200;
int minimumRange = 0;
long duration, distance;
unsigned long timer;

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
  while (!Serial.available());
  masker = Serial.readString().toInt();
  if (masker == 1) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  Serial.println(String(state) + " " + String(distance) + " " + String(digitalRead(ir_hs)) + " " + String(digitalRead(ir_out))+ " " + String(people));
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

  if(masker == 1 && state == 0){
    state =1;
  }
    
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
    if(digitalRead(ir_out)==0){
      people++;
      state=0;
    }
  }
}
