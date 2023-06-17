//Datei erstellen mit den variablen onst char* ssid = ""; const char* password = "";
#include "wlan_zugang.h"
#include <WiFi.h>
#include "netzwerk.hpp"
#include "ScaleReader.hpp"

ScaleReader* scaleReader;
netzwerk netzwerksteuerung{};

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting...");

  scaleReader = new ScaleReader();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop(){
  float zustand_in_g = scaleReader->readScale();
  netzwerksteuerung.Sendewasserstand(zustand_in_g);
  delay(5000);
}
