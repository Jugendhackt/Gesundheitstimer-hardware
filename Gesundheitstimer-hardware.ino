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

const double LEER = 0.00;

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
	  auto [potentiometer_value, poti_succeeded] = potentiometer->readPotentiometer(); // tuple kram
	  if (poti_succeeded) {
	    Serial.print("Potentiometer value: ");
	    Serial.println(potentiometer_value);
	    netzwerksteuerung.Sendepotiwert(potentiometer_value);
	    WaterCheck->change_settings(potentiometer_value);
	    break;
	  }
  }
  auto[read_succeed, scaleValue] = scaleReader->readScale();
  if (read_succeed) WaterCheck->reset(scaleValue);
}

void loop() {
  auto[read_succeeded,zustand_in_g] = scaleReader->readScale();
  auto action = WaterCheck->water_timer(zustand_in_g);
  switch(action){
    case(keine_Flasche_vorhanden):
      if (read_succeeded) {
        netzwerksteuerung.Sendewasserstand(LEER);
        Serial.println("0 sent!");
      }
    case(Flasche_ist_leer):
      break;
    case(Schlage_Alarm):
      netzwerksteuerung.SendeAlarm(1);
      break;
    case(genug_getrunken):
      WaterCheck->reset(800.00);
      Serial.println("reset to 800");
      break;
    case(trinken_nicht_noetig):
      if (read_succeeded) {
        netzwerksteuerung.Sendewasserstand(zustand_in_g);
      }
      break;
  }/*
  static unsigned int lastTime = millis();
  while (millis() - lastTime > 100) delay(1);
  lastTime = millis();
  */
  //delay(200);
}
