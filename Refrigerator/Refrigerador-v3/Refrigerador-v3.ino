#include "definitions.h";
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <RTC.h>

static DS1307 RTC;
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  WiFiManager wifiManager;
  wifiManager.autoConnect("LG_Fridge");
  RTC.begin();
  initialSetup();
  client.setServer(mqttServer, 1883);
  setRunningTime();
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int runningHours = getRunningHours();
    if (runningHours >= 6) {
      makeDefrost();

    } else {
      int currentTemperature = analogRead(A0);
      currentTemperature = map(currentTemperature, 0, 1024, 0, 255);
      cooling(currentTemperature);
      
      int runningMinutes = getRunningMinutes();
      if (runningMinutes != previousMinutes) {
        previousMinutes = runningMinutes;
        snprintf (payload, 30, "%ld", currentTemperature);
        client.publish("mtcnxd/feeds/refrigerator", payload);
      }

    }
  }
}
