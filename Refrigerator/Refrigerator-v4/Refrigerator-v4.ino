#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <RTC.h>
#include "Refrigerator.h";

int pinDefrost = 0;
int pinCompressor = 2;
int pinButton = 16;
int runningHours = 0;

unsigned long previousMillis = 0;
const long interval = 1000;

const char* ssid = "LINKSYS";
const char* password = "100%smart";

Refrigerator fridge;
DS1307 RTC;
ESP8266WiFiMulti WiFiMulti;

void setup()
{
  pinMode(pinButton, INPUT_PULLUP);
  Serial.begin(9600);
  fridge.begin(pinDefrost, pinCompressor);
  setupWifiConnection();
  setRunningTime();
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    bool pushButton = digitalRead(pinButton);
    if (pushButtonPressed(pushButton)) {
      fridge.changeTemperature();
    }

    if (runningHours <= 20) {
      runningHours += 1;
    } else {
      runningHours = 0;
    }

    int currentTemperature = analogRead(A0);
    String fridgeStatus = fridge.run(currentTemperature, runningHours);

    Serial.print("Fridge Status: " + fridgeStatus);
    Serial.print(" Config Temperature: " + (String) fridge.getConfiguredTemperature());
    Serial.println(" Current Temperature: " + (String) currentTemperature);
  }

}
