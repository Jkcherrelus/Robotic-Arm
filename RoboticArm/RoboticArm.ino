#include <Servo.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

//Servo motors
Servo base;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


//Servo pin out
int basePin =  13;//Pin D7
int servoPin1 = 0;//Pin D3
int servoPin2 = 12;//Pin D6
int servoPin3 = 2;//Pin D4
int servoPin4 = 14;//Pin D5

//Servo motor position
int basePos;
int servo1Pos;
int servo2Pos;
int servo3Pos;
int servo4Pos;

//serial port information
unsigned long serialData = 0;
int inbyte;

//Setup message bytes

byte inputByte_0;//check for message

byte inputByte_1;//input or output

byte inputByte_2;//choose servo to turn

byte inputByte_3;//determine direction, up or down

byte inputByte_4; //end of message marker

void setup() {
  // put your setup code here, to run once:
//attach servo to board
base.attach(basePin);
servo1.attach(servoPin1);
servo2.attach(servoPin2);
servo3.attach(servoPin3);
servo4.attach(servoPin4);

//initialize servo position
basePos = 0;
servo1Pos = 0;
servo2Pos = 0;
servo3Pos = 0;
servo4Pos = 0;
Serial.println("All servos have been initialized");

Serial.begin(115200);
}

void loop() 
{
    //Read Buffer
  if (Serial.available() == 5) 
  {
    //Read buffer
    inputByte_0 = Serial.read();
    delay(100);    
    inputByte_1 = Serial.read();
    delay(100);      
    inputByte_2 = Serial.read();
    delay(100);      
    inputByte_3 = Serial.read();
    delay(100);
    inputByte_4 = Serial.read();   
  }
  //Check for start of Message
  if(inputByte_0 == 16)
  {       
       //Detect Command type
       switch (inputByte_1) 
       {
          case 127:
             //Set pick the direction of turning
             switch (inputByte_2)
            {
              case 0:
              if(inputByte_3 == 1)
              {
                moveServoUp(base,90);
                Serial.print("Service performed");
              }
              else if(inputByte_3 == 0)
              {
                moveServoDown(base,90);
                Serial.print("Service performed");
              }
              else{
                moveServoUp(base,0);
                Serial.print("Service performed");
              }
              break;
              case 1:
              if(inputByte_3 == 1)
              {
                moveServoUp(servo1,90);
                Serial.print("Service performed");
              }
              else if(inputByte_3 == 0)
              {
                moveServoDown(servo1,90);
                Serial.print("Service performed");
              }
              else{
                moveServoUp(servo1,0);
                Serial.print("Service performed");
              }
              break;
              case 2:
              if(inputByte_3 == 1)
              {
                moveServoUp(servo2,90);
                Serial.print("Service performed");
              }
              else if(inputByte_3 == 0)
              {
                moveServoDown(servo2,90);
                Serial.print("Service performed");
              }
              else{
                moveServoUp(servo2,0);
                Serial.print("Service performed");
              }
              break;
              case 3:
              if(inputByte_3 == 1)
              {
                moveServoUp(servo3,90);
                Serial.print("Service performed");
              }
              else if(inputByte_3 == 0)
              {
                moveServoDown(servo3,90);
                Serial.print("Service performed");
              }
              else{
                moveServoUp(servo3,0);
                Serial.print("Service performed");
              }
              break;
              case 4:
              if(inputByte_3 == 1)
              {
                moveServoUp(servo4,90);
                Serial.print("Service performed");
              }
              else if(inputByte_3 == 0)
              {
                moveServoDown(servo4,90);
                Serial.print("Service performed");
              }
              else{
                moveServoUp(servo4,0);
                Serial.print("Service performed");
              }
              break;
            } 
            break;
          case 128:
            //Say hello
            Serial.print("HELLO FROM ARDUINO");
            break;
        } 
        //Clear Message bytes
        inputByte_0 = 16;
        inputByte_1 = 127;
        inputByte_2 = 0;
        inputByte_3 = 0;
        inputByte_4 = 0;
        delay(20);
        //Let the PC know we are ready for more data
        Serial.print("-READY TO RECEIVE");
  
}
}

//move servo motor to the right or down
void moveServoDown(Servo servo, int pos)
{  
    for(pos = 0; pos <= 90; pos += 1) // goes from 0 degrees to 90 degrees 
  {                                  // in steps of 1 degree 
    servo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
}
//move servo motor to the left or up
void moveServoUp(Servo servo, int pos)
{
  for(pos = 90; pos>=0; pos-=1)
  {                                
    servo.write(pos);
    delay(15);
  }
}




