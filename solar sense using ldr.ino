#include <Servo.h>

// Horizontal Servo Motor
Servo horizontal; 
int servohori = 90; // Start at center
int servohoriLimitHigh = 175;
int servohoriLimitLow = 5;

// Vertical Servo Motor
Servo vertical; 
int servovert = 45; 
int servovertLimitHigh = 100;
int servovertLimitLow = 1;

// LDR pin connections
const int ldrlt = A0; // Top Left
const int ldrrt = A3; // Top Right
const int ldrld = A1; // Bottom Left
const int ldrrd = A2; // Bottom Right

void setup() {
  horizontal.attach(2);
  vertical.attach(13);
  
  // Move to initial positions slowly
  horizontal.write(servohori);
  vertical.write(servovert);
  delay(2500); 
}

void loop() {
  int lt = analogRead(ldrlt); // Top left
  int rt = analogRead(ldrrt); // Top right
  int ld = analogRead(ldrld); // Bottom left
  int rd = analogRead(ldrrd); // Bottom right

  // Tuning Parameters
  int dtime = 25; // Increase this (e.g., 50) for even smoother/slower movement
  int tol = 50;   // Lowered tolerance slightly for better accuracy

  int avt = (lt + rt) / 2; // Average Top
  int avd = (ld + rd) / 2; // Average Bottom
  int avl = (lt + ld) / 2; // Average Left
  int avr = (rt + rd) / 2; // Average Right

  int dvert = avt - avd; 
  int dhoriz = avl - avr; 

  // --- Vertical Movement ---
  if (abs(dvert) > tol) {
    if (avt > avd) {
      servovert++;
    } else {
      servovert--;
    }
    servovert = constrain(servovert, servovertLimitLow, servovertLimitHigh);
    vertical.write(servovert);
  }

  // --- Horizontal Movement (Corrected Direction) ---
  if (abs(dhoriz) > tol) {
    // If Left LDRs are brighter than Right LDRs
    if (avl > avr) {
      servohori++; // Moves toward the light
    } else {
      servohori--; // Moves toward the light
    }
    servohori = constrain(servohori, servohoriLimitLow, servohoriLimitHigh);
    horizontal.write(servohori);
  }

  delay(dtime);
}

