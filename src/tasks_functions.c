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

void vTaskDisplayTemperature(){
    bool a,b,c,d;
    unsigned short int temp = 0; 

    // Main loop
    while(true) {
        xQueueReceive(xTempQueue, &temp, portMAX_DELAY);
        //printf("temp = %d", temp);
        //temp = (rand()%MAX_TEMPERATURE);
        //0b00001000;
        a = (temp >= 8);
        temp = temp % 8;
        b = (temp >= 4);
        temp = temp % 4;
        c = (temp >= 2);
        temp = temp % 2;
        d = (temp >= 1);
        temp = temp % 1;
        gpio_set_level(LED, 0);
        gpio_set_level(18, 0);
        gpio_set_level(21, 0);
        gpio_set_level(22, 0);
        gpio_set_level(23, 0);
        vTaskDelay(pdMS_TO_TICKS(DELAY));
        gpio_set_level(LED, 1);
        gpio_set_level(18, a);
        gpio_set_level(21, b);
        gpio_set_level(22, c);
        gpio_set_level(23, d);
        vTaskDelay(pdMS_TO_TICKS(DELAY));
    }
}