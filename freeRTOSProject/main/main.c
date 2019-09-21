#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

esp_err_t event_handler(void *ctx, system_event_t *event) {
	return ESP_OK;
}

void app_main(void) {

	nvs_flash_init();
	tcpip_adapter_init();
	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	wifi_config_t sta_config = { .sta = { .ssid = CONFIG_ESP_WIFI_SSID,
			.password = CONFIG_ESP_WIFI_PASSWORD, .bssid_set = false } };
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config));
	ESP_ERROR_CHECK(esp_wifi_start());
	ESP_ERROR_CHECK(esp_wifi_connect());

	/* Create one of the two tasks. Note that a real application should check
	 the return value of the xTaskCreate() call to ensure the task was created
	 successfully. */
	xTaskCreatePinnedToCore(vTask1, /* Pointer to the function that implements the task. */
	"Task 1", /* Text name for the task. This is to facilitate
	 debugging only. */
	1000,
	/* Stack depth - small microcontrollers will use much
	 less stack than this. */
	NULL,
	/* This example does not use the task parameter. */
	1,
	/* This task will run at priority 1. */
	NULL,
	/* This example does not use the task handle. */
	0); /* Values 0 or 1 indicate the index number of the CPU which the task should be pinned to */

	/* Create the other task in exactly the same way and at the same priority. */
	xTaskCreatePinnedToCore(vTask2, "Task 2", 1000, NULL, 2, NULL,0);
	/* Start the scheduler so the tasks start executing. */

	for (;;){

		vTaskDelay(1); ///* Delay for a 1 tick period. */
	}

}

