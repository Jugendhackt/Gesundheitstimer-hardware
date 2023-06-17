#include "water_check.hpp"

water_check::water_check() {
  // beginn des Trinkintervalls
  startMillis = millis();
}

timerstatus water_check::water_timer(double menge_in_g) {
  if(menge_in_g < 1) {
    return keine_Flasche_vorhanden;}
  if(menge_in_g < 460){
    return Flasche_ist_leer;}
  auto aktuelle_Zeit = millis();
  if(letzte_menge - menge_in_g > zeitintervall) {
    startMillis = aktuelle_Zeit;
    letzte_menge = menge_in_g;
    return genug_getrunken;}
  if(startMillis + zeitintervall < aktuelle_Zeit){
    return Schlage_Alarm;}
  return trinken_nicht_noetig;
}
void water_check::reset(double menge_in_g){
  startMillis = millis();
  letzte_menge = menge_in_g;
}

void water_check::change_settings(double zielmenge, double zeit) {
  zielmenge_in_g = zielmenge * 1000;
  // Zeit in Millisecunden
  zeitintervall = (unsigned int)zeit * 60 * 1000;
  }