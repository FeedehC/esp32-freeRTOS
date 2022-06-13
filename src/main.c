#include <driver/gpio.h>
// Include FreeRTOS for delay
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED 2 // LED connected to GPIO2
#define DELAY 1000 // milliseconds to delay blink

int app_main() {
    // Configure pin
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED) | (1ULL << 18) | (1ULL << 21) | (1ULL << 22) | (1ULL << 23);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    // Main loop
    while(true) {
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