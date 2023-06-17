#include "Potentiometer.hpp"

#include <Arduino.h>

Potentiometer::Potentiometer() {
  value = 0.0;
}

float Potentiometer::readPotentiometer() {
  value = analogRead(pin);
  return value / 4095.0 * 100;
}