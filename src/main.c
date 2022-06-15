#include "common.h"

int app_main() {
    // Configure pin
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED) | (1ULL << 18) | (1ULL << 21) | (1ULL << 22) | (1ULL << 23);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    xTempQueue = xQueueCreate((UBaseType_t) QUEUE_SIZE, sizeof(uint8_t));
    if( xTempQueue == NULL )
    {
        // Queue was not created and must not be used.
        return 0;
    }

    xTaskCreate(vTaskGetTemperature,(const char *)"Sensor", (unsigned short) STACK_SIZE, NULL, 4, NULL); //Priority 1
    xTaskCreate(vTaskPrintTemperature,(const char *)"Print", (unsigned short) STACK_SIZE, NULL, 4, NULL); //Priority 1
    vTaskStartScheduler();

    return 0;
}