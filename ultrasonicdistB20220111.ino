// ----------------- START OF USER SETTINGS

#define SSIDNAME "OnePingOnlyZ"
#define PASSWORD "GiveMeAPingVassily"

// Pre-configured for attaching the HC-SR04 to pins D5 & D6 on an
// ESP8266 LOLIN(WEMOS) D1 mini
#define RPin 13 // 13 ESP8266 D7
#define YPin 12 // 12 ESP8266 D6
#define GPin 14 // 14 ESP 8266 D5

// ----------------- END OF USER SETTINGS

// Ignore:
#define REMOTEIP { 192, 168, 4, 1 }
// to be used in client.connect below if you do not have a host-"name"

#define PAUSESECONDS 10
#define MEMORIES 250
#define INTERMEASURE 10

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
// #include <ESP8266WiFi.h>
// #include "WiFi.h"

byte ip[] = REMOTEIP;

char c = 0;
int i = 0;

WiFiClient client;

void setup() {
  pinMode(RPin, OUTPUT);
  pinMode(YPin, OUTPUT);
  pinMode(GPin, OUTPUT);
  digitalWrite(RPin, LOW);
  digitalWrite(YPin, LOW);
  digitalWrite(GPin, LOW);

  Serial.begin(115200); // // 300 or 1200 or 9600 or 115200 baudrate speed
  Serial.println("Ultrasonic Sensor"); // print some text in Serial Monitor

  WiFi.begin(SSIDNAME, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Retry");
    delay(2000);
  }



}

void loop() {

    if (client.connect(ip, 8023)) {
      while (client.connected()) {

        c = client.read();

        if (c == 'R' || c == 'Y' || c == 'G') {
          Serial.print(c);
        }

        if (c == 'R') {
          i = 0;
          digitalWrite(RPin, HIGH);
          digitalWrite(YPin, LOW);
          digitalWrite(GPin, LOW);
          delay(90);
        } else if (c == 'Y') {
          i = 0;
          digitalWrite(RPin, LOW);
          digitalWrite(YPin, HIGH);
          digitalWrite(GPin, LOW);
          delay(90);
        } else if (c == 'G') {
          i = 0;
          digitalWrite(RPin, LOW);
          digitalWrite(YPin, LOW);
          digitalWrite(GPin, HIGH);
          delay(90);
        } else {
          if (i < 30) {
           i++;
           delay(10);
          }
          if (i > 20) {
            digitalWrite(RPin, LOW);
            digitalWrite(YPin, LOW);
            digitalWrite(GPin, LOW);
            i = 0;
          }
        }

      }
      client.stop();
      if (i < 30) {
       i++;
       delay(10);
      }
      if (i > 20) {
        digitalWrite(RPin, LOW);
        digitalWrite(YPin, LOW);
        digitalWrite(GPin, LOW);
        i = 0;
      }

    }
    ESP.wdtFeed();

}
