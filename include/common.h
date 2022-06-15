#ifndef COMMONH
#define COMMONH

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "tasks.h"

#define LED 2 // LED connected to GPIO2
#define DELAY 1000 // milliseconds to delay blink
#define QUEUE_SIZE 10 //Queue size of measures
#define STACK_SIZE 512 //Stack size in words, not bytes
#define DELAY_TEMPERATURE 1000
#define MAX_TEMPERATURE 15

QueueHandle_t xTempQueue;

#endif