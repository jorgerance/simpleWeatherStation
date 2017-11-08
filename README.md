# SWS (Simple Weather Station)
A Simple Weather Station controlled by a NodeMCU dev board writen in Arduino which reports data through ThingSpeak.

## About the ESP8266
Wikipedia:

> The **ESP8266** is a low-cost Wi-Fi chip with full TCP/IP stack and MCU (microcontroller unit) capability produced by Shanghai-based Chinese manufacturer, Espressif Systems.

[Click here to access the full article](https://en.wikipedia.org/wiki/ESP8266)

## Main features
- Humiduty and temperature measurement via **DHT11**.
- Atmospheric pressure and temperature via **BMP180**.
- Luminosity measurement with an **LDR**.
- Multi access point (can manage more than one SSID / password).
- OTA upload (upload new code from the Arduino IDE On The Air, just by using the wifi connection).
- Upload sensor readings to **ThingSpeak**.

## Bill of materials
- 1 x NodeMCU V3 dev board (esp8266): ~2.65 USD.
- 1 x DHT11 sensor: ~1.00 USD.
- 1 x BMP180 sensor: ~1.70 USD.
- 2 x 10K resistors: ~0.10 USD.

**Total cost: 5,45 USD.**

## Schematics

![](https://user-images.githubusercontent.com/22028245/32241498-9380a54c-be70-11e7-8e7f-1704b6ba1354.png)

Since the design is really simple, you can actually mount it directly over a perfoard since there is no real need for a custom made PCB.

![](https://user-images.githubusercontent.com/22028245/32494037-5d68b242-c3c0-11e7-9ada-3190f0d4f6c8.jpg)

## Parameters to be updated on the .ino file

Replace "XXXXXXX" with your API key

    const char * myWriteAPIKey = "XXXXXXX";

Add one of those statements for each SSID you want to be able to connect

	wifiMulti.addAP("SSID", "PASSWORD");

## What to expect once your data has been uploaded to ThingSpeak

![](https://user-images.githubusercontent.com/22028245/32220371-c7f884d2-be31-11e7-877d-fc83b24b0472.png)

Link to the public ThingSpeak channel: [https://thingspeak.com/channels/352849](https://thingspeak.com/channels/352849)
