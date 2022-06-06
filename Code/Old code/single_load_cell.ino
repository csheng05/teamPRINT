#include "HX711.h"

#define DOUT  3
#define CLK  2

HX711 scale;

float calibration_factor = -22400;

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare();

  long zero_factor = scale.read_average();

}

void loop() {
  scale.set_scale(calibration_factor);
  while(!Serial.availableForWrite()){}
  float data = scale.get_units();
  if (data<100) Serial.print('0');
  if (data<10) Serial.print('0');
  if (data<0){
    data=0;
  }
  Serial.print(scale.get_units(), 2);
  Serial.println();
 

}
