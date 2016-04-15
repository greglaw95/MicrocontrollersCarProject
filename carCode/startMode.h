//Header file for the car's initial phase

#ifndef startMode_h
#define startMode_h

#include <Arduino.h>
#include "standardFunctions.h"


class startMode{
  private:
    int checkDir(int currDist);
    int wallScan();
  public:
    void start();
};

#endif
