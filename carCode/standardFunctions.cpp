/**
 * common functionality code file
 **/
#include "standardFunctions.h"
#include <Servo.h>

Servo myServo;


/*MOTORS*/
#define forward 11
#define backward 12
#define right 3
#define left 2

/*PING SENSOR*/
//L=0  R=1
#define echoPin0 6 
#define trigPin0 5 
#define echoPin1 10 
#define trigPin1 8

/*Servo defines*/
#define AFIFTEEN 78
#define CFIFTEEN 89
#define ANINETY 430
#define CNINETY 455
#define AONEEIGHTY 792
#define CONEEIGHTY 820
#define ATHREESIXTY 1535
#define CTHREESIXTY 1575
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
 
 duration = pulseIn(echoPin0, HIGH, 10); //wait until sound reflects back with timeout
 
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
  duration = pulseIn(echoPin1, HIGH, 10); //added timeout
  
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


void standardFunctions::turnServo(int degrees){
  if(degrees>180)
    degrees=180;
  if(degrees<0)
    degrees-0;
  
  myServo.write(degrees);
  
}

//DO NOT CALL
/*
void standardFunctions::turnSensor(int degrees){
  int pulse;
  int timeDelay;
  if(degrees<0){
    pulse = FULLLEFT;
  } else {
    pulse = FULLRIGHT;
  }

  if(degrees==-15){
    timeDelay = AFIFTEEN;
  } else if (degrees==-90){
    timeDelay = ANINETY;
  } else if(degrees==-180){
    timeDelay = AONEEIGHTY;
  } else if (degrees==-360){
    timeDelay = ATHREESIXTY;
  } else if(abs(degrees)==15){
    timeDelay = CFIFTEEN;
  } else if (degrees==90){
    timeDelay = CNINETY;
  } else if(degrees==180){
    timeDelay = CONEEIGHTY;
  }else if (degrees==360){
    timeDelay = CTHREESIXTY;
  } else {
    return;
  }
  myServo.writeMicroseconds(pulse);
  delay(timeDelay);
  myServo.writeMicroseconds(1500);
  //delay(20);
}
*/

void standardFunctions::drive(int direct){
  //-1 for backwards
  //0 for nuffin
  //1 for forwards
  digitalWrite(backward, LOW);
  digitalWrite(forward, LOW);
  if(1==direct){
    digitalWrite(forward, HIGH);
  }else if(direct==-1){
    digitalWrite(backward, HIGH);
  }
}

void standardFunctions::turn(int direct){
  //-1 for left
  //0 for straight
  //1 for right
  digitalWrite(right, LOW);
  digitalWrite(left, LOW);
  if(1==direct){
    //twitch left after right turn to get centre again
    digitalWrite(right, HIGH);
  }else if(direct==-1){
    digitalWrite(left, HIGH);
  }
}
