#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include "driveMode.h"

#include "startMode.h"
#include "standardFunctions.h"
#include "scanMode.h"

static standardFunctions sf;
driveMode dm;
startMode sm;
scanMode s2m;

void setup() {
  Serial.begin(9600);
  Serial.print("start");
  sf.setupStandardFunctions();
  int dir = sm.start();
}


void loop() {
  dm.drive(1);
  s2m.scan(sf);
}
