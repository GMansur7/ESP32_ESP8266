///////////////////////////////////////////////////////////////////////////////////////////
//Firebase
//importando bibliotecas
#include <WiFi.h>                          //importa biblioteca para conectar esp32 com wifi
#include <IOXhop_FirebaseESP32.h>          //importa biblioteca para esp32 se comunicar com firebase
#include <ArduinoJson.h>                   //importa biblioteca para colocar informação no formato json, utilizado no firebase (intalar versão 5)

//fazendo definições para não repetir muito texto durante o código 
#define WIFI_SSID "Mansur"                  //substitua "Nome_do_seu_wifi" pelo nome da sua rede wifi 
#define WIFI_PASSWORD "Mansur01"             //substitua "Senha_do_seu_wifi" pela senha da sua rede wifi 
#define FIREBASE_HOST "https://exemplo.firebaseio.com/"    //substitua "Link_do_seu_banco_de_dados" pelo link do seu banco de dados 
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"   //substitua "Senha_do_seu_banco_de_dados" pela senha do seu banco de dados

//#include <SPI.h>
//#include <Wire.h>
///////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/*
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
// On an arduino LEONARDO:   2(SDA),  3(SCL)
// On an ESP8266         :   4(SDA),  5(SCL),
// On an ESP32           :  21(SDA), 22(SCL), ...
#define OLED_RESET     2 // Reset pin # (or -1 if sharing Arduino reset pin)
//#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

#include "DHT.h"

#define DHTPIN 04    // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

/////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

/////////////////////////////////////////////////////////////////////////////////////////
//Firebase WiFi
  Serial.begin(115200);      //inicia comunicação serial
  Serial.println();          //imprime pulo de linha

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);     //inicia comunicação com wifi com rede definica anteriormente
  
  Serial.print("Conectando ao wifi");       //imprime "Conectando ao wifi"
  while (WiFi.status() != WL_CONNECTED)     //enquanto se conecta ao wifi fica colocando pontos
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  delay(1000);
  
  //Serial.println();                        //imprime pulo de linha

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   //inicia comunicação com firebase definido anteriormente
  delay(1000);
////////////////////////////////////////////////////////////////////////////////////////////

//  Serial.begin(115200); Essa linha reinicia a comunicação serial e trava o ESP32, deixsr comentada
  Serial.println(F("DHTxx test!"));

  dht.begin();
  delay(300);

/////////////////////////////////////////////////////////////////////////////////////////////////
/*
  // put your main code here, to run repeatedly:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Clear the buffer.
  display.clearDisplay();
*/  
///////////////////////////////////////////////////////////////////////////////////////////////// 
}

void loop() {

////////////////////////////////////////////////////////////////////////////////////////////////
  // Wait a few seconds between measurements.
/*  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  //delay(300);
*/  
  delay(1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
 
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  //float hif = 77;
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  //float hic = 25;

  Serial.print(F("Humidity: "));
  //Serial.println(c); //Menor resolução e mais rápido
  Serial.print(hif);
  Serial.print(F("%  Temperature: "));
  //Serial.println(t); //Menor resolução e mais rápido
  Serial.println(hic); //Maior resolução e mais lento

///////////////////////////////////////////////////////////////////////////////////////////
//Firebase função Set

  Firebase.setFloat("/Sala/Temperature", hif);
  delay(100);
  Firebase.setFloat("/Sala/Humidity", hic);
  delay(100);
///////////////////////////////////////////////////////////////////////////////////////////
  
////////////////////////////////////////////////////////////////////////////////////////////////
/* 
  display.display();
  display.clearDisplay();
//  delay(100);
  display.setTextSize(1);
  display.setTextColor(WHITE);// (BLACK, WHITE)
  display.setCursor(0,0);
  display.print(F("Termo-higrometro"));
  display.setCursor(0,16);
  display.print(F("Humidity:     "));
  display.print(hif); //Maior resolução e mais lento
  //display.print(h); //Menor resolução e mais rápido
  display.print(F(" %"));
  display.setCursor(0,24);
  display.print(F("Temperature:  "));
  display.print(hic); //Maior resolução e mais lento
  //display.print(t); //Menor resolução e mais rápido
  display.print(F(" C"));
  display.display();
//  delay(100);
*/
}
