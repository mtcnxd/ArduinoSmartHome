/*
  VARS DEFINITIONS
*/
int hoursToDefrost[] = {6, 12, 18, 23};
int defrostTime   = 600; // seconds (10 mins)
int configTemp    = 18; // centigrados
int temperature   = 15; // Testing only

const char* ssid = "LINKSYS";
const char* password = "100%smart";

bool ledStatus  = false;
bool isPushPressed = false;

static int pinHeater    = 0;  // pin D3
static int pinCompressor = 2;
static int pinPush   = 16; // pin D0

unsigned long previousMillis = 0;
const long interval = 1000;

int minimunTemp = 15;
int maximumTemp = 20;
