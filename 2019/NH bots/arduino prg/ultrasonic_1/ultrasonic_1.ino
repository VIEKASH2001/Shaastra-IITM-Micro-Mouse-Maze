#include <Ultrasonic.h>
Ultrasonic ultrasonic1(12,13);//front sensor
Ultrasonic ultrasonic2(2,4);//left sensor
Ultrasonic ultrasonic3(7,8);//right sensor

const int IN1=3;
const int IN2=5;
const int IN3=6;
const int IN4=9;
 int  SPEED_Control=100;
void setup() 
{
  // fIRST , define the Motor's pin as an OUTPUT
  
pinMode( IN1 ,OUTPUT);// Right Motor forward
pinMode( IN2 ,OUTPUT);// Right Motor back
pinMode( IN3 ,OUTPUT);// left Motor back
pinMode( IN4 ,OUTPUT);// left Motor forward
Serial.begin(9600);
}
////////////////////////////////////////////////////////////////

void BACKWARD(int Speed)
{
 
  analogWrite(IN1,0);
  analogWrite(IN2,Speed);
  analogWrite(IN3,Speed);
  analogWrite(IN4,0);
}
////////////////////////////////////////////////////////////////

void FORWARD(int Speed){

  analogWrite(IN1,Speed);
  analogWrite(IN2,0);
  analogWrite(IN3,0);
  analogWrite(IN4,Speed);
}
////////////////////////////////////////////////////////////////

void LEFT(int Speed){
 
  analogWrite(IN1,Speed);
  analogWrite(IN2,0);
  analogWrite(IN3,0);
  analogWrite(IN4,0);
}
////////////////////////////////////////////////////////////////

void RIGHT(int Speed){
 
  analogWrite(IN1,0);
  analogWrite(IN2,0);
  analogWrite(IN3,0);
  analogWrite(IN4,Speed);
}
////////////////////////////////////////////////////////////////

void Stop(){
  
  analogWrite(IN1,0);
  analogWrite(IN2,0);
  analogWrite(IN3,0);
  analogWrite(IN4,0);
}
////////////////////////////////////////////////////////////////

void loop() 
{
   FORWARD(SPEED_Control);
 byte  distance1 = ultrasonic1.Ranging(CM) ;// waits 15ms for the servo to reach the position
 byte  distance2 = ultrasonic2.Ranging(CM) ;
 byte  distance3 = ultrasonic3.Ranging(CM) ;
  
   if (distance1 <= 20 && distance2 <= 20 && distance3 > 20){
      LEFT(SPEED_Control);
      delay(500);
      }
   else if (distance1 <= 20 && distance3 <= 20 && distance2 >20){
      RIGHT(SPEED_Control);
      delay(500);
      } 
   else if (distance2 <= 20 && distance3 <= 20 && distance1 >20){
      FORWARD(SPEED_Control);
      delay(500);
      } 
  
 
}
