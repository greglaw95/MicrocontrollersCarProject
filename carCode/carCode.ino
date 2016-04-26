#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include "driveMode.h"

#include "startMode.h"
#include "standardFunctions.h"

static standardFunctions sf;
driveMode dm;
startMode sm;

void setup() {
  Serial.begin(9600);
  Serial.print("start");
  sf.setupStandardFunctions();
  //int dir = sm.start();
  dm.drive(1);
  //dm.drive(1);
  /*sf.drive(1);
  sf.turn(-1);
  delay(3700);
  sf.drive(0);
  sf.turn(0);
  */
  
  
}


void loop() {
}
