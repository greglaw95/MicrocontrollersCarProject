//Header file for the car's initial phase

#ifndef startMode_h
#define startMode_h

#include <Arduino.h>
#include "standardFunctions.h"


class startMode{
  private:
    int checkDir(int currDist);
    int wallScan(standardFunctions sf);
  public:
    void start(standardFunctions sf);
};

#endif
