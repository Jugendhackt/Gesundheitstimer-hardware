#pragma once
#include "Arduino.h"

enum timerstatus:int {
  // Waage leer
  keine_Flasche_vorhanden,
  // Flasche leer
  Flasche_ist_leer,
  // nichts getrunken, schlage Alarm
  Schlage_Alarm,
  // genug getunken
  genug_getrunken,
  // trinken noch nicht nötig
  trinken_nicht_noetig
};

class water_check {
  private:
    unsigned int startMillis;
    double div;
    // eingestellte Zeit
    int zeit_in_millis;
    // letztes Gewicht der Flasche
    double letzte_menge;
    double zielmenge_in_g;
    unsigned int zeitintervall;
  public:
    water_check();
    // permanent aufgerufende Funktion
    timerstatus water_timer(double menge_in_g);
    void change_settings(double zielmenge, double zeit=60);
    void reset(double menge_in_g);
};