#include "driveMode.h"
#include "standardFunctions.h"
static standardFunctions sf;


//0 turn left
//1 go straight
//2 turn right

void driveMode::drive(){
  sf.pingSensor(0);
}

int driveMode::returnone(){
  return 1;
}
