/**
 * Code on car startup
 * checkDir chooses direction to turn
 * wallScan pings the sensor off the wall
 * Start moves car + constantly calls these mehtods to keep fairly straight
 * ^ takes variances in wall distance into account
 */

 #include "startMode.h"
 #include "standardFunctions.h"

//starting distance as global var
 int initdist;
 

 int checkDir(int currdist){
  
  int chosendir = 0;
  int CminI = currdist-initdist;


  if (CminI >= -3 && CminI <= 3){
    //go straight
    chosendir = 0;
  }
  if (CminI>3 && CminI<=30){
    //turn right
    chosendir = 1;
  }     
  if (CminI<-3 && CminI>=-30){
    //turn left
    chosendir = -1;
  }
  else if (CminI<-30 || CminI>30){
    //change to new distance
    initdist=currdist;
    chosendir=0;
  }
  
  return chosendir;
 }

 int wallScan(standardFunctions sf){

  //pingval = ping the sensor and return the value
  int pingval = sf.pingSensor(1);

  return pingval;
 }

 
 void start(standardFunctions sf){

  int distance;
  int direct;

  //look ping sensor to right
  sf.turnSensor(90);

  //check the initial distance before moving
  int initdist = wallScan(sf);
  
  //start the car moving for this section
  sf.drive(1);
  //set as for loop and loop for a long time until distance reached

  for (int i=0;i<1000000;i++){
    sf.turn(0);
    distance = wallScan(sf);
    direct = checkDir(distance);
    sf.turn(direct);
  }

  sf.drive(0);
 }

