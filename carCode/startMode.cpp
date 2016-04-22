/**
 * Code on car startup
 * checkDir chooses direction to turn:
 *    -3<=dist>=3 : straight
 *    -30<=dist<-3 : left
 *    3<dist<=30 : right
 *    beyond these, go straight and reassign init distance
 * wallScan pings the sensor off the wall
 * Start moves car + constantly calls these methods to keep fairly straight
 *    takes variances in wall distance into account through the reassignment in checkDir
 */

 #include "startMode.h"
 #include "standardFunctions.h"

 #define RIGHT 180
 #define LEFT 0
 #define STRAIGHT 98

 static standardFunctions sf;

//starting distance as global var
 int initdist;
 int lookdir; //-1=left;0=098;1=right

 int startMode::checkDirAndTurn(int currdist){
  
  int chosendir = 0;
  int CminI = currdist - initdist;
  int changed = 0;  //keep track of switched servo directions

/*
  Serial.println("currdist: "); Serial.print(currdist);
  Serial.println("initdist: "); Serial.print(initdist);
  Serial.println("CminI: "); Serial.print(CminI);
*/
  if(lookdir==-1){
    CminI*=-1;
  }
  if (CminI >= -10 && CminI <=10){
    //go straight
    chosendir = 0;
    sf.turn(chosendir);
    //delay(100);
  } else if (CminI>4 && CminI<=30){
    //turn right
    chosendir = 1;
    sf.turn(chosendir);
    delay(100);
    sf.turn(-1);
    delay(40);
    sf.turn(0);
  } else if (CminI<-5 && CminI>=-30){
    //turn left
    chosendir = -1;
    sf.turn(chosendir);
    delay(100);
    sf.turn(1);
    delay(40);
    sf.turn(0);
  }
  return chosendir;
 }

 int startMode::wallScan(){

  //pingval = ping the sensor and return the value
  int pingval;
  do{
    pingval = sf.pingSensor(0);
    if(pingval>200){
      sf.drive(0);
      Serial.print("Changing side");
      delay(1000);
      //change direction
      initdist=0;
      if(lookdir==1){
        lookdir=-1;
        sf.turnServo(LEFT);
      }else{
        lookdir=1;
        sf.turnServo(RIGHT);
      }
    }else{
      if(initdist==0){
        initdist=pingval;
      }
    }
  }while(pingval>200);
  sf.drive(1);
  return pingval;
 }
/*
void startMode::setUp(){
  initdist = wallScan(); //check the initial distance before moving

  int notfound = 0

  //make sure that the init dist is actually set
  while(initdist == 0 ){
    sf.drive(1);
    delay(100);
    sf.drive(0);
    initdist = wallScan();
  }
}
 */
 int startMode::start(){
  int distance;
  int direct;
  initdist=0;
  sf.turn(0);
  sf.turnServo(RIGHT); //look ping sensor to right
  lookdir=1;
  delay(1000);

 /*
  initdist = wallScan(); //check the initial distance before moving

  //make sure that the init dist is actually set
  while(initdist == 0){
    sf.drive(1);
    delay(100);
    sf.drive(0);
    initdist = wallScan();
  }
*/
  wallScan();
  
  sf.drive(1); //start the car moving for this section
  
  //set a for loop and loop for a long time until distance reached
  for (int i=0;i<100;i++){
    //sf.turn(0);
    distance = wallScan();
    checkDirAndTurn(distance);
  }

  sf.turnServo(STRAIGHT);
  sf.drive(0);
  return lookdir;
 }

