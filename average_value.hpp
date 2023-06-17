#pragma once

#include "Arduino.h"

template<typename T, size_t SIZE>
class averageValue{
  private:
    T samples[SIZE];
  public:
    averageValue() = default;
    averageValue(const T& initValue){
      for(size_t i = 0; i < SIZE;i++){
        samples[i] = initValue;
      }
    }
    void append(T newVal){
      for(size_t i = 1; i < SIZE;i++){
        samples[i-1] = samples[i];
      }
      samples[SIZE-1] = newVal;
    }
    void operator<<(T newVal){
      append(newVal);
    }
    T& operator[](size_t index){
      assert(index < SIZE);
      return samples[index];
    }
    const T& operator[](size_t index) const{
      assert(index < SIZE);
      return samples[index];
    }
    T average() const{
      T val = samples[0];
      for(size_t i = 1; i < SIZE; i++){
        val += samples[i];
      }
      return val/SIZE;
    }
};