//Header file for the car's initial phase

#ifndef startMode_h
#define startMode_h

#include <Arduino.h>


class startMode{
  private:
    int compareSides(int r1, int r2, int l1, int l2);
    int wallScan();
  public:
    void start();
}

#endif
