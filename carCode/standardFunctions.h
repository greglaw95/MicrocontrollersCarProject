//Header file that details the common functionality

#ifndef standardFunctions_h
#define standardFunctions_h

#include <Servo.h>
#include <Arduino.h>


	
class standardFunctions{
public:
	int pingSensor(int pingID);
  void turnServo(int degrees);
  //void turnSensor(int degrees);
  void setupStandardFunctions();
<<<<<<< HEAD
  int demo();
};

//standardFunctions sf;
=======
  void turn(int direction);
  void drive(int direction);
//  void turnServo(int degrees);
};

>>>>>>> a777f3ef0340e91e888fb088a045162834844170

#endif
