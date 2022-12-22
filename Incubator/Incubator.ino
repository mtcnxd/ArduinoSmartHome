#include "incubator.h";

unsigned long previousMillis = 0;
const long interval = 500;

Incubator myIncubator;

void setup()
{
  Serial.begin(9600);
  myIncubator.begin();
}


void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    myIncubator.Run();
  }

}
