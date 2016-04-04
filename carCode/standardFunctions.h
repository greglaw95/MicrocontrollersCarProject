//Header file that details the common functionality

#ifndef standardFunctions_h
#define standardFunctions_h

#include <Arduino.h>


	
class standardFunctions{
public:
	int pingSensor(int pingID);
  void turnSensor(int degrees);
  void setupStandardFunctions();
};

#endif
