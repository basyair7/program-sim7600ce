#include "RTClib.h"

// variabel rtc
RTC_DS3231 rtc;
char hari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};

void setup(){
  // put your setup code here, to run once:

  Serial.begin(9600);
  // Set waktu RTC
  // jika RTC tidak terkoneksi
  if(!rtc.begin()){
    Serial.println("RTC tidak terbaca!");
    
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // jika RTC kehabisan daya baterai
  if(rtc.lostPower()){
    // atur waktu sesuai pada komputer
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // atur secara manual
    // 2019, January, 25, jam 10:30:00
    //rtc.adjust(DateTime(2021, 1, 19, 12, 13, 0));
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
}

void loop(){
  // put your main code here, to run repeatedly:
  
  // Atur jam, hari, tanggal, bulan, tahun
  DateTime now = rtc.now();
  
  // Tanggal, Bulan, Tahun
  Serial.print(hari[now.dayOfTheWeek()]); Serial.print(", "); //Hari
  Serial.print(now.day()); Serial.print('/'); //Tanggal
  Serial.print(now.month()); Serial.print('/'); //Bulan
  Serial.print(now.year()); Serial.print(' '); //Tahun
  // Waktu
  Serial.print(now.hour()); Serial.print(":"); // Jam
  Serial.print(now.minute()); Serial.print(":"); //Menit
  Serial.print(now.second()); Serial.println(); // Detik

  delay(2000);
  
}
