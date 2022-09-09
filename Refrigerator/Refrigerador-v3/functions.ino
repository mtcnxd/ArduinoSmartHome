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
}

void setRunningTime()
{
  delay(1500);
  RTC.setHourMode(CLOCK_H24);
  RTC.setDateTime("01-01-2022", "00:00:00");
  Serial.println("New Time Set");
  RTC.startClock();
}

int getRunningHours()
{
  return RTC.getHours();
}

int getRunningMinutes()
{
  return RTC.getMinutes();
}

void makeDefrost()
{
  bool defrost = true;
  int waitingTimer = 0;

  while (defrost) {
    if (waitingTimer <= sleepTime) {
      Serial.println("Defrosting for: " + (String) waitingTimer + " seconds");
      digitalWrite(pinHeater, LOW);
      digitalWrite(pinCompressor, HIGH);
      delay(1000);
      waitingTimer++;
    } else {
      digitalWrite(pinHeater, HIGH);
      digitalWrite(pinCompressor, LOW);
      setRunningTime();
      defrost = false;
    }
  }
}

void cooling(int temperature)
{
  if (temperature >= configTemp) {
    digitalWrite(pinCompressor, LOW);
    digitalWrite(pinHeater, HIGH);
    Serial.println("Current temperature: " + (String) temperature);

  } else {
    bool waiting = true;
    int waitingTimer  = 0;

    while (waiting) {
      digitalWrite(pinCompressor, HIGH);
      if (waitingTimer <= sleepTime) {
        Serial.println("Waiting for: " + (String) waitingTimer + " seconds");
        delay(1000);
        waitingTimer++;
      } else {
        waiting = false;
      }
    }
  }

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

void reconnect()
{
  while (!client.connected()) {
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
