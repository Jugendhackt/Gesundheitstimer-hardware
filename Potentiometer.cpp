#include "Potentiometer.hpp"

#include <Arduino.h>

Potentiometer::Potentiometer() {
  value = 0.0;
  pinMode(32, INPUT_PULLUP);
}

std::tuple<float, bool> Potentiometer::readPotentiometer() {
  value = analogRead(pin);
  value = as_percent(value);
  recentReads.append(value);
  
  if (Stopped()) {
    UmrechnenInML();
    return {value, true};
  }
  return {0, false}; // if nothing should be done
}

bool Potentiometer::Stopped() {
  float avg = recentReads.average();
  float last = recentReads[9];
  return ((avg - last) < 5.0 ); // 5% tolerance
}

float Potentiometer::as_percent(float v) {
  return v / 4095.0 * 100.0; //4095 is max potentiometer value
}

void Potentiometer::UmrechnenInML() {
  value = value * 20; // 2L max
}