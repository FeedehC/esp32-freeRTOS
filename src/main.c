#include "common.h"

int app_main() {
    //Initial N Value
    N = 2;

    //Init Configure pins
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED) | (1ULL << 18) | (1ULL << 21) | (1ULL << 22) | (1ULL << 23) | (1ULL << 4) | (1ULL << 5) | (1ULL << 19);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    gpio_config_t input_conf;
    input_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    input_conf.mode = GPIO_MODE_INPUT;
    input_conf.pin_bit_mask = (1ULL << 16); //GPIO16 = RX2
    input_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    input_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&input_conf);

    /*
    uart_config_t uart_conf;
    uart_conf.baud_rate = 115200;
    uart_conf.data_bits = UART_DATA_8_BITS;
    uart_conf.parity = UART_PARITY_DISABLE;
    uart_conf.stop_bits = UART_STOP_BITS_1;
    uart_conf.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_conf.rx_flow_ctrl_thresh = 120;
    uart_param_config(UART_NUM_2, &uart_conf);
    */


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
    xTaskCreate(vTaskUpdateN,(const char *)"UpdateN", (unsigned short) STACK_SIZE, NULL, 3, NULL); //Priority 3
    
    //vTaskStartScheduler(); //NO FUNCIONA

    return 0;
}