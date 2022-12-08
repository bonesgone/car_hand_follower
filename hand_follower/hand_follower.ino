#include<Servo.h>
#include<AFMotor.h>
#define LEFT A4
#define echopin A1 // echo pin
#define trigpin A2 // Trigger pin
#define RIGHT A5

AF_DCMotor Motor1(1,MOTOR12_1KHZ);   // front left wheel
AF_DCMotor Motor2(2,MOTOR12_1KHZ);   // rear left wheel
AF_DCMotor Motor3(3,MOTOR12_1KHZ);   // rear right wheel
AF_DCMotor Motor4(4,MOTOR12_1KHZ);   // front right wheel

Servo myservo;
 
int pos = 0;
long time;

void setup(){

Serial.begin(9600);
myservo.attach(10);

for(pos = 90; pos <= 180; pos += 1){ // rotate the servo from the middle point to the right
myservo.write(pos); // apply coordinates to rorate the servo
delay(15); // pause
} 
 
for(pos = 180; pos >= 0; pos-= 1) { // rotate the servo from the right to the left
myservo.write(pos);
delay(15);
}

for(pos = 0; pos<=90; pos += 1) { // rotate the servo from the left to the middle point
myservo.write(pos);
delay(15);
}

pinMode(RIGHT, INPUT); // right IR sensor pin
pinMode(LEFT, INPUT); // left IR sensor pin

pinMode(trigpin, OUTPUT);
pinMode(echopin, INPUT);

}

void loop(){
unsigned int distance = read_cm();

int Right_Value = digitalRead(RIGHT);
int Left_Value  = digitalRead(LEFT);

Serial.print("R= ");
Serial.print(Right_Value);
Serial.print(" L= ");
Serial.print(Left_Value);
Serial.print(" D= ");
Serial.println(distance);

if(distance>=10 && distance<=30){ // if the hand is close enough
  if(checkRight() && checkLeft()){ // if the hand covers both sensors
    forward(); // follows the hand
  } else if(checkRight() && !checkLeft()){ // if the hand is only on the right 
    turnRight(); // turns to the right side
  } else if(!checkRight() && checkLeft()){ // if the hand is only on the left
    turnLeft(); // turns to the left side
  }
}



long read_cm(){ // read ultrasonic sensor
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  time = pulseIn (echopin, HIGH);
  return time / 29 / 2;
}


void forward()
{
    Serial.println("forward");
    Motor1.setSpeed(200);
    Motor1.run(FORWARD);
    Motor2.setSpeed(200);
    Motor2.run(FORWARD);
    Motor3.setSpeed(200);
    Motor3.run(BACKWARD);
    Motor4.setSpeed(200);
    Motor4.run(FORWARD);
} 
 

void turnLeft(){
  Serial.println("left");
  Motor1.setSpeed(100);
  Motor1.run(BACKWARD);
  Motor3.setSpeed(200);
  Motor3.run(FORWARD);
}

void turnRight(){
  Serial.println("right");
  Motor2.setSpeed(200);
  Motor2.run(FORWARD);
  Motor4.setSpeed(100);
  Motor4.run(BACKWARD);
}



bool checkLeft(int Left_Value){
  return Left_Value == 1;
}


bool checkRight(int Right_Value) {
  return Right_Value == 1;
}



void backward(){ // backward
Motor1.setSpeed(120);
Motor1.run(BACKWARD); 
Motor2.setSpeed(120);
Motor2.run(BACKWARD);
Motor3.setSpeed(120);
Motor3.run(BACKWARD); 
Motor4.setSpeed(120);
Motor4.run(BACKWARD); 
}


void stop(){ // stop
Motor1.setSpeed(0);  
Motor1.run(RELEASE);
Motor2.setSpeed(0);
Motor2.run(RELEASE);
Motor3.setSpeed(0);
Motor3.run(RELEASE);
Motor4.setSpeed(0);
Motor4.run(RELEASE);  
}
