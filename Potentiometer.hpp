#pragma once

class Potentiometer {
  private:
    const int pin = 34;
    int value;
  public:
    Potentiometer();
    float readPotentiometer();
};