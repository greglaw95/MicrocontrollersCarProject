//Header file that details the common functionality

#ifndef standardFunctions_h
#define standardFunctions_h

//#include <Servo.h>
#include <Arduino.h>


  
class standardFunctions{
public:
  int pingSensor(int pingID);
  void turnServo(int degrees);
  //void turnSensor(int degrees);
  void setupStandardFunctions();
  void turn(int direction);
  void drive(int direction);
};


#endif
