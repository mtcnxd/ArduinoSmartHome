#include <Wire.h>
#include <RTC.h>

static DS1307 RTC;

const int ledPin = LED_BUILTIN;
const int releCompresor = 12;
const int releDefrost = 14;

void setup() {
  RTC.begin();
  Serial.begin(9600);
  pinMode(releCompresor, OUTPUT);
  pinMode(releDefrost, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Serial.print("Time: ");
  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.println();
  
  digitalWrite(releCompresor, HIGH);
  digitalWrite(releDefrost, LOW);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(releCompresor, LOW);
  digitalWrite(releDefrost, HIGH);
  digitalWrite(ledPin, LOW);
  delay(1000);

}
