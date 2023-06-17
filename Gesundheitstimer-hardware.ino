//Datei erstellen mit den variablen 
//const char* ssid = ""; const char* password = "";
#include "wlan_zugang.h"
#include <WiFi.h>
#include "netzwerk.hpp"
#include "ScaleReader.hpp"
#include "Potentiometer.hpp"

ScaleReader* scaleReader;
netzwerk netzwerksteuerung{};
Potentiometer* potentiometer;


void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting...");


  scaleReader = new ScaleReader();
  potentiometer = new Potentiometer();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop(){
  float zustand_in_g = scaleReader->readScale();

  auto [potentiometer_value, succeeded] = potentiometer->readPotentiometer(); // tuple kram
  if (succeeded) {
    Serial.print("succeeded: ");
    Serial.println(potentiometer_value);
    netzwerksteuerung.Sendepotiwert(potentiometer_value);
  }

  netzwerksteuerung.Sendewasserstand(zustand_in_g);
  delay(100);
}
