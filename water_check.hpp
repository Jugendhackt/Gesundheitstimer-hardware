#pragma once
#include "Arduino.h"

enum timerstatus:int {
  // Wage leer
  keine_Flasche_vorhanden,
  // Flasche leer
  Flasche_ist_leer,
  // Nichts getrunken, schlage Alarm
  Schlage_Alarm,
  // Genug getunken
  genug_getrunken,
  // Noch nicht genug getrunken, noch nicht nötig
  trinken_nicht_noetig
};

class water_check {
  private:
    unsigned int startMillis;
    double div;
    // Eingestellte Zeit
    int zeit_in_millis;
    // Letztes Gewicht der der Flasche
    double letzte_menge;
    double zielmenge_in_g;
    unsigned int zeitintervall;
  public:
    water_check();
    // permant aufgerufende funktion
    timerstatus water_timer(double menge_in_g);
    void change_settings(double zielmenge, double zeit=60);
    void reset(double menge_in_g);
};