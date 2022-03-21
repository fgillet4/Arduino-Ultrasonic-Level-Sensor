// Covid Sensor!
// Author: Francis Gillet
// Date 03/21/2022
// Description: Measure the flowrate over a weir using water level and height of wier

#include <LCD16x2.h> // Library from Olimex LCD 16*2 screen
#include <Wire.h>

// Pins and variables

int trigPIN = 4; // Trigger US pulse
int echoPIN = 5 ; // Echo received US pulse
double duration = 0; // This is a function of speed of sound that will map the distance
double speedOfSound_US = 0.001; // ft/micro second
double speedOfSound_SI = 0.000343 // m/micro second
double distance_meters = 0; // distance sensor is from the waters edge
double distance_feet = 0;
double length_total = 6; // [meter](Measured out in field sensor to bottom)
double water_height = 0; // changes as more or less water flows through
const double weir_height = 2.9;// in meters
double flowrate_cum = 0; //
double flowrate_liters = 0;
const double velocity = 0.1 //
const double friction_constant = 0.5
const double weir_width = 0.8 //meters
double water_tower_height = 0; // storing the pressure
LCD16x2 lcd; //Declare the lcd panel as an object to be able to interact with its library

int buttons; //not sure

void setup(){
  Serial.begin(9600);
  Wire.begin();
  lcd.lcdClear();
  pinMode(trigPIN, OUTPUT); //Sets the trigPIN as the outputsignal
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
  distance_meters = distance_feet * 0.3048;
  water_tower_height = length_total - weir_height - distance_meters;
  flowrate_cum = (weir_width*pow((2*9.81*water_tower_height + pow(velocity,2)),(3/2)))/(3*9.81)- weir_width*pow(velocity,3)/(3*9.81)
  flowrate_liters = flowrate_cum*1000
  Serial.println(flowrate_liters);
  
  
  lcd.lcdGoToXY(2,1);
  lcd.lcdWrite(distance_meters);
  lcd.lcdGoToXY(2,2);
  lcd.lcdWrite("L/s");
  //Serial.println(duration);
  //Serial.println(distance_meters);
  Serial.println(flowrate_liters);
  delay(500);

}
