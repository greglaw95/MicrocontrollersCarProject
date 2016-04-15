#include "driveMode.h"
#include "standardFunctions.h"
static standardFunctions sf;



//0 turn left
//1 go straight
//2 turn right

void driveMode::drive(){

  byte s;
  byte r;
  byte l;
  int distance0,distance1=0;
  int wall;
  
  distance1=sf.pingSensor(1);
  distance0=sf.pingSensor(0);

  long diff=0;
  diff = abs(distance0-distance1);

  if(diff<5 && diff>=0){
    //both can see therefore go straight
    s++;
  }else if(distance0<distance1){
    //turn motor to go left
    r++;
  }else if(distance1<distance0){
    l++;
  }

  if(l==3){
    l=0;
    Serial.print("go left");
  }
  if(r==3){
    r=0;
    Serial.print("go right");
  }
  if(s==3){
    s=0;
    Serial.print("go straight");
  }

  /*If banging against wall for some amount of time*/
  if(distance0<5 && distance1<5){
    wall++;
  } 
  if(wall==10){
    Serial.print("Dats a wall"); //
    wall=0;
  }
   
}

int driveMode::returnone(){
  return 1;
}
