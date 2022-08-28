/*
  FUNCTIONS BLOCK 
*/

void setupWifiConnection()
{
  delay(10);
  Serial.println("Connecting to: " + (String) ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  randomSeed(micros());

  Serial.println("WiFi connected: OK");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
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
      Serial.println("Making defrost while " + (String) currentTime + " seconds");
      digitalWrite(resistor, HIGH);
      currentTime++;
      delay(1000);
    } else {
      digitalWrite(resistor, LOW);
      defrost = false;
    }
  }
}

void sendPostData()
{
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;
    String urlPost = "http://test.fortech.mx/wservice/webhook.php";

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

bool inArray(int hours, int vector[]) 
{
  Serial.println(sizeof(vector));
  for (int i = 0; i <= sizeof(vector); i++) {
    if (hours == vector[i]) {
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
    isPushPressed = true;

  } else {
    isPushPressed = false;
  }
  
  return buttonPressed;
}


bool toggleOutput(bool pushButton)
{
  if (pushButton) {
    if (!isPushPressed) {
      if (ledStatus) {
        ledStatus = false;
        Serial.println("LED Status: " + (String) ledStatus);

      } else {
        ledStatus = true;
        Serial.println("LED Status: " + (String) ledStatus);
      }
    }
    isPushPressed = true;

  } else {
    isPushPressed = false;
  }

  return ledStatus;
}
