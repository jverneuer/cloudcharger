
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <battery.h>

#define unsigned char	chargingslots = 4; 

#define turnLedOffPriority ( tskIDLE_PRIORITY + 2 )
#define turnLedOnPriority ( tskIDLE_PRIORITY + 1 )
#define mainQUEUE_LENGTH 10

static Adafruit_INA219 ina219;
static TaskHandle_t turnLedOffHandle = NULL;
static TaskHandle_t turnLedOnHandle = NULL;
static QueueHandle_t xQueue = NULL;


struct batteryValues{
    float value;
    unsigned long batteryId;
    char unit;
};


void turnLedOff(void * pvParameters){
  for (;;){
    struct batteryValues val;
    if (xQueueReceive(xQueue, &val, portMAX_DELAY) == pdPASS) {
      digitalWrite(A0, LOW); 
    }
    vTaskDelay( 100 / portTICK_PERIOD_MS );
  }
}

void turnLedOn(void * pvParameters){
  for (;;){
    struct batteryValues currentValue;
    digitalWrite(A0, HIGH);
    currentValue.value = ((float) random(0,400))/100;
    currentValue.unit = 'A';
    xQueueSend(xQueue, &currentValue, portMAX_DELAY);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
  }
}
void ina219Test(void * pvParameters){
  for (;;){
    int status = ina219.begin();
    if(!status){
      Serial.println("ina not ready skipping one tick");
      // ina not ready postpone 1 tick
      vTaskDelay(1);
    }
    /*Serial.println("Busvoltage");
    

    Serial.println("getShuntVoltage_mV");
    Serial.println(ina219.getShuntVoltage_mV() );


    Serial.println("getPower_mW");
    Serial.println(ina219.getPower_mW() );

    Serial.println("getShuntVoltage_mV");
    Serial.println(ina219.getShuntVoltage_mV() );
    Serial.println("getCurrent_mA()");
    Serial.println(ina219.getBusVoltage_V() );
    Serial.println(ina219.getCurrent_mA());
*/
    Serial.println(ina219.getBusVoltage_V() );
    Serial.println(ina219.getCurrent_mA());
    digitalWrite(A2, HIGH);
    vTaskDelay( 500 / portTICK_PERIOD_MS );    
    digitalWrite(A2, HIGH);
    vTaskDelay( 500 / portTICK_PERIOD_MS );    

  }
}


void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  ina219.setCalibration_32V_2A ();
  xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof(struct  batteryValues) );
  if( xQueue == NULL ){
        Serial.println("Failed to create main Queue");
  }

  xTaskCreate(turnLedOff,
            "ledOff",
            256,
            NULL, 
            turnLedOffPriority,
            &turnLedOffHandle);

  xTaskCreate(turnLedOn,
            "ledOnn",
            256,
            NULL, 
            turnLedOffPriority,
            &turnLedOnHandle);

    xTaskCreate(ina219Test,
            "ina219Test",
            256,
            NULL, 
            turnLedOffPriority,
            &turnLedOffHandle);

  /* Start the tasks and timer running. */
   vTaskStartScheduler(); 

  pinMode(A2, OUTPUT); 


  pinMode(A0, OUTPUT); 
}


void loop() {}