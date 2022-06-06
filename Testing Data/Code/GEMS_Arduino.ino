#include "HX711.h"
 
#define DOUT  3 //load cell
#define CLK  2  //load cell
#define DOUT2  4 //strain guage
#define CLK2  5 //strain guage
 
HX711 scale1;
HX711 scale2;
 
float force_calibration_factor = -22400;
 
void setup() {
  Serial.begin(115200);
  scale1.begin(DOUT, CLK);
  scale1.set_scale(force_calibration_factor);
  scale1.tare();
 
  scale2.begin(DOUT2, CLK2, 32);
  scale2.set_scale();
  scale2.tare();
 
 
}
 
void loop() {
  scale1.set_scale(force_calibration_factor);
  while(!Serial.availableForWrite()){}
  float force = scale1.get_units();
  float r = scale2.get_units();
  if (force<100) Serial.print('0');
  if (force<10) Serial.print('0');
  if (force<0){
    force=0;
  }
  Serial.print(scale1.get_units(), 2);
  Serial.print(',');
  if (r<100) Serial.print('0');
  if (r<10) Serial.print('0');
  if (r<0){
    r=0;
  }
  Serial.print(scale2.get_units(), 5);
  Serial.println();
}
