
# Video instruction

[![Video instruction](/images/02_thumbnail.png)](https://youtu.be/bdTmS5Z1Oo4)

# Medium article

[Medium.com](https://medium.com/@gektor650/esp-idf-esp32-udp-broadcasts-messages-through-the-wi-fi-4a7f3d75d8ea)

# Wi-Fi connection configuration

1. Copy `nerdy_wi_fi_config.c.example` to `nerdy_wi_fi_config.c`
2. Replace `SSID_NAME` and `SSID_PASSWORD` with your Wi-Fi credentials:
```c
#define WIFI_SSID "Your_access_point_name_should_be_here" // SET YOUR WI-FI ACCESS POINT NAME HERE
#define WIFI_PWD "Your_access_point_passwoed_should_be_here" // SET YOUR WI-FI PASSWORD HERE
```