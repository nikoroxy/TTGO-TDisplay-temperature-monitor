# TTGO T-Display Temperature Monitor

That's my Arduino IDE project, it provides some code who may help someone writing his own.

### Prerequisites 

- Arduino IDE with ESP32 board installed ([How to?](https://github.com/espressif/arduino-esp32))

### Installing

1. Install and configure `TFT_eSPI` and `Button2` libraries ([How to?](https://github.com/Xinyuan-LilyGO/TTGO-T-Display))
2. Install `OneWire` and `DallasTemperature` libraries (ArduinoIDE > Sketch > Include Library > Manage Libraries)
3. Install `SPIFFS` FS and upload the fonts using ArduinoIDE > Tools > ESP32 Sketch Data Upload ([How to?](https://github.com/me-no-dev/arduino-esp32fs-plugin))
4. Compile and flash the sketch.

(DS18B20 D+ wire is set to PIN 27, refer to pinout to know where it is.)

![Imgur](https://i.imgur.com/RmWBstQ.jpg)
