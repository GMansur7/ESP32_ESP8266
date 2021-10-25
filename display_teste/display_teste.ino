#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     2 // Reset pin # (or -1 if sharing Arduino reset pin)
//#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  
}

void loop() {
  // put your main code here, to run repeatedly:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  delay(2000);
  display.setTextSize(1);
  display.setTextColor(WHITE);// (BLACK, WHITE)
  display.setCursor(0,0);
  display.println("Victor Mansur");
  display.setCursor(0,8);
  display.println("Trabalho professor ");
  display.setCursor(0,16);
  display.println("Nuncio");
  display.setCursor(0,24);
  display.println("Mansur");
  display.setCursor(0,32);
  display.println("23 C");
  display.setCursor(0,40);
  display.println("32 C");
  display.setCursor(0,48);
  display.println("32 C");
  display.println("40 C");
  display.display();
  delay(2000);

  display.display();  
  display.setTextSize(1);
  display.setTextColor(BLACK);// (BLACK, WHITE)
  display.setCursor(0,24);
  display.println("Mansur");
  display.setTextColor(WHITE);// (BLACK, WHITE)
  display.setCursor(0,24);
  display.println("MANSUR Oliveira");
  display.display();
  delay(4000);

}
