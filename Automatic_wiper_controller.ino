// Electronic Buzz
// The Automatic car wiper code was written by Prajwal.S.Navalagi
// Updated version with full servo rotation and improved logic

#include <Servo.h>

Servo wiperServo1;  // Main wiper servo
Servo wiperServo2;  // Secondary wiper servo

int rainSensorValue = 0;
const int dryThreshold = 800;    // No rain - wipers off
const int lightRainThreshold = 600;  // Light rain - slow wipers
const int mediumRainThreshold = 460; // Medium rain - medium speed
// Below mediumRainThreshold - heavy rain - fast wipers

void setup() {
  Serial.begin(9600);
  wiperServo1.attach(9);
  wiperServo2.attach(10);
  
  // Initialize servos to parked position
  wiperServo1.write(0);
  wiperServo2.write(0);
  delay(1000);
}

void loop() {
  rainSensorValue = analogRead(A0);
  Serial.print("Rain sensor value: ");
  Serial.println(rainSensorValue);
  
  if (rainSensorValue > dryThreshold) {
    // Dry conditions - park wipers
    wiperServo1.write(0);
    wiperServo2.write(0);
    delay(1000);
  } 
  else if (rainSensorValue > lightRainThreshold) {
    // Light rain - slow wipe (every 2 seconds)
    wipe(180, 15);  // Full 180 degree wipe with slow speed
    delay(2000);
  } 
  else if (rainSensorValue > mediumRainThreshold) {
    // Medium rain - medium speed wipe (every 1 second)
    
    wipe(180, 10);  // Full 180 degree wipe with medium speed
    delay(1000);
  } 
  else {
    // Heavy rain - fast continuous wipe
    wipe(180, 5);  // Full 180 degree wipe with fast speed
    delay(100);
  }
}

// Function to perform a wiping motion
void wipe(int degrees, int speedDelay) {
  // Move from 0 to specified degrees
  for (int pos = 0; pos <= degrees; pos += 1) { 
    wiperServo1.write(pos);  
    wiperServo2.write(pos);             
    delay(speedDelay);        
  }
  
  // Move back from degrees to 0
  for (int pos = degrees; pos >= 0; pos -= 1) { 
    wiperServo1.write(pos);  
    wiperServo2.write(pos);            
    delay(speedDelay);                   
  }
}
