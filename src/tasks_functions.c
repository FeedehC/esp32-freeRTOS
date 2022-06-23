//#include "tasks.h"
#include "common.h"

//Simula un sensor de temperatura, obteniendo valores entre 0 y MAX_TEMPERATURE (30) ºC
void vTaskGetTemperature(){
    uint8_t temperature = 0;
    while(true)
    {
        temperature = (uint8_t) (rand()%MAX_TEMPERATURE); //para obtener valores entre 0 y MAX_TEMPERATURE
		xQueueSend(xTempQueue, &temperature, portMAX_DELAY);	
		//vTaskDelay(pdMS_TO_TICKS((DELAY_TEMPERATURE / N)));
        vTaskDelay(pdMS_TO_TICKS(DELAY_TEMPERATURE));
    }    
}

/*
void vTaskDisplayTemperature(){
    bool a,b,c,d;
    unsigned short int temp = 0; 

    // Main loop
    while(true) {
        xQueueReceive(xAveragedQueue, &temp, portMAX_DELAY);
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
}*/

void vTaskDisplayTemperature(){
    bool a,b,c,d,e,f,g;
    uint8_t temp = 0; 
    uint8_t display = 0;

    // Main loop
    while(true) {    
        //xQueueReceive(xAveragedQueue, &temp, portMAX_DELAY);
        xQueueReceive(xTempQueue, &temp, portMAX_DELAY);

        //printf("temp = %d", temp);
        //temp = (rand()%MAX_TEMPERATURE);
        //0b00001000;
        display = symbols[temp];

        //Bitwise AND (Masks)
        a = (display & 0b1) == 0b1;
        b = (display & 0b10) == 0b10;
        c = (display & 0b100) == 0b100;
        d = (display & 0b1000) == 0b1000;
        e = (display & 0b10000) == 0b10000;
        f = (display & 0b100000) == 0b100000;
        g = (display & 0b1000000) == 0b1000000;
        

        gpio_set_level(LED, 0);
        gpio_set_level(4, 0);
        gpio_set_level(5, 0);
        gpio_set_level(18, 0);
        gpio_set_level(19, 0);
        gpio_set_level(21, 0);
        gpio_set_level(22, 0);
        gpio_set_level(23, 0);
        vTaskDelay(pdMS_TO_TICKS(DELAY));
        gpio_set_level(LED, 1);
        gpio_set_level(4, a);
        gpio_set_level(5, b);
        gpio_set_level(18, c);
        gpio_set_level(19, d);
        gpio_set_level(21, e);
        gpio_set_level(22, f);
        gpio_set_level(23, g);
        vTaskDelay(pdMS_TO_TICKS(DELAY));
    }
}

void vTaskSampleAverage(){
    uint8_t i, aux;
    uint16_t accum = 0;
    while(true){
        for(i=0; i<N; i++){
            xQueueReceive(xTempQueue, &aux, portMAX_DELAY);
            accum += aux;
        }
        aux = 0;
        aux = accum / N; //Average
        xQueueSend(xAveragedQueue, &aux, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS((DELAY_TEMPERATURE)));
    }    
}