#include <config.h>
#include <Wire.h>
#include <battery.h>
#include <muxManager.h>

MuxManager mesurenmentSelector(mux1DataPins, mux1WriteEnablePin, mux1IoPin); 

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
            highPriority,
            &turnLedOffHandle);

  xTaskCreate(turnLedOn,
            "ledOnn",
            256,
            NULL, 
            highPriority,
            &turnLedOnHandle);

    xTaskCreate(ina219Test,
            "ina219Test",
            256,
            NULL, 
            highPriority,
            &turnLedOffHandle);

  /* Start the tasks and timer running. */
   vTaskStartScheduler(); 

}


void loop() {}