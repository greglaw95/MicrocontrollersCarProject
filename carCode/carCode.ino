#include <Arduino.h>
#include "driveMode.h"
#include "startMode.h"
#include "standardFunctions.h"

standardFunctions sf;
//driveMode dm;
startMode sm;
  


void setup() {

  sf.setupStandardFunctions();
  //sf.turnSensor(-90);
  //sm.start();
  //sf.turn(1);

  sf.turnServo(0);
  delay(3000);
  sf.turnServo(90);
  delay(3000);
  sf.turnServo(180);
  delay(3000);
  sf.turnServo(90);

//sf.turnSensor(-15);
  
  Serial.begin(9600);
  sf.setupStandardFunctions();
  /*
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
  sf.turn(0);
*/
  
 sf.pingSensor(0);
}

void loop() {
  //Serial.print(sf.pingSensor(0));
  //sf.turnSensor(25);
  // Serial.println(sf.pingSensor(0));
  // Serial.print(" ");
  // Serial.print(sf.pingSensor(1));
}
