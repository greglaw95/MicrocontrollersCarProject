/**
 * common functionality code file
 **/
#include "standardFunctions.h"

//L=0  R=1
#define echoPin0 8 
#define trigPin0 10
#define echoPin1 7 
#define trigPin1 9

void standardFunctions::setupStandardFunctions(){
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
}

int standardFunctions::pingSensor(int pingID){

 long duration, distance;
 if(pingID==0){
 digitalWrite(trigPin0, LOW); //make sure trigger pin is low
 delayMicroseconds(2); 

 digitalWrite(trigPin0, HIGH); //trigger sound
 delayMicroseconds(10); 
 
 digitalWrite(trigPin0, LOW); 
 
 duration = pulseIn(echoPin0, HIGH); //wait until sound reflects back
 
 Serial.print("Time0  ");
 Serial.print(duration);
 distance = duration/58.2;  
 Serial.print("   Distance0  ");
 Serial.print(distance); 
 delay(50);
 Serial.println("   ");
 
}else if(pingID==1){
  
  digitalWrite(trigPin1, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  
  Serial.print("Time1  ");
  Serial.print(duration);
  distance = duration/58.2;  
  Serial.print("   Distance1  ");
  Serial.print(distance); 
  delay(50);
  Serial.println("   ");
}
return distance;

}
