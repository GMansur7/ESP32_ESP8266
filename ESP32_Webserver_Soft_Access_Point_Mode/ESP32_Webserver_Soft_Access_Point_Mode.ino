#include "WiFi.h"
#define LED0 04
#define LED1 05
const char* ssid = "ESP32-Soft-accessPoint";
const char* password = "Mansur01";
WiFiServer server(80);
String html ="<!DOCTYPE html> \
<html> \
<body> \
<center><h1>ESP32 Soft access point</h1></center> \
<center><h2>Mansur Web Server</h2></center> \
<form> \
<button name=\"LED0\" button style=\"color:green\" value=\"ON\" type=\"submit\">LED0 ON</button> \
<button name=\"LED0\" button style=\"color:red\" value=\"OFF\" type=\"submit\">LED0 OFF</button><br><br> \
<button name=\"LED1\" button style=\"color:green\" value=\"ON\" type=\"submit\">LED1 ON</button> \
<button name=\"LED1\" button style=\"color:red\" value=\"OFF\" type=\"submit\">LED1 OFF</button> \
</form> \
</body> \
</html>";


void Connect_WiFi()
{
WiFi.begin(ssid, password);
while(WiFi.status() != WL_CONNECTED)
{
delay(100);
}
}

void setup()
{
Serial.begin(115200);
pinMode(LED0, OUTPUT);
pinMode(LED1, OUTPUT);
digitalWrite(LED0, LOW);
digitalWrite(LED1, LOW);
Serial.print("Setting soft access point mode");
WiFi.softAP(ssid, password);

IPAddress IP(192, 168, 1, 1);// CONFIGURAÇÃO DE IP FIXO
IPAddress NMask(255, 255, 255, 0);//MASCARA DE REDE
WiFi.softAPConfig(IP, IP, NMask);
//IPAddress IP = WiFi.softAPIP();// IP DINAMICO


Serial.print("AP IP address: ");
Serial.println(IP);
server.begin();
}


void loop()
{
WiFiClient client=server.available();
if(client)
{
String request = client.readStringUntil('\r');
if(request.indexOf("LED0=ON") != -1)digitalWrite(LED0, HIGH);
if(request.indexOf("LED0=OFF") != -1)digitalWrite(LED0, LOW);
if(request.indexOf("LED1=ON") != -1)digitalWrite(LED1, HIGH);
if(request.indexOf("LED1=OFF") != -1)digitalWrite(LED1, LOW);
client.print(html);
request="";
}
}
