/*
  FUNCTIONS BLOCKS
*/

void initialSetup()
{
  delay(500);
  pinMode(pinPush, INPUT_PULLUP);
  pinMode(pinHeater, OUTPUT);
  pinMode(pinCompressor, OUTPUT);
  digitalWrite(pinHeater, HIGH);
  digitalWrite(pinCompressor, HIGH);
  Serial.begin(9600);
  RTC.begin();
  EEPROM.begin(512);
}

void setupWifiConnection()
{
  int connection = 0;
  Serial.println("Connecting to: " + (String) ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    if (connection > 30) {
      Serial.println("WiFi connected: ERROR");
      break;
    }
    connection ++;
    randomSeed(micros());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void setRunningTime()
{
  delay(1500);
  Serial.println("Setting Time");
  RTC.setHourMode(CLOCK_H24);
  RTC.setDateTime("01-01-2022", "00:00:00");
  Serial.println("New Time Set");
  RTC.startClock();
}

int getRunningTime()
{
  Serial.print("Running time: ");
  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.print(RTC.getSeconds());
  Serial.println();
  return RTC.getMinutes();
}

void makeDefrost()
{
  bool defrost = true;
  int currentTime = 0;

  while (defrost) {
    if (currentTime <= defrostTime) {
      Serial.println("Making defrost " + (String) currentTime + " seconds");
      digitalWrite(pinHeater, LOW);
      digitalWrite(pinCompressor, HIGH);
      currentTime++;
      delay(1000);
    } else {
      digitalWrite(pinHeater, HIGH);
      digitalWrite(pinCompressor, LOW);
      defrost = false;
    }
  }
}

void cooling(int temperature)
{
  if (temperature >= configTemp) {
    Serial.println("Sensor value: " + (String) temperature );
    digitalWrite(pinCompressor, LOW);

  } else {
    digitalWrite(pinCompressor, HIGH);
    Serial.println("Compressor sleep for ten minutes");
  }
}

void sendPostData()
{
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;
    String urlPost = "https://io.adafruit.com/api/v2/webhooks/feed/t1WWe4s8Qxq4BV3d4rFBdqHwKfXR/raw";

    if (http.begin(client, urlPost)) {
      int httpCode = http.GET();

      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("Unable to connect\n");
    }
  }
}

void saveTemperature(int addr, int val)
{
  EEPROM.write(addr, val);
}

byte getTemperature(byte addr)
{
  return EEPROM.read(addr);
}

bool inArray(int currentHour, int vector[])
{
  for (int i = 0; i <= sizeof(vector); i++) {
    if (currentHour == vector[i]) {
      return true;
    }
  }
  return false;
}

bool pushButtonPressed(bool pushButton)
{
  bool buttonPressed = false;
  if (pushButton) {
    if (!isPushPressed) {
      buttonPressed = true;
    }

  } else {
    isPushPressed = false;
  }

  return buttonPressed;
}
