  /* Command serial monitor AT
* Check serial support : AT+IPREX=0 (Change baud rate : AT+IPR? // AT+IPR=<speed>
* 1. Check module : AT
* 2. Check Signal Provide : AT+COPS? 
*   Possible values for access technology,
*   0 GSM
*   1 GSM Compact
*   2 UTRAN
*   3 GSM w/EGPRS
*   4 UTRAN w/HSDPA
*   5 UTRAN w/HSUPA
*   6 UTRAN w/HSDPA and HSUPA
*   7 E-UTRAN
* 3. Check Signal Quality : AT+CSQ //Signal quality test, value range is 0-31 , 31 is the best
* 
* 4. Change Signal Provide : AT+COPS=0,0,"Tsel-PakaiMasker",*Change(0, 2 or 7)
* 5. Preferred mode selection : AT+CNMP? // AT+CNMP=(2 *auto, 13 *GSM only, 14 *WCDMA Only, 38 *LTE Only) read datasheet on page 96
* 
* Call command : 
* 1. ATD+"+628XXXX" -> used to call phone number.
* 2. ATA "answer an incoming call"
* 3. ATH / AT+CHUP "disconnect an incoming call"
* 
* 
*/

#include<SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial mySerial(3,2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  //Serial.begin(115200);
  //mySerial.begin(115200);

  //set_baud(38400);

}

void loop() {
  // put your main code here, to run repeatedly:
 while(1){
   while(mySerial.available()){
    Serial.write(mySerial.read());
  }
  while(Serial.available()){
    mySerial.write(Serial.read());
  }
  
 }
}

void csq(){
  //mySerial.println("AT");
  //delay(1000);
  //mySerial.println("AT+CSQ");
  //delay(5000);
  mySerial.println("AT+COPS?");
  delay(2000);
  
}

void set_baud(long int baud){
  delay(1000);
  //mySerial.println("AT");
  //delay(500);
  mySerial.print("AT+IPR=");
  mySerial.println(baud);
  delay(1000);
  Serial.begin(baud);
  mySerial.begin(baud);
  delay(500);
}
