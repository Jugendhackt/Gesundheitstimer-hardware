	/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017
   -------------------------------------------------------------------------------------
*/

/*
   Settling time (number of samples) and data filtering can be adjusted in the config.h file
   For calibration and storing the calibration value in eeprom, see example file "Calibration.ino"

   The update() function checks for new data and starts the next conversion. In order to acheive maximum effective
   sample rate, update() should be called at least as often as the HX711 sample rate; >10Hz@10SPS, >80Hz@80SPS.
   If you have other time consuming code running (i.e. a graphical LCD), consider calling update() from an interrupt routine,
   see example file "Read_1x_load_cell_interrupt_driven.ino".

   This is an example sketch on how to use this library
*/

#include "ScaleReader.hpp"
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

ScaleReader::ScaleReader():LoadCell{HX711_dout, HX711_sck} {
    LoadCell.begin();
	  //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
	  float calibrationValue; // calibration value (see example file "Calibration.ino")
	  calibrationValue = 411.83; // uncomment this if you want to set the calibration value in the sketch
	#if defined(ESP8266)|| defined(ESP32)
	  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
	#endif
	  //EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

	  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
	  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
	  LoadCell.start(stabilizingtime, _tare);
	  if (LoadCell.getTareTimeoutFlag()) {
	    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
	    while (1);
	  }
	  else {
	    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
	    Serial.println("Startup is complete");
	  }
	}

std::tuple<bool,float> ScaleReader::readScale() {
  // get smoothed value from the dataset:
  if (LoadCell.update()) {
    float i = LoadCell.getData();
    if (i < 2) {
      i = 0;
    }
    if (!filter(i)) {
      if (lastIsSame) return {false, i};
      lastIsSame = true;
      return {true, i};
    }
    lastIsSame = false;
    recentReads.append(i);
    Serial.print("Load_cell output val: ");
    Serial.println(i);
    return {false, i};
  }
  return {false, recentReads[0]};
}

bool ScaleReader::filter(float v) {
  float avg = recentReads.average();
  return abs(v - avg) > 2;
}