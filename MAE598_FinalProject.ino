#include <Servo.h>

// Initialize variables
int ldrtopr = A0;     // Top-right LDR                          
int ldrtopl = A1;     // Top-left LDR                          
int ldrbotr = A2;     // Bottom-right LDR                     
int ldrbotl = A3;     // Bottom-left LDR                   

Servo servo_updown;
Servo servo_rightleft;

int threshold_value = 30;  // Threshold value for sensitivity
int step_size = 10;        // Adjust the step size for even faster movement

void setup() {
  Serial.begin(9600);  // Serial communication setup

  servo_updown.attach(5);     // Servo motor for up-down movement
  servo_rightleft.attach(6);  // Servo motor for right-left movement
}

void loop() {
  int topr = analogRead(ldrtopr);
  int topl = analogRead(ldrtopl);
  int botr = analogRead(ldrbotr);
  int botl = analogRead(ldrbotl);

  // Calculate average values for elevation and azimuth
  int avgtop = (topr + topl) / 2;
  int avgbot = (botr + botl) / 2;
  int avgleft = (topl + botl) / 2;
  int avgright = (topr + botr) / 2;

  // Calculate differences in elevation and azimuth
  int diffelev = avgtop - avgbot;
  int diffazi = avgright - avgleft;

  // Adjust servo position for azimuth
  if (abs(diffazi) >= threshold_value) {
    if (diffazi > 0) {
      if (servo_rightleft.read() < 180 - step_size) {
        servo_rightleft.write(servo_rightleft.read() + step_size);
      }
    } else {
      if (servo_rightleft.read() > 0 + step_size) {
        servo_rightleft.write(servo_rightleft.read() - step_size);
      }
    }
  }
  
  // Adjust servo position for elevation
  if (abs(diffelev) >= threshold_value) {
    if (diffelev > 0) {
      if (servo_updown.read() < 180 - step_size) {
        servo_updown.write(servo_updown.read() + step_size);
      }
    } else {
      if (servo_updown.read() > 0 + step_size) {
        servo_updown.write(servo_updown.read() - step_size);
      }
    }
  }

  delay(100); // Adjust delay as needed
}
