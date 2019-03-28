
/*
 Project Charity
 
 Created 03 March 2019
 Rev0 on 03 March 2019
 Rev1 on 05 March 2019
 Rev2 on 09 March 2019 - Left Brake now works
 Rev3 on 26 March 2019 - Both Brakes working
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
    rightServo.attach(3,750,2000);  // attaches the left servo on pin 2 to the servo object
   for (leftPos = 0; leftPos <= 0; leftPos -= 1) { // goes from 0 degrees to 180 degrees
    leftServo.write(10);        // tell servo to go to move 10°
    rightServo.write(10);
    delay(5000);                       // This delay controls the time that the brakes are turned on
    leftServo.detach();
    rightServo.detach();
    break;
  }
  }
  
  if (sensorValue <= 600)
  {
    Serial.println("Button is NOT Pressed");
    Serial.println(sensorValue);
    leftServo.detach();
    rightServo.detach();
   }
}
