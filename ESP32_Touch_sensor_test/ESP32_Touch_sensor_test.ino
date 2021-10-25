
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Touch Sensor Test");
  pinMode(17,OUTPUT);
  digitalWrite(17,LOW);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  int value = touchRead(4);
  Serial.println(value);
  if(value >= 50)
  {
    digitalWrite(17,HIGH);
    Serial.println("LED ON");
    delay(10);
    }else if(value < 50)
    {
      digitalWrite(17,LOW);
      Serial.println("LED OFF");
    delay(10);
      }
  delay(10);
}
