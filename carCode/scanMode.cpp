#include "scanMode.h"
#include "standardFunctions.h"
#define UNRELIABLE 150

standardFunctions sf;

void scanMode::scan(standardFunctions standardFunc){
  sf=standardFunc;
  return;
//find can
// if can found, point at can, return
//else, drive for short time, try again
}

int findCan(){
  //Need to consider checking next value aswell if it isn't unknown (i.e. meeting the start of the loop) this gets really confusing.
  char meaning[24];
  int value[24];
  int consecutiveReadings=0;
  int beforeReadingValue;
  for(int i=0;i<24;i++){
    //Before starting, fill arrays up to say unknown.
    value[i]=-1;
    meaning[i]='U';
  }
  for(int i=0;i<24;i++){
    value[i]=sf.pingSensor(0);
    if(value[i]>UNRELIABLE){
      meaning[i]='N';
      switch (consecutiveReadings) {
        case 0:
          //Not an end of readings nothing interesting here.
          break;
        case 1:
            return i-1;
            break;
        case 2:
          //Need to look at what parameters will be needed.
          markPossibility();
          break;
      }
      consecutiveReadings=0;
      //wipeWall
    }else{
      value[i]='R';
      consecutiveReadings++;
      if(consecutiveReadings==3){
        //Form wall or return can
      }else if(consecutiveReadings>3){
        //check reading matches wall or return as can
      }
      //If there's been 4 now should probably do something clever like working out if it's a wall or
      //if one of them is a can
    }
    sf.turnSensor(15);
  }
  //Haven't found can yet so look at possibilities and walls and stuff
  //if you still have no idea return 25 let the above level move and call this again.
}

/*
 * Given the first position of 3 values which potentially could make
 * a wall or show a can. Will return the position of the can or -1
 * if all 3 form a wall.
 */
int findCanThreeReadings(){
  
}

/*
 * Given the angle from the car and distance from the car.
 * Gives array [x,y] with representative co-ordinate.
 */
double* getCoOrd(int angle,double magnitude){
  double* coOrd=(double*) malloc(2*sizeof(double));
  coOrd[0]=magnitude*sin(angle);
  coOrd[1]=magnitude*cos(angle);
  return coOrd;
}

/*
 * Given two co-oridnates gives equation of line:
 * y=mx+c in form [m,c]
 */
double* equationOfLine(int* coOrdOne,int* coOrdTwo){
  double* equation=(double*) malloc(2*sizeof(double));
  //m=(y2-y1)/(x2-x1)
  equation[0]=(coOrdOne[1]-coOrdTwo[1])/(coOrdOne[0]-coOrdTwo[0]);
  //c=y1-m*x1
  equation[1]=coOrdOne[1]-(equation[0]*coOrdOne[0]);
  return equation;
}


