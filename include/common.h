#ifndef COMMONH
#define COMMONH

//FreeRTOS and Platformio
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

//C Libs
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Project Includes
#include "tasks_functions.h"

//Constant Parameters
#define LED 2 // LED connected to GPIO2
#define DELAY 1000 // milliseconds to delay blink
#define N 10 //Amount of samples to average
#define TEMP_QUEUE_SIZE 100 //Queue size of raw temperature measures
#define AVG_QUEUE_SIZE 100 //Queue size of averaged
#define STACK_SIZE 512 //Stack size in words, not bytes
#define DELAY_TEMPERATURE 1000 //Milliseconds to delay get temperature measurement
#define MAX_TEMPERATURE 15

//Global Variables
QueueHandle_t xTempQueue;
QueueHandle_t xAveragedQueue;

#endif