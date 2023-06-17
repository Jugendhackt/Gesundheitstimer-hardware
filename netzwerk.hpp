#pragma once
#include <WiFi.h>
class netzwerk {
private:
const char* serverUrl = "http://192.168.178.34/api/datengeandert";
const int serverPort = 5000;
const char* endpointWasser = "http://192.168.178.34/api/datengeandert";
const char* endpointpoti = "http://192.168.178.34/api/menge";
//const char* endpointbutton = "http://192.168.178.34/api/ok";
const char* endpointAlarm  = "http://192.168.178.34/api/alarm";
IPAddress  serverIP = {192,168,178,34};


  WiFiClient client;
  public:
  void Sendewasserstand(float wasser_in_g);
  void Sendepotiwert(float poti_in_prozent);
  //void Sendebutton();
  void SendeAlarm(float _0_oder_1_);
  


};