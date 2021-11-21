//Select your modem
//SSL/TLS is currently supported only with SIM8xx series
#define TINY_GSM_MODEM_SIM800

//Increase RX buffer
//#define TINY_GSM_RX_BUFFER 256 

//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
//#include <TinyGPS++.h> //https://github.com/mikalhart/TinyGPSPlus
#include <TinyGsmClient.h> //https://github.com/vshymanskyy/TinyGSM
#include <ArduinoHttpClient.h> //https://github.com/arduino-libraries/ArduinoHttpClient
//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
const char FIREBASE_HOST[]  = "lilygo-esp32-sim800l-default-rtdb.firebaseio.com";
const String FIREBASE_AUTH  = "Legd1ze7Y5xDqgZQxdN23zWPvv791FZe0MSuNv26";
//const String FIREBASE_PATH  = "dados/coordenadas";
const String FIREBASE_PATH  = "/";
const int SSL_PORT          = 443;
//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "GPRS internet";
char user[] = "";
char pass[] = "";
//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN


//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
//GSM Module RX pin to ESP32 2
//GSM Module TX pin to ESP32 4
//#define rxPin 26
//#define txPin 27

//pino LED embarcado no pino 13
#define LED 13


//Pinos SIM800L
#define MODEM_RST 5
#define MODEM_PWRKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26

HardwareSerial sim800(1);
TinyGsm modem(sim800);
//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
/*
//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
//GPS Module RX pin to ESP32 17
//GPS Module TX pin to ESP32 16
#define RXD2 16
#define TXD2 17
HardwareSerial neogps(2);
TinyGPSPlus gps;
//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
*/
//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
TinyGsmClientSecure gsm_client_secure_modem(modem, 0);
HttpClient http_client = HttpClient(gsm_client_secure_modem, FIREBASE_HOST, SSL_PORT);
//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

//unsigned long previousMillis = 0;
//long interval = 10000;

//**************************************************************************************************
void setup() {

  pinMode(LED, OUTPUT);
  
  //Reseta o SIM800L
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_PWRKEY, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);
  digitalWrite(MODEM_PWRKEY, HIGH);
  delay(100);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(1000);
  digitalWrite(MODEM_PWRKEY, HIGH);


  Serial.begin(115200);
  Serial.println("esp32 serial initialize");
  
  sim800.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  Serial.println("SIM800L serial initialize");
/*
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("neogps serial initialize");
  delay(3000);
*/  
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  //Restart takes quite some time
  //To skip it, call init() instead of restart()
  Serial.println("Initializing modem...");
  modem.restart();
  String modemInfo = modem.getModemInfo();
  Serial.print("Modem: ");
  Serial.println(modemInfo);
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  
  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");
  
  http_client.setHttpResponseTimeout(90 * 1000); //^0 secs timeout
}
//**************************************************************************************************


//**************************************************************************************************
void loop() {
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  //Restart takes quite some time
  //To skip it, call init() instead of restart()
  //Serial.println("Initializing modem...");
  //modem.init();
  //String modemInfo = modem.getModemInfo();
  //Serial.print("Modem: ");
  //Serial.println(modemInfo);
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  //Serial.print(F("Waiting for network..."));
  //if (!modem.waitForNetwork()) {
    //Serial.println(" fail");
    //delay(1000);
    //return;
  //}
  //Serial.println(" OK");
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
    
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  Serial.print(F("Connecting to "));
  Serial.print(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    Serial.println(" fail");
    delay(1000);
    return;
  }
  Serial.println(" OK");
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  
  http_client.connect(FIREBASE_HOST, SSL_PORT);
  
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  while (true) {
    if (!http_client.connected()) {
      Serial.println();
      http_client.stop();// Shutdown
      Serial.println("HTTP  not connect");
      break;
    }
    else{
      gps_loop();
    }
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
}
//**************************************************************************************************

//**************************************************************************************************
void PostToFirebase(const char* method, const String & path , const String & data, HttpClient* http) {
  String response;
  int statusCode = 0;
  http->connectionKeepAlive(); // Currently, this is needed for HTTPS
  
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  String url;
  if (path[0] != '/') {
    url = "/";
  }
  url += path + ".json";
  url += "?auth=" + FIREBASE_AUTH;
  Serial.print("POST:");
  Serial.println(url);
  Serial.print("Data:");
  Serial.println(data);
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  
  String contentType = "application/json";
  http->put(url, contentType, data);
//  http->put("/.json?auth=Legd1ze7Y5xDqgZQxdN23zWPvv791FZe0MSuNv26", "application/json", "{\"lat\":41.2,\"lng\":52.1}"); // exemplo de preenchimento
//lilygo-esp32-sim800l-default-rtdb.firebaseio.com/.json?auth=Legd1ze7Y5xDqgZQxdN23zWPvv791FZe0MSuNv26/application/json/{\"lat\":41.2,\"lng\":52.1}
//link para navegador:lilygo-esp32-sim800l-default-rtdb.firebaseio.com/.json?=Legd1ze7Y5xDqgZQxdN23zWPvv791FZe0MSuNv26/application/json/{\"lat\":80.2,\"lng\":52.1}
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  // read the status code and body of the response
  //statusCode-200 (OK) | statusCode -3 (TimeOut)
  statusCode = http->responseStatusCode();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  response = http->responseBody();
  Serial.print("Response: ");
  Serial.println(response);
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  if (!http->connected()) {
    Serial.println();
    http->stop();// Shutdown
    Serial.println("HTTP POST disconnected");
  }
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
}
//**************************************************************************************************


//**************************************************************************************************

void gps_loop()
{
  /*
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  //Can take up to 60 seconds
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;){
    while (neogps.available()){
      if (gps.encode(neogps.read())){
        newData = true;
        break;
      }
    }
  }
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  //If newData is true
  if(true){
  newData = false;
  */
  String latitude = "47.2";
  String longitude = "46.4";
  //float altitude;
  //unsigned long date, time, speed, satellites;
  
  //latitude = String(gps.location.lat(), 6); // Latitude in degrees (double)
  //longitude = String(gps.location.lng(), 6); // Longitude in degrees (double)

  //latitude = String(gps.location.lat(), 6); // Latitude in degrees (double)
  //longitude = String(gps.location.lng(), 6); // Longitude in degrees (double)

  
  //altitude = gps.altitude.meters(); // Altitude in meters (double)
  //date = gps.date.value(); // Raw date in DDMMYY format (u32)
  //time = gps.time.value(); // Raw time in HHMMSSCC format (u32)
  //speed = gps.speed.kmph();
  
  Serial.print("Latitude= "); 
  Serial.print(latitude);
  Serial.print(" Longitude= "); 
  Serial.println(longitude);
      
  String gpsData = "{";
  gpsData += "\"lat\":" + latitude + ",";
  gpsData += "\"lng\":" + longitude + "";
  gpsData += "}";

  //PUT   Write or replace data to a defined path, like messages/users/user1/<data>
  //PATCH   Update some of the keys for a defined path without replacing all of the data.
  //POST  Add to a list of data in our Firebase database. Every time we send a POST request, the Firebase client generates a unique key, like messages/users/<unique-id>/<data>
  //DELETE  Remove data from the Firebase database reference reference.
  //https://firebase.google.com/docs/database/rest/save-data
  
  PostToFirebase("PATCH", FIREBASE_PATH, gpsData, &http_client);
  

 // }
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
}

//**************************************************************************************************
