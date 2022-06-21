#include<ArduinoHardware.h>
#include <ros.h>
#include<ros/time.h>
#include <geometry_msgs/Twist.h>

//ultrasonic and buzzer pins
int const trigPin = 2;
int const echoPin = 3;
int const buzzer = 4;

//left motor Pins
#define enA 7   
#define IN1 14
#define IN2 15

//right motor pins
#define enB 6    
#define IN3 16
#define IN4 17

struct velocity
{
  double velocity;
}*left,*right;

ros::NodeHandle nh;

void onTwist(const geometry_msgs::Twist &msg);

//Subscriber
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel",onTwist);  

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // trig pin will have pulses output
  pinMode(echoPin, INPUT); // echo pin should be input to get pulse width
  pinMode(buzzer, OUTPUT); // buzz pin is output to control buzzering
  
  pinMode(enA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  
  nh.initNode();
  nh.subscribe(sub);
}

void loop() 
{
   nh.spinOnce();
}

void onTwist(const geometry_msgs::Twist &msg)
{
  //Forward
  if(msg.linear.x > 0)
  {
    left->velocity= map(abs(msg.linear.x), 0,255, 100, 255);
    analogWrite(enA, left->velocity);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    right->velocity= map(abs(msg.linear.x), 0,255, 100, 255);
    analogWrite(enB, right->velocity);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  //REVERSE
  else if(msg.linear.x < 0)
  {
    left->velocity= map(abs(msg.linear.x), 0,255, 100, 255);
    analogWrite(enA, left->velocity);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    right->velocity= map(abs(msg.linear.x), 0,255, 100, 255);
    analogWrite(enB, right->velocity);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  //LEFT
  else if(msg.angular.z > 0)
  {
    left->velocity= map(abs(msg.angular.z), 0,255, 100, 220);
    analogWrite(enA, left->velocity);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    right->velocity= map(abs(msg.angular.z), 0,255, 100, 220);
    analogWrite(enB, right->velocity);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  //RIGHT
  else if(msg.angular.z < 0)
  {
    left->velocity= map(abs(msg.angular.z), 0,255, 100, 220);
    analogWrite(enA, left->velocity);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    right->velocity= map(abs(msg.angular.z), 0,255, 100, 220);
    analogWrite(enB, right->velocity);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  //STOP
  else
  {
    left->velocity= map(left->velocity, 0,255, 100, 255);
    analogWrite(enA, left->velocity);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    right->velocity= map(right->velocity, 0,255, 100, 255);
    analogWrite(enB, right->velocity);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}
