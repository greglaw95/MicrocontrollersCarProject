#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include "driveMode.h"
<<<<<<< HEAD
=======
#include "startMode.h"
>>>>>>> a777f3ef0340e91e888fb088a045162834844170
#include "standardFunctions.h"

static standardFunctions sf;
driveMode dm;
startMode sm;

int distance0,distance1=0;
int wall=0;
byte s;
byte r;
byte l;

void setup() {
  Serial.begin(9600);
  Serial.print("start");
  sf.setupStandardFunctions();
<<<<<<< HEAD
}

void loop() {
  Serial.println(sf.demo());
  
 distance1=sf.pingSensor(1);
 //delay(100);
 distance0=sf.pingSensor(0);

 long diff=0;
 diff = abs(distance0-distance1);
Serial.print("Dist1  ");
Serial.print(distance0);
Serial.print("   Dist0   ");
Serial.print(distance1);
Serial.println();


  Serial.println();
  Serial.print("diff  ");
  Serial.print(diff);
  Serial.println();
if(distance0<5 && distance1<5){
  wall++;
}  
if(wall==10){
  Serial.print("Dats a wall");
  wall=0;
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

if(diff<5 && diff>=0){
    //both can see therefore go straight
    s++;
}else if(distance0<distance1){
    //turn motor to go left
    r++;
}else if(distance1<distance0){
   l++;
}
 
 Serial.println(" ");
=======
  sm.start();
  sf.drive(0);
  dm.drive();

}

void loop() {
  dm.drive();
>>>>>>> a777f3ef0340e91e888fb088a045162834844170
}
