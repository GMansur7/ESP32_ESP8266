int analogValue = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Analog Pin Test");
}

void loop() {
  // put your main code here, to run repeatedly:
analogValue = analogRead(4);
Serial.println(analogValue);
delay(500);
}
