#include<CapacitiveSensor.h>
#include <NewPing.h>   //Include NewPing Library

CapacitiveSensor cap= CapacitiveSensor(10,11);

#define LeftMotorForward 2
#define LeftMotorBackward 3
#define RightMotorForward 5
#define RightMotorBackward 4
#define LED 13
#define TRIGGER_PIN  8   //Trigger pin of Ultrasonic sensor connected to pin 6
#define ECHO_PIN     9   //Echo pin of Ultrasonic sensor connected to pin 7
#define MAX_DISTANCE 100 //The maximum distance we want the sensor to look for is 1m

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //Create Ultrasonic sensor object

unsigned int time;            //Variable to store how long it takes for the ultrasonic wave to come back
int distance;                 //Variable to store the distance calculated from the sensor
int triggerDistance = 30;     //The distance we want the robot to look for a new path
int fDistance;                //Variable to store the distance in front of the robot
int lDistance;                //Variable to store the distance on the left side of the robot
int rDistance;                //Variable to store the distance on the right side of the robot

void setup()                                            //This block happens once on startup
{
  Serial.begin(9600);                              //I have included the serial initialize but commented it out, if you want to debug and print information to the serial monitor just uncomment
  
  //Here we are setting the pin modes. As we will sending out signals from the pins we set them as outputs
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(LED, OUTPUT);                                    
}
void loop()
{
  long a=cap.capacitiveSensor(30);
  scan();                                //Get the distance retrieved
  fDistance = distance;  //Set that distance to the front distance
  if(a<100)
  {
    Serial.println(a);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(RightMotorForward, LOW);}
  if(a > 100)
  {
    Serial.println(a);
    while(1){moveForward();
  if(fDistance < triggerDistance){       //If there is something closer than 30cm in front of us
    moveBackward();                      //Move Backward for a second
    delay(1000); 
    moveRight();                         //Turn Right for half a second
    delay(500);
    moveStop();                          //Stop
    scan();                              //Take a reading
    rDistance = distance;                //Store that to the distance on the right side
    moveLeft();
    delay(1000);                         //Turn left for a second
    moveStop();                          //Stop
    scan();                              //Take a reading
    lDistance = distance;                //Store that to the distance on the left side
    if(lDistance < rDistance){           //If the distance on the left is smaller than that of the right
      moveRight();                       //Move right for a second
      delay(1000);
      moveForward();                     //Then move forward
    }
    else{
      moveForward();                     //If the left side is larger than the right side move forward
    }
    
  }
  else{
    moveForward();                       //If there is nothing infront of the robot move forward
  }
  if(digitalRead(7)==HIGH)
    {
      break;
    }
}
  }
}

void scan(){
  time = sonar.ping();                  //Send out a ping and store the time it took for it to come back in the time variable
  distance = time / US_ROUNDTRIP_CM;    //Convert that time into a distance
  if(distance == 0){                    //If no ping was recieved
    distance = 100;                     //Set the distance to max
  }
  delay(10);
}

void moveForward()                                    //This function tells the robot to go forward 
{
  Serial.println("");
  Serial.println("Moving forward");
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
}

void moveBackward()                                  //This function tells the robot to move backward
{
  Serial.println("");
  Serial.println("Moving backward");
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
}

void moveLeft()                                      //This function tells the robot to turn left
{
  Serial.println("");
  Serial.println("Moving left");
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  
}

void moveRight()                                    //This function tells the robot to turn right
{
  Serial.println("");
  Serial.println("Moving right");
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
}

void moveStop()                                     //This function tells the robot to stop moving
{
  Serial.println("");
  Serial.println("Stopping");
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}


