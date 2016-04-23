#include "driveMode.h"
#include "standardFunctions.h"
static standardFunctions sf;

//0 turn left
//1 go straight
//2 turn right

void driveMode::drive(){

  sf.turnServo(98);
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
    
    diff = abs(distance0-(distance1+3));
    //Serial.println();
    /*Serial.print("Dist0  ");
    Serial.print(distance0);
    Serial.print("   Dist1   ");
    Serial.print(distance1);*/
    Serial.println();
    Serial.print("diff  ");
    Serial.print(diff);
    Serial.println();
    //delay(1000);
  /*while there isn't a can on our nose*/
    if(diff<10 && diff>=0){
     //both can see therefore go straight
     Serial.print("  straight  ");
     sf.turn(0);
     sf.drive(1);
    }else if(distance0<distance1){
     //turn motor to go left
      sf.drive(1);
      sf.turn(1);
      Serial.print("  right   ");
    }else if(distance1<distance0){
      //turn right
      Serial.print("  left  ");
      sf.turn(-1);
      sf.drive(1);
    }
    Serial.println();
   }
   while(distance0!=1 && distance1!=1);
     /*We've hit something, check what it is by seeing if the 
    * ping values change. Non moving, low values = wall.
    * Higher values after the low values that broke it out 
    * of this loop. Probably a can
    */
  sf.drive(0);
}

