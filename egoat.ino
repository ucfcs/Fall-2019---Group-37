/* 
 *  ROS subscriber for motor speed commands
 */

#include <ros.h>
#include "egoat/SetMotorSpeed.h"

//Motor Pins
int EN_A = 11;      //Enable pin for first motor
int IN1 = 9;       //control pin for first motor
int IN2 = 8;       //control pin for first motor
int IN3 = 7;        //control pin for second motor
int IN4 = 6;        //control pin for second motor
int EN_B = 10;      //Enable pin for second motor

ros::NodeHandle  nh;

/*
 * Handle the message received.
 */
void messageCb(const egoat::SetMotorSpeed& msg){
  int left = msg.left_motor;
  int right = msg.right_motor;

  // Convert message to values the motor controller understands
  writeMotorSpeedAndDirection(left, EN_A, IN1, IN2);
  writeMotorSpeedAndDirection(right, EN_B, IN3, IN4);

  // Use NodeHandle to output debug info to rostopic
  char buf[5]; // loginfo is picky and wants a char*, so we have to use itoa
  nh.loginfo("Received: ");
  nh.loginfo(itoa(left, buf, 10));
  nh.loginfo(itoa(right,buf, 10));
}

/*
 * Convert the message value
 * 
 * Currently, the ROS message SetMotorSpeed receives 2 int8, which means
 * the range for each motor is [-128, 127].
 * 
 * The intention is to set the motor speed as a percentage (in int)
 * of maximum motor speed. This will have to be mapped to
 * [0, 255] for the L298N motor controller on the prototype's
 * speed, and the sign indicates the direction
 * 
 * TODO: Check the range of values for the final version's
 * motor controllers.
 */
void writeMotorSpeedAndDirection(int messageValue, int enablePin, int input1, int input2) {
  int powerOut = map(abs(messageValue), 0, 100, 0, 255);
  analogWrite(enablePin, powerOut);
  if(messageValue > 0) {
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
  } else if(messageValue < 0) {
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
  } else {
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
  }
}

ros::Subscriber<egoat::SetMotorSpeed> sub("motors", &messageCb);

void setup()
{   
  // Set up motor controller pins
  pinMode(EN_A, OUTPUT);
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);
  pinMode(EN_B, OUTPUT);

  // Set up the NodeHandler for ROS
  nh.initNode();
  nh.subscribe(sub);
}

/*
 * TODO: Add code to stop the bot regardless of message if the ultrasonic
 * sensors detect an obstacle.
 */
void loop()
{  
  nh.spinOnce();
  delay(1);
}