
#define echoPin 14 // ESP32 Wrover 16 // 14 ESP8266 D6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 12 // ESP32 Wrover 17 // 12 ESP8266 D5 // attach pin D3 Arduino to pin Trig of HC-SR04
#define INTERMEASURE 10

#define REDDISTANCE 20
#define YELLOWDISTANCE 30

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
// #include <ESP8266WiFi.h>
// #include "WiFi.h"

int dist = 0;
char c = 0;

int i = 0;

int distance;
long duration;

unsigned int recmin = 0;
int dist1 = 0;
int dist2 = 0;
int dist3 = 0;
int dist4 = 0;
int dist5 = 0;

WiFiServer wifiServer(8023);
WiFiClient client = wifiServer.available();

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  //Serial.begin(115200); // // 9600 baudrate speed
  //Serial.println("Ultrasonic Sensor"); // print some text in Serial Monitor

  
  WiFi.softAP("OnePingOnlyZ", "GiveMeAPingVassily");
  // WiFi.softAP("OnePingOnlyZ", "GiveMeAPingVassily", 1, 1); // channel & hidden SSID
  delay(500);
  wifiServer.begin();
  //Serial.print(" Net:OnePingOnlyZ Password:GiveMeAPingVassily");
  //Serial.print(" IP:");
  //Serial.print(WiFi.softAPIP());
  //Serial.println(" Port:8023");
}



void loop() {

    for (i = 0; i < 5; i++) {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2; 
      //Serial.print("dist1=");
      //Serial.print(dist1);
      //Serial.print("   dist2=");
      //Serial.print(dist2);
      //Serial.print("   dist3=");
      //Serial.print(dist3);
      //Serial.print("   dist4=");
      //Serial.print(dist4);
      //Serial.print("   dist5=");
      //Serial.print(dist5);
      //Serial.print("   h=");
      //Serial.print(hhhhhh);
      //Serial.print(" m=");
      //Serial.print(mm);
      //Serial.print(" s=");
      //Serial.print(ss);
      //Serial.print("   recmin=");
      //Serial.println(recmin);

      dist5 = dist4;
      dist4 = dist3;
      dist3 = dist2;
      dist2 = dist1;
      dist1 = distance;
      delay(INTERMEASURE);
    }


    distance = (dist1 + dist2 + dist3 + dist4 + dist5) / 5;
    dist1 = 0;
    dist2 = 0;
    dist3 = 0;
    dist4 = 0;
    dist5 = 0;

    if (distance < REDDISTANCE) {
      c = 'R';
    } else if (distance < YELLOWDISTANCE) {
      c = 'Y';
    } else {
      c = 'G';
    }

    client = wifiServer.available();
    if (client) {
      while (client.connected()) {
      client.print(c);
      c = 0;
      break;
    }}
    client.stop();
    ESP.wdtFeed();
    delay(100);
}
