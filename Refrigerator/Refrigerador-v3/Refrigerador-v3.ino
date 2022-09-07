#include "definitions.h";
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <Wire.h>
#include <RTC.h>

static DS1307 RTC;
ESP8266WiFiMulti WiFiMulti;

void setup()
{
  initialSetup();
  setupWifiConnection();
  setRunningTime();
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    bool pushButton = !digitalRead(pinPush);

    if (pushButtonPressed(pushButton)) {
      saveTemperature(0, temperature);
      Serial.println("Temperature: " + (String) temperature);

      if (temperature >= maximumTemp) {
        temperature = minimunTemp;
      } else {
        temperature += 1;
      }
    }

    int runningTime = getRunningTime();

    if (inArray(runningTime, hoursToDefrost)) {
      //sendPostData();
      makeDefrost();

    } else {
      digitalWrite(pinHeater, HIGH);
      int sensorValue = analogRead(A0);
      sensorValue = map(sensorValue, 0, 1024, 10, 30);
      cooling(sensorValue);

    }
  }
}
