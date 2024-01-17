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
#include "nerdy_udp_server.h"
#include "nerdy_mac_address.h"

#define UPDATE_INTERVAL 5000

static const char *TAG = "MAIN";


/**
 * UDP message sending immitation. The messages will be sent in an infinite loop with UPDATE_INTERVAL interval.
*/
void immitate_udp_message_sending() {
    int message_number = 1;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(UPDATE_INTERVAL));
        if (nerdy_wifi_ip_broadcast != NULL) 
        {
            char *message;
            // Build a message, increment message_number 
            asprintf(&message, "{\"mac_address\": \"%s\" , \"message_number\": \"%d\"}\n", nerdy_get_mac_address(), message_number++);
            // Send message
            nerdy_udp_client_send_message(nerdy_wifi_ip_broadcast, UDP_PORT_CLIENT, message);
            // Release message from memory
            free(message);
            // Log to the console
            ESP_LOGI(TAG, "Message is sent to %s %d", nerdy_wifi_ip_broadcast, UDP_PORT_CLIENT);
        }
    }
}

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);

    // Connect ESP32 to a Wi-Fi network. 
    // Change Access Point Name and Password in the config. 
    // Read the README.md or nerdy_wifi/README.md for details!!!
    nerdy_wifi_connect();

    /**
     * We don't have sensors so we will send a mock message
    */
    immitate_udp_message_sending();

    /** Start UDP server (listen to messages)
    * For testing use 
    * socat - UDP-DATAGRAM:255.255.255.255:32411,broadcast 
    * Don't forget to change 32411 to your port, if you change config.
    **/
    // nerdy_udp_server_start(UDP_PORT_SERVER);
}