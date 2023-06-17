#pragma once

#include "HX711_ADC.h"

class ScaleReader {
public:
    ScaleReader();
    float readScale();
private:
	const int HX711_dout = 4;
	const int HX711_sck = 5;  
	const int calVal_eepromAdress = 0;
	unsigned long t = 0;
  HX711_ADC LoadCell;
};

