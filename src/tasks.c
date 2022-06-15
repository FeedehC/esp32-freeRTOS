//#include "tasks.h"
#include "common.h"

//Simula un sensor de temperatura, obteniendo valores entre 0 y MAX_TEMPERATURE (30) ºC
void vTaskGetTemperature(){
    uint8_t temperature = 0;
    while(true)
    {
        temperature = (uint8_t) (rand()%MAX_TEMPERATURE); //para obtener valores entre 0 y MAX_TEMPERATURE
		xQueueSend(xTempQueue, &temperature, portMAX_DELAY);	
		vTaskDelay(pdMS_TO_TICKS(DELAY_TEMPERATURE));
    }    
}

void vTaskPrintTemperature(){
    //bool a,b,c,d;
    unsigned short int temp = 0;

    // Main loop
    while(true) {
        xQueueReceive(xTempQueue, &temp, portMAX_DELAY);
        printf("temp = %d", temp);
        gpio_set_level(LED, 0);
        gpio_set_level(18, 0);
        gpio_set_level(21, 0);
        gpio_set_level(22, 0);
        gpio_set_level(23, 0);
        vTaskDelay(pdMS_TO_TICKS(DELAY));
        gpio_set_level(LED, 1);
        gpio_set_level(18, 1);
        gpio_set_level(21, 1);
        gpio_set_level(22, 1);
        gpio_set_level(23, 1);
        vTaskDelay(pdMS_TO_TICKS(DELAY));
    }
}