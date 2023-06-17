//Datei erstellen mit den variablen onst char* ssid = ""; const char* password = "";
#include "wlan_zugang.h"
#include <WiFi.h>
#include "netzwerk.hpp"

netzwerk netzwerksteuerung{};
void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop(){
  netzwerksteuerung.Sendewasserstand(233.5);
  delay(5000);

  
}
