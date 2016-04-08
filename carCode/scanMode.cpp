#include "scanMode.h"
#include "standardFunctions.h"

#define UNRELIABLE 150
#define ANGLEINTERVAL 15
#define LINETOLERANCE 10

static standardFunctions sf;

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
double* equationOfLine(double* coOrdOne,double* coOrdTwo){
  double* equation=(double*) malloc(2*sizeof(double));
  //m=(y2-y1)/(x2-x1)
  equation[0]=(coOrdOne[1]-coOrdTwo[1])/(coOrdOne[0]-coOrdTwo[0]);
  //c=y1-m*x1
  equation[1]=coOrdOne[1]-(equation[0]*coOrdOne[0]);
  return equation;
}

/*
 * Given the first position of 3 values which potentially could make
 * a wall or show a can, with a no reading on either side. Will return the position of the can or -1
 * if all 3 form a wall.
 */
int wallOrCan(int* values,int start){
  double* pointOne=getCoOrd(start*ANGLEINTERVAL,values[start]);
  double* pointTwo=getCoOrd((start+1)*ANGLEINTERVAL,values[start+1]);
  double* pointThree=getCoOrd((start+2)*ANGLEINTERVAL,values[start+2]);
  double* equationOneTwo = equationOfLine(pointOne,pointTwo);
  //Expected y = mx +c
  double pointThreeExpectedY = equationOneTwo[0]*pointThree[0]+equationOneTwo[1]; 
  double difference = pointThree[1]-pointThreeExpectedY;
  if(difference<1){
    difference=difference*-1;
  }
  if(difference<LINETOLERANCE){
    //It's a wall
    return -1;
  }
  double* equationOneThree = equationOfLine(pointOne,pointThree);  
  double* equationTwoThree = equationOfLine(pointTwo,pointThree);
  double origin[2] = {0,0};
  //TODO Problem here if start-1 is less than 0
  double* boundPointOne = getCoOrd((start-1)*ANGLEINTERVAL,UNRELIABLE);
  double* boundPointTwo= getCoOrd((start+4)*ANGLEINTERVAL,UNRELIABLE);
  double* boundingLineOne = equationOfLine(origin,
 }

/*
 * Mark a possibility if there's two readings in a row.
 */
void markPossibility(){
  return;
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
        case 3:
          //Mark all as wall or head for can
          break;
      }
      consecutiveReadings=0;
      //wipeWall
    }else{
      value[i]='R';
      consecutiveReadings++;
      if(consecutiveReadings==4){
        //Form wall or return can
      }else if(consecutiveReadings>4){
        //check reading matches wall or return as can
      }
    }
    sf.turnSensor(ANGLEINTERVAL);
  }
  //Haven't found can yet so look at possibilities and walls and stuff
  //if you still have no idea return 25 let the above level move and call this again.
}

void scanMode::scan(standardFunctions standardFunc){
  sf=standardFunc;
  findCan();
  return;
//find can
// if can found, point at can, return
//else, drive for short time, try again
}



