#include <SoftwareSerial.h>
/* Create object named bt of the class SoftwareSerial */
SoftwareSerial GPS_SoftSerial(10, 11);/* (Rx, Tx) */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); /* Define baud rate for serial communication */
  GPS_SoftSerial.begin(9600);
}

void loop() {
  while(Serial.available())
  {
    GPS_SoftSerial.write(Serial.read());
  }
  while(GPS_SoftSerial.available())
  {
    Serial.write(GPS_SoftSerial.read());
  }

}
