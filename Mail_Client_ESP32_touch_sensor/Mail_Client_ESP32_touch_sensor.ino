#include "ESP32_MailClient.h"

const char* ssid = "Mansur";
const char* password = "Mansur01";

#define emailSenderAccont "mansur.iot7@gmail.com"
#define emailSenderPassword "74021798051Iot"
#define emailRecipient "gustavo.mansuroliveira@gmail.com"
#define smtpServer "smtp.gmail.com"
#define smtpServerPort 465
#define emailSubject "ESP32 Testing Email"

SMTPData smtpData;

int touchValue;

void setup() {
  // put your setup code here, to run once:

pinMode(17,OUTPUT);
digitalWrite(17,LOW);  

WiFi.begin (ssid, password);
while (WiFi.status() !=WL_CONNECTED){
  //Serial.begin(115200);
  Serial.print("*");
  delay(200);
  }  
  Serial.println("WiFi is Connected");
/*
//SMTPData smtpData;
  
//smtpData.setLogin (smtpServer, smtpServerPort, emailSenderAccont, emailSenderPassword);
//smtpData.setSender ("ESP32 Sender E-mail", emailSenderAccont);
//smtpData.setPriority ("Hight");
//smtpData.setSubject (emailSubject);
//smtpData.setMessage ("Hello Word! This is ESP Email Testing!", false);
//smtpData.setMessage ("<p>Hello Word!</p><p>Mansur.iot7 begin!</p>",true);
//smtpData.addRecipient(emailRecipient);

//if (!MailClient.sendMail (smtpData)){
//  Serial.println ("Error in Sending the Email" + MailClient.smtpErrorReason());

//  smtpData.empty();
//  }
*/
} 
void loop() {
// put your main code here, to run repeatedly:

smtpData.setLogin (smtpServer, smtpServerPort, emailSenderAccont, emailSenderPassword);
smtpData.setSender ("ESP32 Sender E-mail", emailSenderAccont);
smtpData.setPriority ("Hight");
smtpData.setSubject (emailSubject);
smtpData.addRecipient(emailRecipient);
touchValue = touchRead(4);
Serial.println("Touch sensor value: ");
Serial.println(touchValue);  

  
if (touchValue >= 100)
{ 
//  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);
  smtpData.setMessage ("Hello Word! This is ESP Email Testing!", false);
//  smtpData.addRecipient(emailRecipient);
 
if (!MailClient.sendMail(smtpData))
  Serial.println ("Error in Sending the Email" + MailClient.smtpErrorReason());
  smtpData.empty();
delay(10000);
    
  }
}
