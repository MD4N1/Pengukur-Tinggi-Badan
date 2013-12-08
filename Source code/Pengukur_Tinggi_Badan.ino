#include <Arduino.h>
#include "LedControl.h"
#include <NewPing.h>

#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 204 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 13 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 12 is connected to LOAD
 We have only a single MAX72XX.
 */
LedControl myled = LedControl(13,11,12,1);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

unsigned int jarak, tinggi;
byte satuan, puluhan, ratusan;

void setup()
{
  myled.shutdown(0,false);
  /* Set the brightness to a medium values */
  myled.setIntensity(0,8);
  /* and clear the display */
  myled.clearDisplay(0);

}

void loop()
{
   unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
   jarak = uS/US_ROUNDTRIP_CM;
   tinggi = 204 - jarak;
   ratusan = tinggi /100;
   puluhan = (tinggi % 100)/10;
   satuan = (tinggi % 100)%10;
   delay(1000);
   myled.setChar(0,0,satuan,false);
   myled.setChar(0,1,puluhan,false);
   myled.setChar(0,2,ratusan,true);
   delay(10);

}
