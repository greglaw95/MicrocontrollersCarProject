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

 static standardFunctions sf;

//starting distance as global var
 int initdist;

 int startMode::checkDir(int currdist){
  
  int chosendir = 0;
  int CminI = currdist - initdist;

  Serial.println("currdist: "); Serial.print(currdist);
  Serial.println("initdist: "); Serial.print(initdist);
  Serial.println("CminI: "); Serial.print(CminI);


  if (CminI == -initdist){
    //go straight
    chosendir = 0;
  } else if (CminI >= -5 && CminI <= 4){
    //go straight
    chosendir = 0;
  } else if (CminI>4 && CminI<=30){
    //turn right
    chosendir = 1;
  } else if (CminI<-5 && CminI>=-30){
    //turn left
    chosendir = -1;
  } else if (CminI<-30 || CminI>30){
    //change to new distance
    initdist=currdist;
    chosendir = 0;
  }
  
  return chosendir;
 }

 int startMode::wallScan(){

  //pingval = ping the sensor and return the value
  int pingval = sf.pingSensor(0);

  return pingval;
 }

 
 void startMode::start(){

  int distance;
  int direct;

  sf.turnServo(180); //look ping sensor to right

  initdist = wallScan(); //check the initial distance before moving

  //make sure that the init dist is actually set
  while(initdist == 0){
    sf.drive(1);
    delay(100);
    sf.drive(0);
    initdist = wallScan();
  }

  
  
  sf.drive(1); //start the car moving for this section
  
  //set a for loop and loop for a long time until distance reached
  for (int i=0;i<20;i++){
    sf.turn(0);
    distance = wallScan();
    direct = checkDir(distance);
    sf.turn(direct);
   // Serial.println(distance);
   // Serial.println(direct);
    delay(500);
  }

  sf.drive(0);
 }

