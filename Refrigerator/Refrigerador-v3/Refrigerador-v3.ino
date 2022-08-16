#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <RTC.h>

int timeToDefrost = 2;  // in minutes
int defrostTime   = 60; // in seconds
int configTemp    = 20; // in centigrados

const char* ssid = "LINKSYS";
const char* password = "100%smart";

static int resistor  = 0; // pin D0
static int compresor = 2; // pin D4

static DS1307 RTC;
ESP8266WiFiMulti WiFiMulti;

void setup()
{
  pinMode(resistor, OUTPUT);
  pinMode(compresor, OUTPUT);
  Serial.begin(9600);
  RTC.begin();
  setRunningTime();
  setupWifiConnection();
}

void loop()
{
  int runningTime = getRunningTime();

  if (runningTime == timeToDefrost) {
    sendPostData();
    makeDefrost();

  } else {
    int sensorValue = analogRead(A0);
    Serial.println("Sensor value: " + (String) sensorValue );
    if (sensorValue <= configTemp) {
      digitalWrite(compresor, HIGH);
    } else {
      digitalWrite(compresor, LOW);
      Serial.println("Compresor sleep for ten minutes");
    }
  }

  delay(1000);
}