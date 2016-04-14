#include <Arduino.h>
#include "driveMode.h"

#include "standardFunctions.h"

standardFunctions sf;
driveMode dm;

void setup() {
  Serial.begin(9600);
  sf.setupStandardFunctions();
  sf.drive(0);
  sf.turn(0);
  //sf.turnSensor(360);
  /*
  delay(1500);
  sf.turn(1);
  delay(1500);
  sf.turn(0);
  
  sf.drive(1);
  delay(1500);
  sf.drive(0);
  delay(350);
  sf.drive(-1);
  delay(1500);
  sf.drive(0);
  */
}

void loop() {
  Serial.print(sf.pingSensor(0));
}
