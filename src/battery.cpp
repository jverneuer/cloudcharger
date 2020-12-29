#include "battery.h"

// Battery Class, basically just for keeping the State of each battery
// the status is uploaded to AWS, batterz livecycle can be stopped and resumed 
// basically a local statemachine with cloud storage


void Battery::recordMesurenment(float voltage, float current){
    // is called every time a mesurenment has been done.
    //Averages the mesurenments and triggers a message containing those to be pushed to the cloud.
}
void Battery::setInternalResistance(float res){
    // internal resistance reading collected, tasks needs to stop itself
    // if a seperate discharge circuit is used to increase comparability the disharge path on the PCB has to be rerouted to the discharge resistor.
}
void Battery::setId(unsigned long id){
    //set the id and trigger aws lookup
}