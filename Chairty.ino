
/*
 Project Charity

 This program (so far) drives a  bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.
 The motor is controlled based on the analog value from the capacitive touch sensor attached to Pin A0.
 
 Created 03 March 2019
 Rev0 on 03 March 2019
 Rev1 on 05 March 2019
 Rev2 on 09 March 2019 - Left Brake now works
 by Brandon Rosenblatt

 */
// Global initializations
#include <Servo.h>
Servo leftServo;  // create servo object to control a servo
Servo rightServo;  // create servo object to control a servo
//Harman Code
int gyroPin = 11;               //Gyro is connected to analog pin 11 (May not be, unsure if it is referring to SDA pin)
float gyroVoltage = 5;         //Gyro is running at 5V
float gyroZeroVoltage = 2.5;   //Gyro is zeroed at 2.5V
float gyroSensitivity = .007;  //Our example gyro is 7mV/deg/sec-sample rate only, we need the one for our model.
float rotationThreshold = 1;   //Minimum deg/sec to keep track of - helps with gyro drifting
float currentAngle = 0;          //Keep track of our current angle
float currentAngle2 = 0;
//Harman code ends

void setup() {
  // initialize the serial port:
  Serial.begin(9600); // Set Baud Rate
}

void loop() {
  int sensorValue = analogRead(A0); // default value is 0 on startup
 
  if (sensorValue > 600 )
  {
    Serial.println("Button is Pressed");
    Serial.println(sensorValue);
    //Harman Code
    currentAngle1 = currentAngle2;//Sets previous angle to angle1 
    currentAngle2 = int gyro();//finds new angle
    if (currentAngle2-currentAngle1>5 && currentAngle2 !=0){ //if difference is greater than cutoff, exit the loop (use in actuator loop, not break)  
      break;                    //If necessary we can call additional times during loop.
    }
    
  }
  
  
  if (sensorValue <= 600)
  {
    Serial.println("Button is NOT Pressed");
    Serial.println(sensorValue);
    leftServo.detach();
   }
}


//Gyro Code
int gyro() {
  //This line converts the 0-1023 signal to 0-5V
  float gyroRate = (analogRead(gyroPin) * gyroVoltage) / 1023;

  //This line finds the voltage offset from sitting still
  gyroRate -= gyroZeroVoltage;

  //This line divides the voltage we found by the gyro's sensitivity
  gyroRate /= gyroSensitivity;

  //Ignore the gyro if our angular velocity does not meet our threshold
  if (gyroRate >= rotationThreshold || gyroRate <= -rotationThreshold) {
    //This line divides the value by 100 since we are running in a 10ms loop (1000ms/10ms)
    gyroRate /= 100;
    currentAngle += gyroRate;
  }

  //Keep our angle between 0-359 degrees
  if (currentAngle < 0)
    currentAngle += 360;
  else if (currentAngle > 359)
    currentAngle -= 360;

  //DEBUG
  Serial.println(currentAngle);

  return currentAngle;
}
