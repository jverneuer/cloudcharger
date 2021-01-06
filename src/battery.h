#include <time.h>
#ifndef BATTERY_H
#define BATTERY_H

class Battery {
    private:
        unsigned long id;
        unsigned char chargingSlot;
        /* keeping most values as short to convert later to floats on the getter 
        The ina chips produce 2 digits voltage readings multiplied by 100 the values are handled as shorts.
        A short takes half the memory than a float.
        */
        struct batteryData{ 
            short voltage; // current voltage 
            short initialVoltage; // Voltage before current cycle
            short topVoltage; // High point mesured (mostly to identify broken chargers going too high)
            short internalResistance; // in mOhm
            short chargedMilliAmpere; // the mAh put into the battery so far
            short disChargedMilliAmpere; // the mAh drained from the Battery
            time_t startChargeTime; // charge start timestamp
            time_t stopChargeTime; // charge stop timestamp
            time_t startDisChargeTime; // charge start timestamp
            time_t stopDisChargeTime; // charge stop timestamp
            enum state {
                batteryDetcted, //Battery Inserted event
                waitForId, // waiting for id scan
                getStatusFromRemote, //get Battery data from AWS battery might resume if in a resumable state e.g. battery is in Status restInStorage
                initialCharge, // charge up to max
                checkResistance, // mesure internal resistance
                discharging, // full discharge
                capacityTestCharge, // full charge
                rest, // battery rests for the voltage to settle
                recordStorageVoltage, // records the voltage before restInStorage
                restInStorage,  // battery is physically removed and put in storage for 4 weeks to be able to detect self discharge
                checkStorageDrift, // internal discharge is determined by comparing voltage before and after storage
                dischargeToStorageVoltage // battery is discharged to storage voltage, testing is done for this cell
            };
        };
    public:
        void recordMesurenment( float voltage, float current);
        void setInternalResistance( float res);
        void setId( unsigned long id);

};

#endif