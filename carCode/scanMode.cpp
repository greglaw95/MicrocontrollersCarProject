#include "scanMode.h"
#include "standardFunctions.h"

#define UNRELIABLE 100
#define ANGLEINTERVAL 30
#define LINETOLERANCE 80
#define READINGS 7

#define QUARTERTURN 1000

#define pingReliable 0

static standardFunctions sf;

//Turn the car to point in a certain direction
void pointAt(int direction){
  Serial.print("Pointing at ");
  Serial.print(direction*ANGLEINTERVAL);
  Serial.print("\n");
  sf.turnServo(direction*ANGLEINTERVAL);
  delay(2000);
  if(direction==6){
    return;
  }
  if(direction<4){
    sf.turn(-1);
    sf.drive(1);
    delay(500);
  }else if(direction<8){
    //Straightish
  }else if(direction<13){
    sf.turn(1);
    sf.drive(1);
    delay(1000);
  }else{
    sf.turn(-1);
    delay(3700);
  }
  sf.turn(0);
  sf.drive(0);
}

/*
 * Given the angle from the car and distance from the car.
 * Gives array [x,y] with car as 0,0
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
  * Returns 1 if it matches, -1 otherwise
 */
 int checkMatchesWall(double* point,double* wall){
  double expectedY = wall[0]*point[0]+wall[1]; 
  double difference = point[1]-expectedY;
  if(difference<1){
    difference=difference*-1;
  }
  if(difference<LINETOLERANCE){
    //It's a wall
    return 1;
  }else{
    //It's not a wall
    return -1;
  }
 }

/*
 * Given the first position of 3 values which potentially could make
 * a wall or show a can. Returns -1 if it's all a wall or 1 if one
 * of them is a can.
 */
int canPresent(int* values,int start){
  double* pointOne=getCoOrd(start*ANGLEINTERVAL,values[start]);
  double* pointTwo=getCoOrd((start+1)*ANGLEINTERVAL,values[start+1]);
  double* pointThree=getCoOrd((start+2)*ANGLEINTERVAL,values[start+2]);
  double* equationOneTwo = equationOfLine(pointOne,pointTwo);
  //Expected y = mx +c
  if(checkMatchesWall(pointThree,equationOneTwo)==-1){
    //It's a wall
    return -1;
  }
  //There's a can there somewhere
  return 1;
 }
 
 /*
 
 */
 double* formWallOrFindCan(int* values,int start){
   double* points[4];
   double* potentialLine;
   double* answer=(double*) malloc(2*sizeof(double));
   double expectedY;
   double difference;
   for(int a=0;a<4;a++){
    points[a]=getCoOrd((start+a)*ANGLEINTERVAL,values[(start+a)]);
   }
   for(int i=0;i<2;i++){     
     //Gives point one
     //Need combination of 3 points and only have 4 so lowest point can only be 1 or 2
     for(int j=i+1;j<3;j++){
       //Gives point two
       //Needs at least one more point after it so can only be 3 at max
       potentialLine=equationOfLine(points[i],points[j]);
       for(int k=j+1;k<4;k++){
        //Gives third point
        //has to be 4th at max because we're looking at 4 values
        //y=mx+c
        if(checkMatchesWall(points[k],potentialLine)==-1){
          //It's a wall
          if(k==3){
            //The first 3 made a wall look at the fourth
            if(checkMatchesWall(points[4],potentialLine)){
              //All of them make a wall
              return potentialLine;
            }else{
              //The last one doesn't match the wall it's a can
              answer[0]=start+3;
              answer[1]=0;
              return answer;
            }
          }else{
            //3 of 4 made a wall need to find out which wasn't used it'll be a can.
            if(j==2){
              //The second value in the wall was the second point and
              //the third point in wall was the fourth point. So the third
              //point doesn't match the wall it must be a can, return it.
              answer[0]=start+2;
              answer[1]=0;
              return answer;
            }else{
              if(i==2){
                //The second and third points of the wall were the third and fourth points given
                //So whatever one out of 1 and 2 wasn't the first point must be the can.
                answer[0]=start;
                answer[1]=0;
                return answer;
              }else{
                answer[0]=start+1;
                answer[1]=0;
                return answer;
              }
            }
          }
        }
       }
     }
       
   }
   
   answer[0]=666;
   answer[1]=0;
   return answer;
 }


int faceCan(){
  //Need to consider checking next value aswell if it isn't unknown (i.e. meeting the start of the loop) this gets really confusing.
  Serial.print("Facing 0 \n");
  int currentAngle=0;
  int hadNoReading=0;
  int possibility=-1;
  int value[READINGS];
  double* wall;
  double* result;
  int consecutiveReadings=0;
  int beforeReadingValue;
  sf.turnServo(currentAngle);
  delay(1000);
  for(int i=0;i<READINGS;i++){
    value[i]=sf.pingSensor(0);
    Serial.print("Value ");
    Serial.print(value[i]);
    Serial.print("\n");
    if(value[i]>UNRELIABLE){
      Serial.print("No Reading\n");
      //No reading
      if(hadNoReading==0){
        if(consecutiveReadings==1){
          pointAt(i);
          return 1;
        }
      }else{
        switch (consecutiveReadings) {
          case 0:
            //Not an end of readings nothing interesting here.
            break;
          case 1:
            //Found can
            pointAt(i-1);
            return 1;
            break;
          case 2:
            //Need to look at what parameters will be needed.
            pointAt(i-1);
            return 1;
            break; 
          }
      }
      consecutiveReadings=0;
      hadNoReading=1;
    }else{
      Serial.print("Reading\n");
      consecutiveReadings++;
    }
    currentAngle+=ANGLEINTERVAL;
    sf.turnServo(currentAngle);
    Serial.print("Facing ");
    Serial.print(currentAngle);
    Serial.print("\n");
    delay(500);
  }
  if(value[READINGS-2]>UNRELIABLE&&value[READINGS-1]<UNRELIABLE){
    pointAt(READINGS-1);
    return 1;
  }
  return -1;
}

void scanMode::scan(standardFunctions standardFunc){
  pointAt(18);
  Serial.begin(9600);
  Serial.print("Scanning\n");
  sf=standardFunc;
  int result=faceCan();
  Serial.print("Result");
  Serial.print(result);
  Serial.print("\n");
  if(result==-1){
    //Didn't find can decide what to do
    return scan(sf);
  }else{
    return;
  }
}

/**
 * If we have time:
 * Improve what happens if we don't find can
 * Possible miniscan?
 */
