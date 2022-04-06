// Lib Contactless Temperature Sensor
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// LCD Display
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define GPIO pins
#define relay_pump 4
#define relay_lock 6
#define ir_out 5
#define trig 8
#define echo 7
#define ir_hs 12

// Declare Variables
int masker = 0;
int state = 0;
int people_in = 0;
int people_out = 0;
int current_people = 0;
int maximumRange = 200;
int minimumRange = 0;
int active_gate = 0;
int no_mask = 0;
int over_temp = 0;
boolean masuk =false;
long duration, distance;
unsigned long timer;
float temp = 0;

// Setup I/O etc.
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

  lcd.begin();
}

void loop() {
  
  //Read Ultrasonic Sensor
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

  //Read Temperature Sensor
  temp = mlx.readAmbientTempC();

  //Read From Serial - Mask Detection
  while (!Serial.available());
  masker = Serial.readString().toInt();
  if(state == 0){
    lcd.setCursor(0,0);
    lcd.print("     Welcome    ");
    lcd.setCursor(0,1);
    lcd.print(" To MeoCon Corp ");
  }

  if(masker == 1 && state == 0){
    state =1;
    lcd.setCursor(0,0);
    lcd.print(" Mask Detected  ");
    lcd.setCursor(0,1);
    lcd.print("Check Tmperature");
  }

  current_people = people_in - people_out;
  Serial.println(String(current_people) + " " + String(active_gate) + " " + String(people_in) + " " + String(people_out)+ " " + String(no_mask)+ " " + String(over_temp));
    
  //State Machine
  if(state==1 && digitalRead(ir_hs)==0){
    digitalWrite(relay_pump, LOW);
    timer = millis();
    state = 2;
    lcd.setCursor(0,0);
    lcd.print("   Your TMP:    ");
    lcd.setCursor(0,1);
    lcd.print("     "+String(temp)+" C      ");
  }
  if(state==2){
    if(millis()-timer > 500){
      digitalWrite(relay_pump, HIGH);
    }
    if(masuk==true){ //Orangnya terdeteksi sensor, kunci terbuka
      digitalWrite(relay_lock, LOW);
      timer = millis();
      state = 3;
      lcd.setCursor(0,0);
      lcd.print("  Door Opened   ");
      lcd.setCursor(0,1);
      lcd.print(" Please come in ");
    }
  }
  if(state==3){
    if(millis()-timer > 3000){
      digitalWrite(relay_lock, HIGH);
    }
    if(digitalRead(ir_out)==1){ //Pint dibuka (di dorong)
      state = 4;
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
    }
  }
  if(digitalRead(ir_out)==0 && state==4){ // Pintu udah ketutup lagi
    people_in++;
    state=0;
  }
  if(digitalRead(ir_out)==1){
    state=5; //People Out
  }
  if(state==5 && masuk==true){ // orang udah ngelewatin pintu
    if(digitalRead(ir_out)==0){ // pintu udah ditutup lagi
      state=0;
      people_out++;
    }
  }
}
