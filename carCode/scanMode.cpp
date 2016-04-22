#include "scanMode.h"
#include "standardFunctions.h"

#define UNRELIABLE 150
#define ANGLEINTERVAL 15
#define LINETOLERANCE 10
#define READINGS 12

static standardFunctions sf;

//Turn the car to point in a certain direction
void pointAt(int direction){
  if(direction==6){
    return;
  }
  if(direction>6&&direction<18){
    sf.turn(1);
  }else{
    sf.turn(0);
  }
  //Need to work out how long to drive for each one
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
 * a wall or show a can. Returns -1 if it's all a wall or -2 if one
 * of them is a can.
 */
int wallOrCan(int* values,int start){
  double* pointOne=getCoOrd(start*ANGLEINTERVAL,values[start]);
  double* pointTwo=getCoOrd((start+1)*ANGLEINTERVAL,values[start+1]);
  double* pointThree=getCoOrd((start+2)*ANGLEINTERVAL,values[start+2]);
  double* equationOneTwo = equationOfLine(pointOne,pointTwo);
  //Expected y = mx +c
  if(checkMatchesWall(pointThree,equationOneTwo)==-1){
	  //It's a wall
	  return -1;
  }else{
	  //There's a can there somewhere get closer look again.
	  pointAt(start+1);
	  return -2;
  }
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
		 //Need combination of 3 points so lowest point can only be 1 or 2
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
   answer[1]=666;
   return answer;
 }


int findCan(){
  //Need to consider checking next value aswell if it isn't unknown (i.e. meeting the start of the loop) this gets really confusing.
  int currentAngle=0;
  int hadNoReading=0;
  int possibility=-1;
  int value[READINGS];
  double* wall;
  double* result;
  int consecutiveReadings=0;
  int beforeReadingValue;
  for(int i=0;i<READINGS;i++){
    value[i]=sf.pingSensor(0);
    if(value[i]==0){
      //No reading
      if(hadNoReading==1){
        possibility=i;
      }else{
        switch (consecutiveReadings) {
          case 0:
            //Not an end of readings nothing interesting here.
            break;
          case 1:
            //Found can
            return i-1;
            break;
          case 2:
            //Need to look at what parameters will be needed.
            possibility=i-1;
            break;
          case 3:
            int tempValue=wallOrCan(value,i-3);
            if(tempValue!=-1){
              //not a wall
              return tempValue;
            }
            break;
          }
      }
      consecutiveReadings=0;
      hadNoReading=1;
    }else{
      consecutiveReadings++;
      if(consecutiveReadings==4){
        //Form wall or return can
		    result = formWallOrFindCan(value,i-3);
		    if (result[1]==666){
			    //Error just move on.
			    consecutiveReadings=0;
		    }else{
			    if(result[1]==0){
				    return result[0];
			    }else{
				    wall=result;
			    }
		    }
      }else if(consecutiveReadings>4){
        //check reading matches wall or return as can
		    if(checkMatchesWall(getCoOrd(i*ANGLEINTERVAL,value[i]),wall)!=1){
			    //If the next one doesn't match the wall it's a can go for it.
			    return i;
		    }
      }
    }
    currentAngle+=ANGLEINTERVAL;
    sf.turnSensor(currentAngle);
  }
  return possibility;
}

void scanMode::scan(standardFunctions standardFunc){
  sf=standardFunc;
  int result=findCan();
  if(result==-1){
    //Didn't find can turn 180
    pointAt(18);
    return scan(sf);
  }else if(result==-2){
    //Edge towards can check again
    sf.drive(1);
    delay(250);
    sf.drive(0);
    return scan(sf);
  }else{
    pointAt(result);
    return;
  }
}

/**
 * If we have time:
 * Improve what happens if we don't find can
 * Possible miniscan?
 */



