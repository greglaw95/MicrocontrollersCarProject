#include <Arduino.h>
#include "driveMode.h"
#include "scanMode.h"

#include "standardFunctions.h"

static standardFunctions sf;
driveMode dm;
scanMode s2m;

void setup() {
  Serial.begin(9600);
  s2m.scan(sf);
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
