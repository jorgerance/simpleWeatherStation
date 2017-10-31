
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "ThingSpeak.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <DHT.h>
#include <ArduinoOTA.h>

ESP8266WiFiMulti wifiMulti;                                     // Instancia de WifiMulti para gestionar múltiples SSIDs.

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

#define DHTPIN 2
DHT dht(DHTPIN, DHT11, 15);                                     // Definido DHT11. Pasar a 22 en un futuro?

unsigned long myChannelNumber = 352849;
const char * myWriteAPIKey = "XXXXXXXXX";

const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {

  wifiMulti.addAP("XXX", "XXX");            // Listado de SSIDs
  wifiMulti.addAP("XXX", "XXX");

  Serial.begin(115200);

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(1000);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("SSID:\t\t");
  Serial.println(WiFi.SSID());              // SSID al que se ha conectado.
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // IP del ESP8266.
  dht.begin();
  ThingSpeak.begin(client);
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();

  delay(1500);
  float dht_h = dht.readHumidity();
  float dht_t = dht.readTemperature();
  double gamma = log(dht_h / 100) + ((17.62 * dht_t) / (243.5 + dht_t));
  double dp = 243.5 * gamma / (17.62 - gamma);
  float dew_point = dp;
  if (isnan(dht_h) || isnan(dht_t)) {
    Serial.println("Failed to read from DHT11");
    delay(1000);
    return;
  }
  else {
    Serial.print("DHT11 temp:\t");
    Serial.print(dht_t);
    Serial.print(" ºC \n");
    Serial.print("DHT11 humi:\t");
    Serial.print(dht_h);
    Serial.print(" RH \n");
    Serial.print("DHT11 dew_p:\t");
    Serial.print(dp);
    Serial.print(" ºC \n");
  }

  if (!bmp.begin()) {
    Serial.print("Failed to connect to BMP sensor");
    while (1);
  }

  sensors_event_t event;
  bmp.getEvent(&event);

  Serial.print("Pressure:\t");
  Serial.print(event.pressure);
  Serial.print(" hPa\n");

  float seaLevelPressure = 1015;
  Serial.print("Altitude:\t");
  Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
  Serial.println(" m");

  float temperature;
  bmp.getTemperature(&temperature);
  Serial.print("Temperature:\t");
  Serial.print(temperature);
  Serial.print(" ºC \n");

  int ldrValue = analogRead(A0);
  float voltage = ldrValue * (3.3 / 1023.0);
  Serial.print("Light:\t\t");
  Serial.print(voltage);
  Serial.println(" V \n");


  if (client.connect(server, 80)) {
    ThingSpeak.setField(1, event.pressure);
    ThingSpeak.setField(2, temperature);
    ThingSpeak.setField(3, voltage);
    ThingSpeak.setField(4, dht_h);
    ThingSpeak.setField(5, bmp.pressureToAltitude(seaLevelPressure, event.pressure));
    ThingSpeak.setField(6, dew_point);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(600000);
  }

}
