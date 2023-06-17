#pragma once

#include "average_value.hpp"
#include <tuple>

class Potentiometer {
  private:
    const int pin = 34;
    int value;
    averageValue<float, 10> recentReads;
  public:
    Potentiometer();
    std::tuple<float, bool> readPotentiometer();
    bool Stopped();
    void UmrechnenInML();
    float as_percent(float v);
};