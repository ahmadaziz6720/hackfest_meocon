//tes semua sensor
#define relay_pump 2
#define relay_lock 3
#define ir_in 4
#define ir_out 7
#define ir_hs 12
//#define laser 8

void setup() {
  pinMode(relay_pump, OUTPUT);
  pinMode(relay_lock, OUTPUT);
  pinMode(ir_in, INPUT);
  pinMode(ir_out, INPUT);
  pinMode(ir_hs, INPUT);
  Serial.begin(9600);
//  pinMode(laser, OUTPUT);
}

void loop() {
  Serial.print("ir_in:");
  Serial.print(digitalRead(ir_in));
  Serial.print("     ir_out:");
  Serial.print(digitalRead(ir_out));
  Serial.print("     ir_hs:");
  Serial.println(digitalRead(ir_hs));

  if(digitalRead(ir_in)==LOW){
    digitalWrite(relay_pump, HIGH);
    digitalWrite(relay_lock, LOW);
  }else if(digitalRead(ir_in)==HIGH){
    digitalWrite(relay_pump, LOW);
    digitalWrite(relay_lock, HIGH);
  }
  // put your main code here, to run repeatedly:

}
