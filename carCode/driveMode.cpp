#include "driveMode.h"
#include "standardFunctions.h"
static standardFunctions sf;

//-1 turn left
//0 go straight
//1 turn right

#define turnAfterHittingWall 3000 
#define turnAfterHittingCan 2500

void driveMode::drive(int directionToTurnAfterHitting){
  int canclose=0;
  int wall=0;
  sf.turn(0);
  /*hit can? change mode?
  if(distance0<5 && distance1<5){
    sf.drive(0);
    sf.turn(0);
    return;
  }*/
  sf.turnServo(105);
  sf.drive(1);
  
   long diff=0;
   int distance0,distance1=0;
 do{
 
    distance0=sf.pingSensor(0);
    distance1=sf.pingSensor(1);
    if(distance0>5&&distance1>5&&((distance0<90||distance0>250)&&(distance1<90||distance1>250))){
    //distance1=distance1-3;
    /*
    if(distance0<4 && distance1<4){
      wall++;
    }else{
      wall=0;
    }
    if(wall==4){
      Serial.print("wall");
      //sf.turn(directionToTurnAfterHitting*-1); //left or right?
      //delay(turnAfterHittingWall);
      return;
    }*/
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
    //delay(1000);
  /*while there isn't a can on our nose*/
    if(diff<20 && diff>=0){
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
      delay(200);
      sf.turn(0);
    }
    
    if(distance0<15 && distance1<15){
      //can is close?
      canclose=1;
    }
    if(distance0>40 && distance1>40 && canclose==1){
      Serial.println("cancanasdas");
      break;
      canclose=0;
      //sf.turn(directionToTurnAfterHitting*-1);
      //delay(turnAfterHittingCan);
      
    }
    
    Serial.println();
   }
 }
   while(distance0!=1 && distance1!=1);
   //while(1); //hit a can or a wall
    Serial.print("end");
   /*We've hit something, check what it is by seeing if the
    * ping values change. Non moving, low values = wall.
    * Higher values after the low values that broke it out 
    * of this loop = Probably a can
    */
    /*
    Serial.println();
    Serial.print("distance0  ");
    Serial.print(distance0);
    Serial.print("distance1  ");
    Serial.print(distance1);
    Serial.println();
    int previousdist0=sf.pingSensor(0);
    int previousdist1=sf.pingSensor(1);
    distance0=sf.pingSensor(0);
    distance1=sf.pingSensor(1);
    int wall=0;
    Serial.print("prevdistance0  ");
    Serial.print(previousdist0);
    Serial.print("previousdist1  ");
    Serial.print(previousdist1);
    Serial.println();
    while(distance0==previousdist0 && distance1==previousdist1){
        if(wall==5){
          //defo a wall
          //do wall stuff
          Serial.println("wall");
          //sf.turn(-1);
          //delay(3000);
          return;
        }
        previousdist0=distance0;
        previousdist1=distance1;
        distance0=sf.pingSensor(0);
        distance1=sf.pingSensor(1);
        wall++;
    }

    if(wall<5){
      //a can
      Serial.println("can");
    }

    
    /*
    if(distance0<5 && distance1<5){ //we are face first into a wall
        distance0=sf.pingSensor(0);
        distance1=sf.pingSensor(1);
       while(distance0<5 && distance1<5){
          if(directionToTurnAfterHittingCan==-1)
            sf.turn(1);
          }else{
            sf.turn(-1);
          }
          distance0=sf.pingSensor(0);
          distance1=sf.pingSensor(1);
       }
     //or instead of a while have a turn for certain time    
     }
     if(distance0<5 || distance1<5){ //just hit a can 
      
     }
  

    //while(no cans)
     //put this code in carCode
    scanMode(); //see any cans?
    //startMode(2); // no, drive for 2m
    scanMode();
    startMode(2);
    //...
    //driven too far
    //turn the 90o in the opposite direction to the wall
    //eg. if wall is one left, turn right
    //scanMode();
    //startMode(2);
    */
    sf.drive(0);

}
