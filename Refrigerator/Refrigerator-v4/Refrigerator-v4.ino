#include <Wire.h>
#include <RTC.h>
#include "Refrigerator.h";

int systemClock = 0;

static int pinDefrost = 0;
static int pinCompressor = 2;
static int pinButton = 3;

bool isPushPressed = false;

unsigned long previousMillis = 0;
const long interval = 1000;

static DS1307 RTC;

Refrigerator fridge;

void setup()
{
  pinMode(pinButton, INPUT_PULLUP);
  Serial.begin(9600);
  fridge.begin(pinDefrost, pinCompressor);
}

void loop()
{
  int sensorValue = analogRead(A0);
  bool pushButton = digitalRead(pinButton);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (pushButtonPressed(pushButton)) {
      fridge.changeTemperature();
    }

    if (systemClock <= 20) {
      systemClock += 1;
    } else {
      systemClock = 0;
    }

    String fridgeStatus = fridge.run(sensorValue, systemClock);
    
    Serial.print("Fridge Status: " + fridgeStatus);
    Serial.print(" Default Temperature: " + (String) fridge.getDefaultTemperature());
    Serial.println(" Current Temperature: " + (String) sensorValue);
  }

}
