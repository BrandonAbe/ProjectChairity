const int leftRelay = 53;
const int rightRelay = 52;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Set Baud Rate
  pinMode(leftRelay, OUTPUT); //forward
  pinMode(rightRelay, OUTPUT); //backward
}

void loop() {
  int sensorValue = analogRead(A0); // default value is 0 on startup
   if (sensorValue > 600 )
  {
    Serial.println("Button is Pressed");
    Serial.println(sensorValue);
    actuate();
  }

  if (sensorValue <= 600)
  {
    Serial.println("Button is NOT Pressed");
     Serial.println(sensorValue);
  } 
}

void actuate(){
 //Up for 3.5 seconds
  digitalWrite(leftRelay, HIGH);
  digitalWrite(rightRelay, LOW);//Activate the relay the other direction, they must be different to move the motor
  delay(35000);// wait 35 seconds
  digitalWrite(leftRelay, HIGH);
  digitalWrite(rightRelay, HIGH);//Deactivate both relays to brake the motor
  delay(500);// wait .5 seconds
 
  //Down for 3.5 seconds
  digitalWrite(leftRelay, LOW);
  digitalWrite(rightRelay, HIGH);//Activate the relay one direction, they must be different to move the motor
  delay(35000); //wait 35 seconds
  digitalWrite(leftRelay, HIGH);
  digitalWrite(rightRelay, HIGH);//Deactivate both relays to brake the motor
  delay(500);// wait .5 seconds buffer time before another commmand can occur
  
}

void actuateDown(){
  digitalWrite(leftRelay, LOW);
  digitalWrite(rightRelay, HIGH);//Activate the relay one direction, they must be different to move the motor
  delay(35000); // wait 10 seconds

  digitalWrite(leftRelay, HIGH);
  digitalWrite(rightRelay, HIGH);//Deactivate both relays to brake the motor
  delay(500);// wait .5 seconds
}

void actuateUp(){
 digitalWrite(leftRelay, HIGH);
 digitalWrite(rightRelay, LOW);//Activate the relay the other direction, they must be different to move the motor
 delay(35000);// wait 10 seconds

 digitalWrite(leftRelay, HIGH);
 digitalWrite(rightRelay, HIGH);//Deactivate both relays to brake the motor
 delay(500);// wait .5 seconds
}
