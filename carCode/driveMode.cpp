#include "driveMode.h"
#include "standardFunctions.h"
static standardFunctions sf;


//0 turn left
//1 go straight
//2 turn right

void driveMode::drive(){
  sf.turnServo(97);
  sf.drive(1);
  /*hit can? change mode?
  if(distance0<5 && distance1<5){
    sf.drive(0);
    sf.turn(0);
    return;
  }*/
   long diff=0;
   int distance0,distance1=0;
 do{
 
    distance0=sf.pingSensor(0);
    distance1=sf.pingSensor(1);
    
    diff = abs(distance0-distance1);
    //Serial.println();
    /*Serial.print("Dist0  ");
    Serial.print(distance0);
    Serial.print("   Dist1   ");
    Serial.print(distance1);*/
    Serial.println();
    Serial.print("diff  ");
    Serial.print(diff);
    Serial.println();
    delay(1000);
  /*while there isn't a can on our nose*/
    if(diff<5 && diff>=0){
     //both can see therefore go straight
     Serial.print("  straight  ");
     sf.turn(0);
    }else if(distance0<distance1){
     //turn motor to go left
     sf.turn(-1);
     Serial.print("  left  ");
     delay(50);
    }else if(distance1<distance0){
      //turn right
      Serial.print("  right  ");
     sf.turn(1);
     delay(90);
    }
    Serial.println();
   }
   while(distance0>5 && distance1>5);
  
  sf.drive(0);
}

int driveMode::returnone(){
  return 1;
}
