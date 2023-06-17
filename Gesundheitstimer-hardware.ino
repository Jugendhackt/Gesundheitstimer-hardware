#include "ScaleReader.hpp"

ScaleReader* scaleReader;

void setup() {
  Serial.begin(57600); delay(10);
	Serial.println();
	Serial.println("Starting...");
  scaleReader = new ScaleReader();
}

void loop() {
	scaleReader->readScale();
}
