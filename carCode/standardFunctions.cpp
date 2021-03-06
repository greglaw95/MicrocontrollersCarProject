#include <Servo.h>

/**
 * common functionality code file
 **/
#include "standardFunctions.h"


Servo myServo;


/*MOTORS*/
#define FORWARD 11
#define BACKWARD 12
#define LEFT 2
#define RIGHT 3


/*PING SENSOR*/
//L=0  R=1
#define TRIGPIN0 6 
#define ECHOPIN0 7
#define RESETPIN1 5 
#define TRIGPIN1 8
#define ECHOPIN1 9
#define READINGS 5
#define TIMEOUT 7000

/*
Code for old servo approach
#define AFIFTEEN 78
#define CFIFTEEN 89
#define ANINETY 430
#define CNINETY 455
#define AONEEIGHTY 792
#define CONEEIGHTY 820
#define ATHREESIXTY 1535
#define CTHREESIXTY 1575
*/

/*Servo defines*/
#define FULLLEFT 1700
#define FULLRIGHT 1300

#define SERVOPIN 13


void standardFunctions::setupStandardFunctions(){
  pinMode(TRIGPIN0, OUTPUT);
  pinMode(ECHOPIN0, INPUT);
  pinMode(TRIGPIN1, OUTPUT);
  pinMode(ECHOPIN1, INPUT);
  myServo.attach(SERVOPIN);
  pinMode(FORWARD, OUTPUT);
  pinMode(BACKWARD, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RESETPIN1,OUTPUT);
  digitalWrite(RESETPIN1,LOW);
}



int soloPingSensor(int pingID){

 long duration, distance;
 if(pingID==0){
 digitalWrite(TRIGPIN0, LOW); //make sure trigger pin is low
 delayMicroseconds(2); 

 digitalWrite(TRIGPIN0, HIGH); //trigger sound
 delayMicroseconds(10); 
 
 digitalWrite(TRIGPIN0, LOW); 
 
 duration = pulseIn(ECHOPIN0, HIGH, TIMEOUT); //wait until sound reflects back with timeout
 
 //Serial.print("Time0  ");
 //Serial.print(duration);
 distance = duration/58.2;  
 //Serial.print("   Distance0  ");
 //Serial.print(distance); 
 //delay(100);
 //Serial.println("   ");
 
}else if(pingID==1){
  digitalWrite(TRIGPIN1, LOW); 
  delayMicroseconds(2); 

  digitalWrite(TRIGPIN1, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(TRIGPIN1, LOW);
  duration = pulseIn(ECHOPIN1, HIGH, TIMEOUT); //added timeout
  //Serial.print("Time1  ");
  //Serial.print(duration);
  distance = duration/58.2;  
  //Serial.print("   Distance1  ");
  //Serial.print(distance); 
  //delay(100);
  //Serial.println("   ");
}
return distance;

}


void standardFunctions::turnServo(int degrees){
  if(degrees>172)
    degrees=172;
  if(degrees<8)
    degrees=8;
  myServo.write(degrees);
  
}

int getCountOfSimilarNumbers(int pingValues[],int index){
  /*returns the count of similar values in the array
  to the ping value at index*/
  int i;
  int counter=0;
  for(i=0;i<READINGS;i++){
     int diff = abs(pingValues[i] - pingValues[index]);
     if(diff<10 && diff>=0){
       //similar number
       counter++;
   }
  }
  return counter;
}

int standardFunctions::pingSensor(int pingID){
  int currentReading;
  int attempts=0;
  currentReading=soloPingSensor(pingID);
  for(;attempts<READINGS; attempts++){
    if(pingID==1){
      digitalWrite(RESETPIN1,HIGH);
      delay(3);
      digitalWrite(RESETPIN1,LOW);
      delay(3);
    }
    currentReading=soloPingSensor(pingID);
    if(currentReading!=0){
      Serial.print("   pingSensor");
      Serial.print(pingID);
      Serial.print(":   ");
      Serial.print(currentReading);
      Serial.println();
      return currentReading;
    }
  }
  Serial.print("   pingSensor");
  Serial.print(pingID);
  Serial.print(":   ");
  Serial.print(300);
  Serial.println();
  return 300;
  
  /*
  int pingValues[READINGS];
  int similarValues[READINGS];
  int currentResult;
  int totalResult=0;
  int largest=0;
  int largestIndex=0;
  for(int i=0;i<READINGS;i++){
    do{
      currentResult=soloPingSensor(pingID);
    } while(currentResult==0);
    pingValues[i]=currentResult;
    //totalResult=totalResult+currentResult;
  }

  for(int i=0;i<READINGS;i++){
    similarValues[i] = getCountOfSimilarNumbers(pingValues,i); 
  }
    //finds one of the numbers that have the highest count of similar numbers
    for (int i = 0; i < READINGS; i++)
    {
        if (largest < similarValues[i]){
            largest = similarValues[i];
            largestIndex=i;
        }
    }
  //return totalResult/READINGS;
  return pingValues[largestIndex];
  */

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
  digitalWrite(BACKWARD, LOW);
  digitalWrite(FORWARD, LOW);
  if(1==direct){
    digitalWrite(FORWARD, HIGH);
  }else if(direct==-1){
    digitalWrite(BACKWARD, HIGH);
  }
}

void standardFunctions::turn(int direct){
  //-1 for left
  //0 for straight
  //1 for right
  digitalWrite(RIGHT, LOW);
  digitalWrite(LEFT, LOW);
  if(1==direct){
    //twitch left after right turn to get centre again
    digitalWrite(RIGHT, HIGH);
  }else if(direct==-1){
    digitalWrite(LEFT, HIGH);
  }
}
