#include <time.h>

// Battery Class, basically just for keeping the State of each battery
// the status is uploaded to AWS, batterz livecycle can be stopped and resumed 
class Battery{
    public:
        Battery(unsigned long batteryId){
            id = batteryId; 
        };
        bool isRegistered(){
            if
        }
    private:
        unsigned long id;
        /* keeping the values as short to convert later to floats on the getter 
        The ina chips produce 2 digits voltage readings multiplied by 100 the values are handled as shorts.
        A short takes half the memory than a float.
        */
        struct batteryData{ 
            short voltage; // current voltage 
            short initialVoltage; // Voltage before charge
            short topVoltage; // High point mesured (mostly to identify broken chargers going too high)
            short internalResistance; // in mOhm
            short chargedMilliAmpere; // the mAh put into the battery so far
            short disChargedMilliAmpere; // the mAh drained from the Battery
            time_t startChargeTime; // charge start timestamp
            time_t stopChargeTime; // charge stop timestamp
            time_t startDisChargeTime; // charge start timestamp
            time_t stopDisChargeTime; // charge stop timestamp
            char chargingSlot;
            enum state {
                batteryDetcted, //Battery Inserted event
                waitForId, // waiting for id scan
                getStatusFromRemote, //get Battery data from AWS battery might resume if in a resumable state e.g. battery is in Status restInStorage
                charging, // charge up to max
                checkResistance, // mesure internal resistance
                discharging, // full discharge
                charging, // full charge
                checkResistance, // second test for internal resistance after a hard cycle
                rest, // battery rests for the voltage to settle
                recordStorageVoltage, // records the voltage before restInStorage
                restInStorage,  // battery is physically removed and put in storage for 4 weeks to be able to detect self discharge
                checkStorageDrift, // internal discharge is determined by comparing voltage before and after storage
                dischargeToStorageVoltage // battery is discharged to storage voltage, testing is done for this cell
            }
        }
};