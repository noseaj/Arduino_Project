#include "config.h"

//////////// finger print /////////////
#include <Adafruit_Fingerprint.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(0, 2);  // TX = D3(GPIO 0), RX = D4(GPIO 2)

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white

#define mySerial Serial1

#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
//////////// finger print /////////////

//////////// oled /////////////
#include <Wire.h>
#include "SSD1306Wire.h"

SSD1306Wire display(0x3c, SDA, SCL);
//////////// oled /////////////

// set up the 'fingerprint' feed
AdafruitIO_Feed *fingerprint = io.feed("fingerprint");
String std_ID = "";

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  
  //////////// finger print /////////////
  // Serial.begin(9600); // client - arduino
  finger.begin(57600);  // arduino - module

  if (finger.verifyPassword()) {
    Serial.println("\nFound fingerprint sensor!");
  } else {
    Serial.println("\nDid not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
  //////////// finger print /////////////
  
  //////////// oled /////////////
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  //////////// oled /////////////
}

void loop() {
  
  io.run();
  
  //////////// finger print /////////////
  uint8_t p = finger.getImage();

  // returns -1 if failed, otherwise returns ID #
  if (p != FINGERPRINT_OK)  return;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  //////////// finger print /////////////

  std_ID = fingerprint_match(finger.fingerID);  

  Serial.print(" with Student_ID :  "); Serial.println(std_ID);

  display.drawString(0, 15, std_ID);
  display.drawString(0, 30, "Attendance completed");
  display.display();
  
  // save fingerID to the 'fingerprint' feed on Adafruit IO 
  fingerprint->save(std_ID);
  
  // 어짜피 일일히 찍는데 시간이 조금 걸리니깐 5초로 설정
  delay(5000);
  
  display.clear();

}

// Student matching 
String fingerprint_match(int id) {
  
  String student = "";
  if (id == 1) {
    student = "2022123001 홍길동"; // Change Student name
  }
  else if (id == 2) {
    student = "2017123099 이순신"; // Change Student name
  }
  else if (id == 3) {
    student = "2021123011 유관순"; // Change Student name
  }
  else if (id == 4) {
    student = "2019123016 안창호"; // Change Student name
  }
  else if (id == 5) {
    student = "2018123029 김구"; // Change Student name
  }
  return student;
}
