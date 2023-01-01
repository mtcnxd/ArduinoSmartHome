#include "incubator.h";

unsigned long previousMillis = 0;
const long interval = 2500;

Incubator myIncubator;

void setup()
{
  Serial.begin(9600);
  myIncubator.begin();
}

void loop()
{
  unsigned long currentMillis = millis();

  myIncubator.RunButtons();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    myIncubator.RunMain();
  }

}
