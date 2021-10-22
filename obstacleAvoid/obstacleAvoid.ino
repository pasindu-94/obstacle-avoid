/*===================================================================

This code is used to develop an Obstacle Avoiding Robot with 3 Ultra Sonic Sensors for Automatic Navigation

DEVELOPER: Pasindu Liyanage
DATE: 2020.04.27
=====================================================================*/

#include <NewPing.h>

#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonarfront(A0, 13, MAX_DISTANCE);
NewPing sonarright(A1, 12, MAX_DISTANCE);
NewPing sonarleft(A2, 11, MAX_DISTANCE); 

int distancefront, distanceleft, distanceright;

int frontlimit = 10;
int leftlimit = 10;
int rightlimit = 10;


#define LeftMotorEnable 6
#define RightMotorEnable 5

#define LeftMotorA 3
#define LeftMotorB 4

#define RightMotorA 8
#define RightMotorB 9



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initializePins();

  //Set Speed
  analogWrite(LeftMotorEnable, 200);
  analogWrite(RightMotorEnable, 120);

  //Delay to Start
  delay(5000);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  
  pingSensors();

  forward();

  obstacleAvoid();


}


void initializePins() {
  pinMode(LeftMotorEnable, OUTPUT);
  pinMode(RightMotorEnable, OUTPUT);

  pinMode(LeftMotorA, OUTPUT);
  pinMode(LeftMotorB, OUTPUT);

  pinMode(RightMotorA, OUTPUT);
  pinMode(RightMotorB, OUTPUT);

}


void forward() {
  digitalWrite(LeftMotorA, LOW);
  digitalWrite(LeftMotorB, HIGH);

  digitalWrite(RightMotorA, LOW);
  digitalWrite(RightMotorB, HIGH);
}


void backward() {
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW);

  digitalWrite(RightMotorA, HIGH);
  digitalWrite(RightMotorB, LOW);
}



void left() {
  digitalWrite(LeftMotorA, HIGH);
  digitalWrite(LeftMotorB, LOW);

  digitalWrite(RightMotorA, LOW);
  digitalWrite(RightMotorB, HIGH);
}



void right() {
  digitalWrite(LeftMotorA, LOW);
  digitalWrite(LeftMotorB, HIGH);

  digitalWrite(RightMotorA, HIGH);
  digitalWrite(RightMotorB, LOW);
}


void pingSensors() {
  distancefront = sonarfront.ping_cm();
  distanceleft = sonarleft.ping_cm();
  distanceright = sonarright.ping_cm();

}


void obstacleAvoid() {
  if ((distancefront < frontlimit) && (distancefront != 0)) {
    distancefront = sonarfront.ping_cm();
    if ((distancefront < frontlimit) && (distancefront != 0)) {
      if ((distanceleft < distanceright) && (distanceleft != 0)) {
        backward();
        delay(300);
        right();
        delay(1000);
      } else {
        backward();
        delay(300);
        left();
        delay(1000);
      }
    }
  }

  if ((distanceleft < leftlimit) && (distanceleft != 0)) {
    distanceleft = sonarleft.ping_cm();
    if ((distanceleft < leftlimit) && (distanceleft != 0)) {
      backward();
      delay(300);
      right();
      delay(1000);
    }
  }

  if ((distanceright < rightlimit) && (distanceright != 0)) {
    distanceright = sonarright.ping_cm();
    if ((distanceright < rightlimit) && (distanceright != 0)) {
      backward();
      delay(300);
      left();
      delay(1000);
    }
  }
}
