/*
 * Example2Task.c
 *
 *  Created on: Sep 21, 2019
 *      Author: amit
 */
//#include "esp_log.h"
//Logging Tag
//static const char *LOG = "Task2";

#include "stdlib.h"
#include "stddef.h"
#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"

void vTask2( void *pvParameters )
{
	const char *pcTaskName = "I am task 2\r\n";
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s",pcTaskName);
		/* Delay for a 1 tick period. */
		vTaskDelay(1);
	}
}
