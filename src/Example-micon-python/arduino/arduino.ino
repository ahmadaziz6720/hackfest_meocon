int x;
void setup() {
 Serial.begin(9600);
 Serial.setTimeout(1);
 pinMode(13, OUTPUT);
}
void loop() {
 while (!Serial.available());
 x = Serial.readString().toInt();
 if (x == 1) {
  digitalWrite(13, HIGH);
 }
 else {
  digitalWrite(13, LOW);
 }
 Serial.println("Haiii Lizaa");
}
