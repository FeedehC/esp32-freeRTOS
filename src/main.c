#include "common.h"

int app_main() {
    //Init Configure pins
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED) | (1ULL << 18) | (1ULL << 21) | (1ULL << 22) | (1ULL << 23) | (1ULL << 4) | (1ULL << 5) | (1ULL << 19);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    xTempQueue = xQueueCreate((UBaseType_t) TEMP_QUEUE_SIZE, sizeof(uint8_t));
    xAveragedQueue = xQueueCreate((UBaseType_t) AVG_QUEUE_SIZE, sizeof(uint8_t));
    if( xTempQueue == NULL || xAveragedQueue == NULL )
    {
        // Queue was not created and must not be used.
        return 0;
    }

    xTaskCreate(vTaskGetTemperature,(const char *)"Sensor", (unsigned short) STACK_SIZE, NULL, 1, NULL); //Priority 1
    xTaskCreate(vTaskSampleAverage,(const char *)"SampleAverage", (unsigned short) STACK_SIZE, NULL, 2, NULL); //Priority 2
    xTaskCreate(vTaskDisplayTemperature,(const char *)"Display", (unsigned short) STACK_SIZE, NULL, 1, NULL); //Priority 1
    
    //vTaskStartScheduler(); //NO FUNCIONA

    return 0;
}