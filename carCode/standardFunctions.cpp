/**
 * common functionality code file
 **/
#include "standardFunctions.h"
#include <Servo.h>

Servo myServo;

#define vref 11

/*MOTORS*/
#define forward 1
#define backward 2
#define right 3
#define left 4

/*PING SENSOR*/
//L=0  R=1
#define echoPin0 8 
#define trigPin0 10
#define echoPin1 7 
#define trigPin1 9

/*Servo defines*/
#define FIFTEEN 70
#define NINETY 350
#define ONEEIGHTY 665
#define THREESIXTY 1330
#define FULLLEFT 1700
#define FULLRIGHT 1300
#define servoPin 9

#define SERVOPIN 9


void standardFunctions::setupStandardFunctions(){
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  myServo.attach(SERVOPIN);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(vref,OUTPUT);
  digitalWrite(vref,HIGH);

  myServo.attach(servoPin);
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


void standardFunctions::turnSensor(int degrees){
  int pulse;
  int timeDelay;
  if(degrees>0){
    pulse = FULLLEFT;
  } else {
    pulse = FULLRIGHT;
  }
  if(abs(degrees)==15){
    timeDelay = FIFTEEN;
  } else if (abs(degrees)==90){
    timeDelay = NINETY;
  } else if(abs(degrees)==180){
    timeDelay = ONEEIGHTY;
  }else if (abs(degrees)==360){
    timeDelay = THREESIXTY;
  } else {
    return;
  }
  myServo.writeMicroseconds(pulse);
  delay(timeDelay);
  myServo.writeMicroseconds(1500);
  //delay(20);
}

void standardFunctions::drive(int direct){
  //-1 for backwards
  //0 for nuffin
  //1 for forwards
  digitalWrite(backward, LOW);
  digitalWrite(forward, LOW);
  if(direct){
    digitalWrite(forward, HIGH);
  }else if(direct==-1){
    digitalWrite(backward, HIGH);
  }
  int direction=1;
}

void standardFunctions::turn(int direct){
  //-1 for left
  //0 for straight
  //1 for right
  digitalWrite(right, LOW);
  digitalWrite(left, LOW);
  if(direct){
    //twitch left after right turn to get centre again
    digitalWrite(right, HIGH);
  }else if(direct==-1){
    digitalWrite(left, HIGH);
  }
}
