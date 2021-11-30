#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Mansur";
const char* password = "Mansur01";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.43.3:80";
//String serverName = "https://6bb5-2804-431-e7da-4763-37b0-c48f-2b3d-664e.ngrok.io/";
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
setgpio2on();
delay(5000);
setgpoi2off();
delay(5000);
}

void setgpio2on(){
    //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      //endereço do site
      String serverPath = serverName + "/gpio2on";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());

      //envio de cabeçalho
      http.addHeader("header", "TWFuc3VyOk1hbnN1cjAx");

      //String httpRequestData = "Banana";

      // Send HTTP GET request
      int httpResponseCode = http.GET();

      //Send HTTP POST request
      //int httpResponseCode = http.POST(httpRequestData);
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        //Carega o HTML do web server
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    //lastTime = millis();
  }
}

void setgpoi2off(){
    //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      //endereço do site
      String serverPath = serverName + "/gpio2off";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());

      //envio de cabeçalho
      http.addHeader("header", "TWFuc3VyOk1hbnN1cjAx");

      //String httpRequestData = "Banana";

      // Send HTTP GET request
      int httpResponseCode = http.GET();

      //Send HTTP POST request
      //int httpResponseCode = http.POST(httpRequestData);
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        //Carega o HTML do web server
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    //lastTime = millis();
  }
}
