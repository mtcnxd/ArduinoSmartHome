/*
  FUNCTIONS BLOCKS
*/

void setRunningTime()
{
  delay(1500);
  RTC.setHourMode(CLOCK_H24);
  RTC.setDateTime("01-01-2022", "00:00:00");
  Serial.println("Set running time: OK");
  RTC.startClock();
}

void showRunningTime()
{
  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.println(RTC.getSeconds());
}

int getRunningHours()
{
  return RTC.getHours();
}

int getRunningMinutes()
{
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

void reconnect()
{
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection: ");
    Serial.println(mqttServer);

    if (client.connect(mqttClientId.c_str(), mqttUser, mqttPassword)) {
      Serial.println("connected to server");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
