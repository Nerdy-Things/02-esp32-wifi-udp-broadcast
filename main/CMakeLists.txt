idf_component_register(
    SRCS "app_main.c"
    REQUIRES nvs_flash esp_wifi esp_event driver nerdy_wifi nerdy_udp_client nerdy_mac_address
    INCLUDE_DIRS "."
)
