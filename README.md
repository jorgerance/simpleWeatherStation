# sws
Simple weather station controlled by an NodeMCU writen on Arduino uploading data to ThingSpeak.

## Main features:
- Humiduty and temperature measurement via **DHT11**.
- Atmospheric pressure and temperature via **BMP180**.
- Luminosity measurement with an **LDR**.
- Multi access point (can manage more than one SSID / password).
- OTA upload (upload new code from the Arduino IDE On The Air, just by using the wifi connection).
- Upload sensor readings to **ThingSpeak**.

## List of components:
- 1 x NodeMCU V3 dev board: ~2,65 USD.
- 1 x DHT11 sensor: ~1,00 USD.
- 1 x BMP180 sensor: ~1,70 USD.
- 2 x 10K resistors: ~0,10 USD.

**Total cost: 5,45 USD.**

# Parameters to be updated on the .ino file

Replace "XXXXXXX" with your API key:

    const char * myWriteAPIKey = "XXXXXXX";
    
Add one of those statements for each SSID you want to be able to connect:

	wifiMulti.addAP("SSID", "PASSWORD");

What to expect once your data has been uploaded to ThingSpeak:

![](https://user-images.githubusercontent.com/22028245/32220371-c7f884d2-be31-11e7-877d-fc83b24b0472.png)
