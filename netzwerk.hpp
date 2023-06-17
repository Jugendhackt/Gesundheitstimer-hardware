#pragma once
#include <WiFi.h>
class netzwerk {
private:
const char* serverUrl = "http://192.168.178.34/api/datengeandert";
const int serverPort = 5000;
const char* endpoint = "http://192.168.178.34/api/datengeandert";
IPAddress  serverIP = {192,168,178,34};


  WiFiClient client;
  public:
  void Sendewasserstand(float wasser_in_g);

};