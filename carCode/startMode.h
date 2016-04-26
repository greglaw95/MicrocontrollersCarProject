//Header file for the car's initial phase

#ifndef startMode_h
#define startMode_h

#include <Arduino.h>
#include "standardFunctions.h"


class startMode{
  private:
    int checkDirAndTurn(int currDist);
    int wallScan();
    void endLoop();
  public:
    int start();
};

#endif
