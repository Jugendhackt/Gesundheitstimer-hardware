#pragma once

#include "average_value.hpp"
#include "HX711_ADC.h"
#include "cstdlib"

class ScaleReader {
public:
    ScaleReader();
    std::tuple<bool,float> readScale();
private:
	const int HX711_dout = 4;
	const int HX711_sck = 5;  
	const int calVal_eepromAdress = 0;
	unsigned long t = 0;
  HX711_ADC LoadCell;
  bool filter(float v);
  averageValue<float,2> recentReads;
};