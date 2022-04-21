#include <Servo.h>

#define S0 PB0
#define S1 PB1
#define S2 PA2
#define S3 PA3
#define sensorOut PA7

int redMin = 108; // Red minimum value
int redMax = 158; // Red maximum value
int greenMin = 143; // Green minimum value
int greenMax = 240; // Green maximum value
int blueMin = 108; // Blue minimum value
int blueMax = 189; // Blue maximum value
// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0; 
// Variables for final Color values 
int redValue;
int greenValue;
int blueValue;

//int color; // 0 for red, 1 for green, 2 for  blue, 3 for other

Servo servoA0; // create servo object to control a servo
Servo servoA1;
int posA0 = 0; // variable to store the servo position
int posA1 = 0;

void setup() {
 
  servoA0.attach(PA0); // attaches the servo on pin 9 to the servo object
  servoA1.attach(PA1);

  pinMode(PC13, OUTPUT);
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop(){

  digitalWrite(PC13, HIGH);
  delay(2000);
  redPW = getRedPW();
  redValue = map(redPW, redMin,redMax,255,0);
  delay(200);
  greenPW = getGreenPW();
  greenValue = map(greenPW, greenMin,greenMax,255,0);
  delay(200);
  bluePW = getBluePW();
  blueValue = map(bluePW, blueMin,blueMax,255,0);
  delay(200);

  Serial.print("Red = ");
  Serial.print(redValue);
  Serial.print(" - Green = ");
  Serial.print(greenValue);
  Serial.print(" - Blue = ");
  Serial.println(blueValue);
  
  
  if (redValue-greenValue > 20 && redValue-blueValue > 20) {  // If red
    //color = 0;
    //for (posA0 = 0; posA0 <= 10; posA0 += 1) {
    //servoA0.write(posA0);             
    //delay(15);                 
    //}

    delay(3000);
    getObject();
    delay(5000);

    //for (posA0 = 10; posA0 >= 0; posA0 -= 1) { 
    //servoA0.write(posA0);              
    //delay(15);
    //}
  } else if (greenValue-redValue > 30 && greenValue-blueValue > 30) {  //If green
    //color = 1;
    for (posA0 = 0; posA0 <= 50; posA0 += 1) {
    servoA0.write(posA0);             
    delay(15);                 
    }

    delay(3000);
    getObject();
    delay(5000);
    
    for (posA0 = 50; posA0 >= 0; posA0 -= 1) { 
    servoA0.write(posA0);              
    delay(15);
    }
  } else if (blueValue-redValue > 100 && blueValue-greenValue > 40) {  //If blue
    //color = 2;
    for (posA0 = 0; posA0 <= 90; posA0 += 1) {
    servoA0.write(posA0);             
    delay(15);                 
    }

    delay(3000);
    getObject();
    delay(5000);

    for (posA0 = 90; posA0 >= 0; posA0 -= 1) { 
    servoA0.write(posA0);              
    delay(15);
    }
  } else {  //If invalid color
    //color = 3;
    for (posA0 = 0; posA0 <= 90; posA0 += 1) {
    servoA0.write(posA0);             
    delay(15);                 
    }

    delay(3000);
    getObject();
    delay(5000);

    for (posA0 = 90; posA0 >= 0; posA0 -= 1) { 
    servoA0.write(posA0);              
    delay(15);
    }
  }
  
}


void getObject() {
  for (posA1 = 0; posA1 <= 70; posA1 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoA1.write(posA1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(500);
  for (posA1 = 70; posA1 >= 0; posA1 -= 1) { // goes from 180 degrees to 0 degrees
    servoA1.write(posA1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}


// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}
// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}
// Function to read Blue Pulse Widths
int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}
