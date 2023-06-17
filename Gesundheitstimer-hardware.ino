//Datei erstellen mit den variablen 
//const char* ssid = ""; const char* password = "";
#include "wlan_zugang.h"
#include <WiFi.h>
#include "netzwerk.hpp"
#include "ScaleReader.hpp"
#include "Potentiometer.hpp"
#include "water_check.hpp"

ScaleReader* scaleReader;
netzwerk netzwerksteuerung{};
Potentiometer* potentiometer;
water_check* WaterCheck;

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting...");


  scaleReader = new ScaleReader();
  potentiometer = new Potentiometer();
  WaterCheck = new water_check();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  delay(2000);
  while (true) {
  auto [potentiometer_value, succeeded] = potentiometer->readPotentiometer(); // tuple kram
  if (succeeded) {
    Serial.print("succeeded: ");
    Serial.println(potentiometer_value);
    netzwerksteuerung.Sendepotiwert(potentiometer_value);
    WaterCheck->change_settings(potentiometer_value);
    break;
  }
  }
  WaterCheck->reset(scaleReader->readScale());
}

void loop(){
  

  float zustand_in_g = scaleReader->readScale();

  auto action = WaterCheck->water_timer(zustand_in_g);
  switch(action){
    case(keine_Flasche_vorhanden):
    case(Flasche_ist_leer):
    break;
    case(Schlage_Alarm):
    netzwerksteuerung.SendeAlarm(1);
    break;
    case(genug_getrunken):
    break;
    case(trinken_nicht_noetig):
    netzwerksteuerung.Sendewasserstand(zustand_in_g);
    break;
  }

  delay(100);
}
