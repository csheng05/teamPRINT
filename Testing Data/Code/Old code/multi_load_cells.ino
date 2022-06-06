#include "HX711-multi.h"
#include "HX711.h"

#define DOUT1  3   //load cell
#define DOUT2  4   //strain guage
#define CLK  2

#define TARE_TIMEOUT_SECONDS 4

byte DOUTS[2] = {DOUT1, DOUT2};

#define CHANNEL_COUNT sizeof(DOUTS)/sizeof(byte)

long int results[CHANNEL_COUNT];

HX711MULTI scales(CHANNEL_COUNT, DOUTS, CLK);

float force_calibration_factor = -22400;

void setup() {
  Serial.begin(115200);
  Serial.flush();

  tare();
}

void tare() {
  bool tareSuccessful = false;

  unsigned long tareStartTime = millis();
  while (!tareSuccessful && millis()<(tareStartTime+TARE_TIMEOUT_SECONDS*1000)) {
    tareSuccessful = scales.tare(20,10000);
  }
}

void sendRawData() {
  scales.read(results);
  for (int i=0; i<scales.get_count(); ++i) {
    Serial.print(-results[i]);
    Serial.print((i!=scales.get_count()-1)?"\t":"\n");
  }
  delay(10);
}

void loop() {
  sendRawData();

  if (Serial.available()>0) {
    while (Serial.available()) {
      Serial.read();
    }
    tare();
  }
 

}
