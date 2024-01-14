idf_component_register(
    SRCS "nerdy_udp_server.c"
    REQUIRES driver esp_event esp_netif
    INCLUDE_DIRS "."
)
