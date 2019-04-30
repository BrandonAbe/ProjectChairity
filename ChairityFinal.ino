/*
 A Safe Lift Mechanism For Elderly Assistance
 Authors: Brandon Rosenblatt, Harman Singh, Israel Helms
 
 This program was created to control an Arduino Mega 2560, MPU 6050 Gyroscope,
 capacitive touch sensor, and a 2-channel relay.
*/

// Global initializations
#include <Servo.h>
#include <Wire.h>
#include <math.h>

//Brake Constants
Servo leftServo;  // create servo object to control the left servo
Servo rightServo;  // create servo object to control the right servo

//Relay Constants
const int leftRelay = 53;  // sets control pin for left relay 
const int rightRelay = 52; // sets control pin for left relay 

//Gyroscope Constants
const int MPU=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double pitch,roll,yaw; // Double float variables for pitch, roll, and yaw
//Set gyro limits
double pitchLimit, yawLimit, rollLimit; // Variables for limiting pitch, roll, and yaw

void setup() {
  // initialize the serial port:
  Serial.begin(9600); // Set Baud Rate

  //relay Code
  pinMode(leftRelay, OUTPUT);  // Allow left relay to be an output
  pinMode(rightRelay, OUTPUT); // Allow right relay to be an output

  //Gyro Code
  Wire.begin(); 
  Wire.beginTransmission(MPU); //Begin transmission to gyro
  Wire.write(0x6B); //Write to this location
  Wire.write(0);    //The value 0
  Wire.endTransmission(true); //End transmission
}

void loop() {
  int sensorValue = analogRead(A0); // default value is 0 on startup
  if (sensorValue > 600 )
  {
    Serial.println("Button is Pressed");
    //Serial.println(sensorValue);   // Uncomment to display analog value from touch sensor for debugging purposes. 
    leftServo.attach(2,750,2000);  // attaches the left servo on pin 2 to the servo object
    rightServo.attach(3,750,2000);  // attaches the right servo on pin 3 to the servo object
   
   for (leftPos = 0; leftPos <= 0; leftPos -= 1) { // goes from 0 degrees to 180 degrees
    leftServo.write(10);        //  tell left servo to go to move 10°
    rightServo.write(10);       // tell right servo to go to move 10°
    actuateUp();                // Actuates the servo up
    actuateDown();              // Actuates the servo back down
    leftServo.detach();         // Turns off left servo movement
    rightServo.detach();        // Turns off left servo movement
    break;                      // Exit loop
  }
  }
  
  if (sensorValue <= 600) // if capacitive sensor is not pressed
  {
    Serial.println("Button is NOT Pressed");
    Serial.println(sensorValue);
    leftServo.detach();
    rightServo.detach();
   }
}

void actuateUp(){
 digitalWrite(leftRelay, HIGH); //Control Polarity of Motor
 digitalWrite(rightRelay, LOW); //Control Polarity of Motor
 for (int i = 0; i <= 3500; i++){
    //Gyro Code comparison
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,14,true);

    //read gyro data
    GyX=(Wire.read()<<8|Wire.read())/100;
    GyY=(Wire.read()<<8|Wire.read())/100;
    GyZ=(Wire.read()<<8|Wire.read())/100;

    //get pitch/roll
    getAngle(AcX,AcY,AcZ);
  
    Serial.print("Gyroscope: ");
    Serial.print("X = "); Serial.print(GyX);
    Serial.print(" | Y = "); Serial.print(GyY);
    Serial.print(" | Z = "); Serial.println(GyZ);
    Serial.println(" ");
    if (roll>=rollLimit){
      actuateDown();
      break;
    }
    if (yaw>= yawLimit){
      actuateDown();
      break;
    }
    if (pitch>= pitchLimit){
      break;
    }
    delay(100);

 }

 digitalWrite(leftRelay, HIGH); //Control Polarity of Motor
 digitalWrite(rightRelay, HIGH); //Control Polarity of Motor
 delay(5000);// wait 5 seconds
}

//convert the accel data to pitch/roll
void getAngle(int Vx,int Vy,int Vz) {
double x = Vx;
double y = Vy;
double z = Vz;

roll = atan(x/sqrt((y*y) + (z*z)));
pitch = atan(y/sqrt((x*x) + (z*z)));
//convert radians into degrees
pitch = pitch * (180.0/3.14);
roll = roll * (180.0/3.14) ;
}

void actuateDown(){
  digitalWrite(leftRelay, LOW);
  digitalWrite(rightRelay, HIGH);//Activate the relay one direction, they must be different to move the motor
   for (int i = 0; i <= 3500; i++){
    //Gyro Code comparison
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,14,true);

    int GyXoff,GyYoff,GyZoff;

    //Gyro correction
    GyXoff = -1*xAvg;
    GyYoff = -1*yAvg;
    GyZoff = -1*zAvg;

    //read gyro data
    GyX=(Wire.read()<<8|Wire.read()) + GyXoff;
    GyY=(Wire.read()<<8|Wire.read()) + GyYoff;
    GyZ=(Wire.read()<<8|Wire.read()) + GyZoff;

    //get pitch/roll
    getAngle(AcX,AcY,AcZ);

    //send the data out the serial port
    /*Serial.print("Angle (in degrees): ");
    Serial.print("Pitch = "); Serial.print(pitch);
    Serial.print(" | Roll = "); Serial.println(roll);


    Serial.print("Gyroscope: ");
    Serial.print("X = "); Serial.print(GyX);
    Serial.print(" | Y = "); Serial.print(GyY);
    Serial.print(" | Z = "); Serial.println(GyZ);
    Serial.println(" ");
    if (roll>=rollLimit){
      actuateDown();
      break;
    }
    if (yaw>= yawLimit){
      actuateDown();
      break; 
    }*/
    if (pitch<= 0){
      break;
    }
    delay(100);

 }

  digitalWrite(leftRelay, HIGH);
  digitalWrite(rightRelay, HIGH);//Deactivate both relays to brake the motor
  delay(500);// wait .5 seconds
}
