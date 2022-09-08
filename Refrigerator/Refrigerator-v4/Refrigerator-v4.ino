#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <RTC.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Refrigerator.h";
#include "definitions.h";

Refrigerator fridge;
DS1307 RTC;

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  pinMode(pinButton, INPUT_PULLUP);
  Serial.begin(9600);
  WiFiManager wifiManager;
  wifiManager.autoConnect("LGFridge");
  client.setServer(mqttServer, 1883);
  fridge.begin(pinDefrost, pinCompressor);
  setRunningTime();
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  showRunningTime();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    bool pushButton = digitalRead(pinButton);
    if (pushButtonPressed(!pushButton)) {
      fridge.changeTemperature();
    }

    int runningHours = getRunningMinutes();
    int currentTemperature = analogRead(A0);
    String fridgeStatus = fridge.run(currentTemperature, runningHours);

    int runningMinutes = getRunningMinutes();
    Serial.println("Running Minutes: " + (String) runningMinutes);

    if (runningMinutes != lastMinutes) {
      lastMinutes = runningMinutes;
      snprintf (msg, 50, "%ld", currentTemperature);
      client.publish("mtcnxd/feeds/refrigerator", msg);
    } else {
      //Serial.print("Fridge Status: " + fridgeStatus);
      //Serial.print(" Config Temperature: " + (String) fridge.getConfiguredTemperature());
      //Serial.println(" Current Temperature: " + (String) currentTemperature);

    }

  }

}
