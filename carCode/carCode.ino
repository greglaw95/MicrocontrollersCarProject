#include <Arduino.h>
#include "driveMode.h"

#include "standardFunctions.h"

standardFunctions sf;
driveMode dm;

void setup() {
  Serial.begin(9600);
  /*sf.setupStandardFunctions();
  sf.drive(1);
  delay(100);
  sf.turn(-1);
  delay(300);
  sf.turn(1);
  delay(300);
  sf.turn(-1); //turn back left after right to centre
  sf.turn(0);
  delay(100);
  sf.drive(0);
  delay(200);
  sf.drive(-1);
  delay(100);
  sf.turn(-1);
  delay(300);
  sf.turn(1);
  delay(300);
  sf.turn(-1); //turn back left after right to centre
  sf.turn(0);
  delay(100);
  sf.drive(0);*/
  
 sf.pingSensor(0);
}

void loop() {
 //sf.turnSensor(25);
// Serial.println(sf.pingSensor(0));
// Serial.print(" ");
// Serial.print(sf.pingSensor(1));
}
