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
  dm.drive(-1);
 
  
/*
  sf.turn(1);
  delay(2000);
  sf.turn(-1);
  delay(2000);
  sf.turn(0);
*/
  /*
  sf.turnServo(0);
  delay(3000);
  sf.turnServo(90);
  delay(3000);
  sf.turnServo(180);
  delay(3000);
  sf.turnServo(90);
  */

  /*
  sf.drive(1);
  delay(1000);
  sf.turn(-1);
  delay(300);
  sf.turn(1);
  delay(300);
  sf.turn(-1); //turn back left after right to centre
  sf.turn(0);
  delay(100);
  sf.drive(0);
  sf.turn(0);

  sf.turnServo(0);
  delay(750);
  sf.turnServo(45);
  delay(750);
  sf.turnServo(90);
  delay(750);
  sf.turnServo(135);
  delay(750);
  sf.turnServo(180);
  
  sf.pingSensor(0);
  */
  //sf.pingSensor(0); 
  //Serial.print(sf.pingSensor(0));
}


void loop() {
}
