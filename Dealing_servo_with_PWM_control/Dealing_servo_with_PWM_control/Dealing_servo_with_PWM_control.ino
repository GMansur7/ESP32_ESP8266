#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>



int freq = 50;
int ledCh = 0;
int resolution = 8; // 0 to 255 steps
int dutyCycle = 21;
float analogValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("Testing PWM");
  
ledcSetup (ledCh, freq, resolution);
ledcAttachPin (17, ledCh);
ledcWrite (ledCh, dutyCycle);


}

void loop() {
  // put your main code here, to run repeatedly:
ledcWrite (ledCh, dutyCycle);
analogValue = analogRead(4);

dutyCycle = map(analogValue, 0, 4095, 8, 33);
Serial.println(analogValue/40.95);
//dutyCycle = analogValue/40.95;
delay(50);
}
