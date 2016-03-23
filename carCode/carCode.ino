#include <Arduino.h>
#include "driveMode.h"

#include "standardFunctions.h"

standardFunctions sf;
driveMode dm;

void setup() {
  Serial.begin(9600);
  sf.setupStandardFunctions();
  //dm.drive();
  //dm.returnone();
}

void loop() {
 Serial.println(sf.pingSensor(0));
 Serial.print(" ");
 Serial.print(sf.pingSensor(1));
}
