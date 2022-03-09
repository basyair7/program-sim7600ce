#include<SoftwareSerial.h>
#include<Wire.h>

SoftwareSerial mygsm(7,8);

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  mygsm.begin(115200);
  // Perintah Module
  Serial.println("Connecting To Server........");
  mygsm.println("AT+CNMP=13");
  delay(2000);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  // melakukan terima memanggil
  digitalWrite(13,HIGH);
  delay(3000);
  //mygsm.println("ATA");
  
  mygsm.println("AT+COPS?");
  mygsm.write(Serial.read());
  delay(1000);
  digitalWrite(13,LOW);
  delay(3000);
}
