#include <Arduino.h>
#include "driveMode.h"
#include "startMode.h"
#include "standardFunctions.h"
#include "scanMode.h"

standardFunctions sf;
driveMode dm;
startMode sm;
scanMode s2m;
int dir;

void setup() {
  Serial.begin(9600);
  Serial.print("start");
  sf.setupStandardFunctions();
  dir = sm.start();
}


void loop() {
  dm.drive(dir);
  s2m.scan(sf);
}
