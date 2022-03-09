#include <SoftwareSerial.h>
#include <Wire.h>
#include "RTClib.h"

/******************************SETTINGS********************************/
/* true = aktif
 * false = non-aktif */
 
// Set jam test pemanggilan
bool auto_check = false; // cek nomor modul (memanggil ke hp) secara otomatis
#define jam_test    0
#define menit_test  0
#define detik_test  0

// Set jam
#define jam_mulai     0 // jam memulai proses menerima
#define jam_mulai_2  14 // jam memulai proses memanggil

// set menit menerima panggilan
#define menit_1          0
#define menit_akhir_1   58
#define menit_tutup     59

// set menit memanggil
bool auto_call = false;  // memanggil panggilan secara otomatis
#define menit_2          0
#define menit_akhir_2   59

// set nomor hp panggilan
//#define nomor_hp    "ATD082281406024;"
#define nomor_cek   "ATD082281406024;"
//#define nomor_hp    "ATD085261098617;"
#define nomor_hp    "ATD085261098637;"

/**********************************************************************/

// koneksi modul sim7600 ke arduino board
SoftwareSerial mygsm(7, 8);
// variabel rtc
RTC_DS3231 rtc;
char hari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
/* PIN RTC : SDA = A4
 *           SCL = A5
 * PIN SIM7600 = 7 & 8 */

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  mygsm.begin(115200); 
  //mygsm.begin(230400);
  Serial.begin(115200); 
  //Serial.begin(230400);

  //Perintah AT untuk modul
  Serial.println("Connecting To Server........");
  mygsm.println("AT");
  set_baud_rate(9600);

  cek_rtc();
  tanggal_waktu();

  if(auto_check == 1){
    cek_modul();  
  }
  
  //memanggil();
  //menerima();
}

void loop() {
  // put your main code here, to run repeatedly:
  /**
  if(mygsm.available()){
    Serial.write(mygsm.read()); //if Serial received data, output it via Serial.
  }
  if(Serial.available()){
    mygsm.write(Serial.read()); //if mygsm received data, output it via Serial.
  }
  **/
  //digitalWrite(13,HIGH);
  //delay(500);
  //tanggal_waktu();
  
  menerima();
  if(auto_call == 1){
    memanggil();
  }
  
}

void menerima(){
  // Atur jam, hari, tanggal, bulan , tahun
  DateTime now = rtc.now();
  //menerima telfon
  if(now.hour() == jam_mulai){
    // perintah menerima panggilan telfon
    if (now.minute() == menit_1 || now.minute() <= menit_akhir_1){
      //tanggal_waktu();
      //Serial.println("Menerima panggilan...");
      //delay(500);
      digitalWrite(13,HIGH);
      mygsm.println("AT");
      delay(3000);
      mygsm.println("ATA");
      delay(2000);
      digitalWrite(13,LOW);
      delay(5000);
      
    }
     // perintah tutup telfon
   else if (now.minute() == menit_tutup){
      //Serial.println("panggilan Selesai...");
      digitalWrite(13,LOW);
      delay(500);
      mygsm.println("AT+CHUP");
      delay(2000);
      //memanggil();
    }
  }
  else {
    mygsm.println("error");
    Serial.println("Ada terjadi kesalahan...");
    delay(1000);
  }
}

void memanggil(){
  // Atur jam, hari, tanggal, bulan , tahun
  DateTime now = rtc.now();
  //melakukan panggilan telfon
  if(now.hour() == jam_mulai_2){
    // perintah menerima panggilan telfon
    if (now.minute() == menit_2 || now.minute() <= menit_akhir_2){
      //tanggal_waktu();
      //Serial.println("Memanggil...");
      digitalWrite(13,HIGH);
      delay(500);
      mygsm.println("AT");
      delay(3000);
      mygsm.println(nomor_hp);
      delay(2000);
      while(1);
    }
    else if(now.minute() == menit_akhir_2){
      digitalWrite(13,LOW);
      delay(200);
    }
  }
  else {
    //mygsm.println("error");
    Serial.println("Ada terjadi kesalahan...");
    delay(1000);
  }
}

void cek_modul(){
  // Cek misscall ke hp jika program berjalan (misscall pada jam 19.00 - 19.59)
  DateTime now = rtc.now();
  if(now.hour() == jam_test){
    if(now.minute() == menit_test && now.second() == detik_test){
      mygsm.println(nomor_cek);
      delay(1000);
    }
  }
}

void cek_rtc(){
  // Set waktu RTC
  // jika RTC tidak terkoneksi
  if (!rtc.begin()){
    Serial.println("RTC tidak terbaca");
  }
  // jika RTC kehabisan daya baterai
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (rtc.lostPower()){
    // atur waktu sesuai pada komputer
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // atur waktu secara manual
    // 2019, January, 25 jam 10:30:00
    // rtc.adjust(DateTime(2019, 1, 25, 10, 30, 0));
    
  }
  delay(500);
}

void set_baud_rate(long int baud){
  delay(1000);
  mygsm.print("AT+IPR=");
  mygsm.println(baud);
  delay(500);
  Serial.begin(baud);
  mygsm.begin(baud);
  delay(1000);
}

void tanggal_waktu(){
  // Atur jam, hari, tanggal, bulan , tahun
  DateTime now = rtc.now();
  // Tanggal, Bulan, Tahun
  Serial.print(hari[now.dayOfTheWeek()]); Serial.print(", "); //Hari
  Serial.print(now.day()); Serial.print('/'); //Tanggal
  Serial.print(now.month()); Serial.print('/'); //Bulan
  Serial.print(now.year()); Serial.print(' '); //Tahun
  // Waktu
  Serial.print(now.hour()); Serial.print(':'); //jam
  Serial.print(now.minute()); Serial.print(':'); //menit
  Serial.print(now.second()); Serial.println(); //detik
  delay(1000);
}
