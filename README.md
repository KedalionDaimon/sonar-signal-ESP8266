# sonar-signal-ESP8266
One ESP module signalling distance to another, which in response lights up a traffic lights module.

Two ESP8266 Wemos D1 mini modules, A and B, connect to each other, where the one detects a disturbance in the ultrasonic  HC-SR04 sensor of the other and signals correspondingly a traffic lights module, with green being nothing close, yellow something being closer and red something being really close.

Wiring:


Sonar detector to ESP866

VCC : 5V

TRIG : D6

ECHO : D5

GND : G



Traffic lights to ESP8266

GND : G

R : D7

Y : D6

G : D5
