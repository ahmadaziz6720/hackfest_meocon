// this sample code provided by www.programmingboss.com
int x;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(1);
  pinMode(15, OUTPUT);
}
void loop() {
    while (!Serial.available());
    x = Serial.readString().toInt();
    if (x == 1) {
    digitalWrite(15, HIGH);
    }
    else {
      digitalWrite(15, LOW);
    }
}
