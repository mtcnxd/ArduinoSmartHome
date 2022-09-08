#include <Arduino.h>

const char* mqttServer = "io.adafruit.com";
const char* mqttUser   = "mtcnxd";
const char* mqttPassword = "f0dd74b723d90a2ca81a2fc6af57c5e0dc6982e4";
const String mqttClientId = "mtc.nxd@gmail.com";

char msg[50];

int pinDefrost = 0;
int pinCompressor = 2;
int pinButton = 16;
int runningHours = 0;

unsigned long previousMillis = 0;
const long interval = 3000;

int lastMinutes = 0;
