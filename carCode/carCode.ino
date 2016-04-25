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

}


void loop() {
}
