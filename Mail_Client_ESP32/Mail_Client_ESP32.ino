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


void setup() {
  // put your setup code here, to run once:

WiFi.begin (ssid, password);
while (WiFi.status() !=WL_CONNECTED){
  //Serial.begin(115200);
  Serial.print("*");
  delay(200);
  }  
  Serial.println("WiFi is Connected");

//SMTPData smtpData;
  
smtpData.setLogin (smtpServer, smtpServerPort, emailSenderAccont, emailSenderPassword);
smtpData.setSender ("ESP32 Sender E-mail", emailSenderAccont);
smtpData.setPriority ("Hight");
smtpData.setSubject (emailSubject);
smtpData.setMessage ("Hello Word! This is ESP Email Testing!", false);
smtpData.setMessage ("<p>Hello Word!</p><p>Mansur.iot7 begin!</p>",true);
smtpData.addRecipient(emailRecipient);

if (!MailClient.sendMail (smtpData)){
  Serial.println ("Error in Sending the Email" + MailClient.smtpErrorReason());

  smtpData.empty();
  }
} 

void loop() {
  // put your main code here, to run repeatedly:
 
}
void sendCallback (SendStatus massage){
  Serial.begin(115200);
  Serial.println (massage.info());

  if (massage.success ()){
  Serial.print("+++++++");
  }
}
