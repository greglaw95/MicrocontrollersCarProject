/**
 * Code on car startup
 */

 #include startMode.h

 int lavg;
 int ravg;

 bool compareSides(int r1, int r2, int l1, int l2){

  int retval = 1;
  
  //check right side
  if(r1 >= (r2-10) && r1 <= (r2+10)){
    ravg = (r1 * sin(45) + r2 * sin(45))/2;
  }
  else{
    ravg = -1;
  }

  //check left side
  if(l1 >= (l2-10) && l1 <= (l2+10)){
    lavg = (l1 * sin(45) + l2 * sin(45))/2;
  }
  else{
    lavg = -1;
  }

  //check averages
  if(lavg==-1 && ravg==-1)
    retval=1;
  if(lavg==-1 && ravg!=-1)
    retval=2; //use ravg
  if(lavg!=-1 && ravg==-1)
    retval=3; //use lavg
  if(lavg!=-1 && ravg!=-1){
    if (lavg>ravg)
      retval = 2;
    else
      retval = 3;
  }
  return retval;
 }

 int wallScan(){
  //int r1 = 045 scan;
  //int r2 = 135 scan;
  //int l1 = 315 scan;
  //int l2 = 225 scan;

  return compareSides(r1, r2, l1, l2);
 }

 void start(){
  
  int side = wallScan();

  //turn the sensor to the appropriate side
  switch(side){
    case 1:
      // restart
      printf("no good reading\n");
    case 2:
      //sensor to 090
      printf("wall is on the right\n");
    case 3:
      //sensor to 270
      printf("Wall is on the left\n");
    case else:
      //restart
      printf("fatal error\n");   
  }
  
  //start the car moving for this section
  

  
 }

