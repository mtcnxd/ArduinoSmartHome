/*
  FUNCTIONS BLOCKS
*/

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
    Serial.print(".");
    delay(500);
  }
  randomSeed(micros());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setRunningTime()
{
  delay(1500);
  RTC.setHourMode(CLOCK_H24);
  RTC.setDateTime("01-01-2022", "00:00:00");
  Serial.println("Set running time: OK");
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

bool pushButtonPressed(bool pushButton)
{
  bool isPushPressed = false;
  bool buttonPressed = false;
  
  if (pushButton && !isPushPressed) {
    buttonPressed = true;
  } else {
    isPushPressed = false;
  }

  return buttonPressed;
}
