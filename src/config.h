#include <Arduino.h>
#include <Adafruit_INA219.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

unsigned char chargingslots = 4; 
#define highPriority ( tskIDLE_PRIORITY + 2 )
#define mediumPriority ( tskIDLE_PRIORITY + 1 )
#define mainQUEUE_LENGTH 10

static Adafruit_INA219 ina219;
static TaskHandle_t turnLedOffHandle = NULL;
static TaskHandle_t turnLedOnHandle = NULL;
static QueueHandle_t xQueue = NULL;



// Queue message schema
struct batteryValues{
    float value;
    unsigned long batteryId;
    char unit;
};

//Mux Config
// order from lowest to highest
int mux1DataPins[4] = {46 ,47,48,49};  
int mux1WriteEnablePin = 23;
int mux1IoPin = 22;


