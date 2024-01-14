#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <inttypes.h>
#include <string.h>
#include "config.h"
#include "nerdy_wifi.h"
#include "nerdy_udp_client.h"
#include "nerdy_mac_address.h"

#define UPDATE_INTERVAL 5000

static const char *TAG = "MAIN";

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);

    nerdy_wifi_connect();

    int message_number = 1;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(UPDATE_INTERVAL));
        if (nerdy_wifi_ip_broadcast != NULL) 
        {
            char *message;
            asprintf(&message, "{\"mac_address\": \"%s\" , \"message_number\": \"%d\"}\n", nerdy_get_mac_address(), message_number++);

            nerdy_udp_client_send_message(nerdy_wifi_ip_broadcast, UDP_PORT, message);

            free(message);

            ESP_LOGI(TAG, "Message is sent to %s %d", nerdy_wifi_ip_broadcast, UDP_PORT);
        }
    }
}
