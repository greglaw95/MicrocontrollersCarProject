#include <Arduino.h>
#include "driveMode.h"
#include "startMode.h"
#include "standardFunctions.h"

standardFunctions sf;
driveMode dm;
startMode sm;

void setup() {
  Serial.begin(9600);
  Serial.print("start");
  sf.setupStandardFunctions();
  sm.start();
  //sf.turnServo(98);
  sf.drive(0);
}

void loop() {
  //dm.drive();
}
