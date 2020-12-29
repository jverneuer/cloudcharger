#include "battery.h"

// Battery Class, basically just for keeping the State of each battery
// the status is uploaded to AWS, batterz livecycle can be stopped and resumed 
// basically a local statemachine with cloud storage

void Battery::recordMesurenment(char chargingSlot, float voltage, float current){

}
void Battery::setInternalResistance(char chargingSlot, float res){

}
void Battery::setId(char chargingSlot, unsigned long id){

}