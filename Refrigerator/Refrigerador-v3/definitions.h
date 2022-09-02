/*
  VARS DEFINITIONS
*/

int timeToDefrost = 1;  // minutes
int defrostTime   = 60; // seconds
int configTemp    = 18; // centigrados
int temperature   = 15; // Testing only

const char* ssid = "LINKSYS";
const char* password = "100%smart";

bool ledStatus  = false;
bool isPushPressed = false;

static int resistor  = 0;  // pin D3
static int compresor = 2;
static int pinPush   = 16; // pin D0

unsigned long previousMillis = 0;
const long interval = 1000;

int minimunTemp = 15;
int maximumTemp = 20;
