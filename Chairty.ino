
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
    leftServo.attach(2,750,2000);  // attaches the left servo on pin 2 to the servo object
   for (leftPos = 0; leftPos <= 0; leftPos -= 1) { // goes from 0 degrees to 180 degrees
    leftServo.write(10);        // tell servo to go to move 10°
    delay(5000);                       // This delay controls the time that the brakes are turned on
    leftServo.detach();
    break;
  }
  }
  
  if (sensorValue <= 600)
  {
    Serial.println("Button is NOT Pressed");
    Serial.println(sensorValue);
    leftServo.detach();
   }
}
