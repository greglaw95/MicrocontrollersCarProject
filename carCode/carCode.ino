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
  /*
  Serial.begin(9600);
  sf.setupStandardFunctions();
  sf.drive(0);
  sf.turn(0);
  //sf.turnSensor(360);
    sf.turnSensor(360);
    delay(900);
    sf.turnSensor(-360);

/*
 for(int i=0; i<6; i++){
    sf.turnSensor(15);
    delay(400);
  }
  
  for(int i=0; i<6; i++){
    sf.turnSensor(-15);
    delay(400);
  }*/
  
}

void loop() {
  //Serial.print(sf.pingSensor(0));
  
}
