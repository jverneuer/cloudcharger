#include "muxManager.h"
#include <Arduino.h>

// constructor sets up the adress spaces for the MUX storing the information
// in private variables, so they cant be changed during runtime, if that is needed a new instance of the class shoulkd
// be created to ensure consistent functionality
MuxManager::MuxManager(int data[4], int we, int io){
    for (int i = 0; i < 3; i++) {
        dataPins[i] = data[i];
    }
    writeEnablePin = we;
    ioPin = io;
};

// makes sure all pins are in the right setting as they might have been reused 
// for other things in the meantime
void MuxManager::init(ioMode mode){
    pinMode(writeEnablePin, OUTPUT); 
    // set the data pins to output
    for (int i = 0; i < 3; i++) {
        pinMode(dataPins[i], OUTPUT); 
    }
    setMode(mode);
};

// sets the mode between read and write, helper function to be used internally
void MuxManager::setMode(ioMode mode){
    // setting the Mode of the IO Pin depending on the task at hand
    if(mode = write){
        pinMode(ioPin, OUTPUT);
    }
    else{
        pinMode(ioPin, INPUT);
    }
};

// sets the adress of the selected channnel, the mapping represents the 4 bit adress space,
// can be done more elegant or by sledgehammer using a mapping tablke like demonstrated here.

void MuxManager::setChannel(int channel){
    init(read);
    // channel adress mapping
    int muxChannel[16][4]={
        {LOW,LOW,LOW,LOW}, //channel 0
        {HIGH,LOW,LOW,LOW}, //channel 1
        {LOW,HIGH,LOW,LOW}, //channel 2
        {HIGH,HIGH,LOW,LOW}, //channel 3
        {LOW,LOW,HIGH,LOW}, //channel 4
        {HIGH,LOW,HIGH,LOW}, //channel 5
        {LOW,HIGH,HIGH,LOW}, //channel 6
        {HIGH,HIGH,HIGH,LOW}, //channel 7
        {LOW,LOW,LOW,HIGH}, //channel 8
        {HIGH,LOW,LOW,HIGH}, //channel 9
        {LOW,HIGH,LOW,HIGH}, //channel 10
        {HIGH,HIGH,LOW,HIGH}, //channel 11
        {LOW,LOW,HIGH,HIGH}, //channel 12
        {HIGH,LOW,HIGH,HIGH}, //channel 13
        {LOW,HIGH,HIGH,HIGH}, //channel 14
        {HIGH,HIGH,HIGH,HIGH}  //channel 15
    };
    // set the 4 Bit to select the channel
    for (int i = 0; i < 3; i++) {
        digitalWrite(dataPins[i], muxChannel[channel][i]);
    }
};

// reads the value at the given Channel and returns a digital Value
// could be extended to support Analog reads 
int MuxManager::readPin(int channel){
    setChannel(channel);
    setMode(read);
    return digitalRead(ioPin);
};

// sets the data pin on the given channel
void MuxManager::writePin(int channel, int data){
    setChannel(channel);
    setMode(write);
    digitalWrite(ioPin, data);
}
// shorthand for readPin
int MuxManager::r(int channel){
    return readPin(channel);
};

// shorthand for writePin
void MuxManager::w(int channel, int data){
    writePin(channel, data);
}
