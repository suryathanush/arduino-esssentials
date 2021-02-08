#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/* Create object named bt of the class SoftwareSerial */
SoftwareSerial GPS_SoftSerial(10, 11);/* (Rx, Tx) */
/* Create an object named gps of the class TinyGPSPlus */
TinyGPSPlus gps;      

volatile float minutes, seconds;
volatile int degree, secs, mins;
double lat_val=0, lng_val=0;

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  GPS_SoftSerial.begin(9600); /* Define baud rate for software serial communication */
}

void loop() {
        smartDelay(1000); /* Generate precise delay of 1ms */
        unsigned long start;
        bool loc_valid;
        lat_val = gps.location.lat(); /* Get latitude data */
        loc_valid = gps.location.isValid(); /* Check if valid location data is available */
        lng_val = gps.location.lng(); /* Get longtitude data */
        if (!loc_valid)
        {          
          Serial.print(lat_val);
          Serial.println("***");
          Serial.print(lng_val);
          Serial.println("***");
        }
        else
        {
          Serial.print("Latitude : ");
          Serial.println(lat_val, 6);
          Serial.print("Longitude  : ");
          Serial.println(lng_val, 6);
        }
        lat_val = 0;
        lng_val = 0;
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (GPS_SoftSerial.available())  /* Encode data read from GPS while data is available on serial port */
      gps.encode(GPS_SoftSerial.read());
/* Encode basically is used to parse the string received by the GPS and to store it in a buffer so that information can be extracted from it */
  } while (millis() - start < ms);
}
