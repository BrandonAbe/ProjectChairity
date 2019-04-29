// Global initializations
#include <Servo.h>
#include <Wire.h>
#include <math.h>

//Gyroscope Constants
const int MPU=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double pitch,roll,yaw;
double pitchAvg = 0; //Averages across 13 samples
double rollAvg = 0; //Average across 13 samples
double xAvg = 0; double yAvg = 0; double zAvg = 0;
//Set gyro limits
double pitchLimit, yawLimit, rollLimit;
//pitchLimit = 0;
//yawLimit = 0;
//rollLimit = 0;

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

void setup() {
   Serial.begin(9600); // Set Baud Rate
   
   //Gyro Setup Code
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
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
    GyX=(Wire.read()<<8|Wire.read())/100;
    GyY=(Wire.read()<<8|Wire.read())/100;
    GyZ=(Wire.read()<<8|Wire.read())/100;

    //get pitch/roll
    getAngle(AcX,AcY,AcZ);

    //send the data out the serial port
    Serial.print("Angle (in degrees): ");
    Serial.print("Pitch = "); Serial.print(pitch);
    Serial.print(" | Roll = "); Serial.println(roll);


    Serial.print("Gyroscope: ");
    Serial.print("X = "); Serial.print(GyX);
    Serial.print(" | Y = "); Serial.print(GyY);
    Serial.print(" | Z = "); Serial.println(GyZ);
    delay(2000);
}
