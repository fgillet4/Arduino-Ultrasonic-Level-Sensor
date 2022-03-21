// Covid Sensor!
// Author: Francis Gillet
// Date 03/30/2021
// Description: Stay 6 feet away from me! Ultrasonic sensor will measure distance and prinbt to the lcd if someone comes too close!

#include <LCD16x2.h> // Library from Olimex LCD 16*2 screen
#include <Wire.h>

// Pins and variables

int trigPIN = 4; // Trigger US pulse
int echoPIN = 5 ; // Echo received US pulse
double duration = 0; // This is a function of speed of sound that will map the distance
double speedOfSound = 0.001; // ft/micro second
double distance_meters = 0;
double distance_feet = 0;
LCD16x2 lcd; //Declare the object

int buttons;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  lcd.lcdClear();
  pinMode(trigPIN, OUTPUT);
  pinMode(echoPIN, INPUT);
}
void loop(){

  digitalWrite(trigPIN, LOW);
  delayMicroseconds(5); 
  digitalWrite(trigPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPIN, LOW);
  pinMode(echoPIN, INPUT);
  duration = pulseIn(echoPIN, HIGH);
  distance_feet = (duration*speedOfSound)/2;
  distance_feet = round(distance_feet);
  //distance_feet = distance_meters /0.3048;
  lcd.lcdGoToXY(2,1);
  lcd.lcdWrite(distance_feet);
  lcd.lcdGoToXY(2,2);
  lcd.lcdWrite("Feet");
  //Serial.println(duration);
  //Serial.println(distance_meters);
  Serial.println(distance_feet);
  delay(500);

}
