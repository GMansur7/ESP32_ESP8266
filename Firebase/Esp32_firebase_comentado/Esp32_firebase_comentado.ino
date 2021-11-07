////////////////////////////////////////////////////
//Código exemplo como comunicar esp32 com firebase//
////////////////////////////////////////////////////


////////////////////
//links adicionais//
////////////////////

//link do tutorial:
//link para fazer download dos códigos:
//Autor: Matteo Freitas Reis (email: matteo.reis@gmail.com)


//importando bibliotecas
#include <WiFi.h>                          //importa biblioteca para conectar esp32 com wifi
#include <IOXhop_FirebaseESP32.h>          //importa biblioteca para esp32 se comunicar com firebase
#include <ArduinoJson.h>                   //importa biblioteca para colocar informação no formato json, utilizado no firebase (intalar versão 5)

//fazendo definições para não repetir muito texto durante o código 
#define WIFI_SSID "Mansur"                  //substitua "Nome_do_seu_wifi" pelo nome da sua rede wifi 
#define WIFI_PASSWORD "Mansur01"             //substitua "Senha_do_seu_wifi" pela senha da sua rede wifi 
#define FIREBASE_HOST "https://exemplo.firebaseio.com/"    //substitua "Link_do_seu_banco_de_dados" pelo link do seu banco de dados 
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"   //substitua "Senha_do_seu_banco_de_dados" pela senha do seu banco de dados

void setup() {
  Serial.begin(115200);      //inicia comunicação serial
  Serial.println();          //imprime pulo de linha

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);     //inicia comunicação com wifi com rede definica anteriormente
  
  Serial.print("Conectando ao wifi");       //imprime "Conectando ao wifi"
  while (WiFi.status() != WL_CONNECTED)     //enquanto se conecta ao wifi fica colocando pontos
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  //Serial.println();                         //imprime pulo de linha

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   //inicia comunicação com firebase definido anteriormente

}

void loop() {
// remova os marcadores de comentário "/*  */" para testar os códigos das funções Set, Get e Push


  /////////////////////////
  //exemplo da função Get//
  /////////////////////////
/*  
  Serial.println();
  Serial.print("Dono do quarto: ");
  Serial.print(Firebase.getString("/quarto/dono"));
  Serial.println();
  Serial.print("Luminosidade do quarto: ");
  Serial.print(Firebase.getInt("/quarto/luminosidade"));
  Serial.println();
  Serial.print("Temperatura do quarto: ");
  Serial.print(Firebase.getFloat("/quarto/temperatura"));
  Serial.println();
  Serial.print("O quarto está ocupado: ");
  Serial.print(Firebase.getBool("/quarto/ocupado"));
  Serial.println();
  Serial.print("Luminosidade da sala: ");
  Serial.print(Firebase.getInt("/sala/luminosidade"));
  Serial.println();
  delay(3000);
*/



  /////////////////////////
  //exemplo da função Set//
  /////////////////////////

  Firebase.setString("/quarto/dono", "Rebeca");
  Firebase.setInt("/quarto/luminosidade", 300);
  Firebase.setBool("/quarto/ocupado", false);
  Firebase.setFloat("/quarto/dono", 24.7);
  Firebase.setInt("/sala/luminosidade", 200);
  delay(3000);
  Firebase.setString("/quarto/dono", "Matteo");
  Firebase.setInt("/quarto/luminosidade", 500);
  Firebase.setBool("/quarto/ocupado", true);
  Firebase.setFloat("/quarto/dono", 35.3);
  Firebase.setInt("/sala/luminosidade", 500);
  delay(3000);



  //////////////////////////
  //exemplo da função Push//
  //////////////////////////
/*
  Firebase.pushString("/quarto/registro", "Matteo");
  delay(3000);
  Firebase.pushString("/quarto/registro", "Rebeca");
  delay(3000);
  Firebase.pushString("/quarto/registro", "Vanderson");
  delay(3000);
  Firebase.pushString("/quarto/registro", "Raquel");
  delay(3000);
*/
}
