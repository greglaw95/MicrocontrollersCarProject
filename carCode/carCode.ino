#include <Arduino.h>
#include "driveMode.h"

#include "standardFunctions.h"

static standardFunctions sf;
driveMode dm;

void setup() {
  Serial.begin(9600);
  //sf.setupStandardFunctions();
  //dm.drive();
  //dm.returnone();
}

void loop() {
 // sf.turnSensor(25);
 //Serial.println(sf.pingSensor(0));
 //Serial.print(" ");
 //Serial.print(sf.pingSensor(1));
}
