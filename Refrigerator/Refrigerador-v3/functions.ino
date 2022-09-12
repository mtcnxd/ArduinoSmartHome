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
  client.publish("mtcnxd/feeds/refrigerator", "Defrosting");
  Serial.println("Starting defrost");
  digitalWrite(pinHeater, LOW);
  digitalWrite(pinCompressor, HIGH);
  timerInMinutes(12);
  digitalWrite(pinHeater, HIGH);
  setRunningTime();
}

void cooling(int temperature)
{
  if (temperature >= configTemp) {
    digitalWrite(pinCompressor, LOW);
    Serial.println("Current temperature: " + (String) temperature);

  } else {
    Serial.println("Turning off compressor");
    digitalWrite(pinCompressor, HIGH);
    timerInMinutes(12);
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

void timerInMinutes(int minutes)
{
  bool isWaiting = true;
  int minutesWaiting = 1;

  while (isWaiting) {
    int currentMinutes = getRunningMinutes();
    if (currentMinutes != previousMinutes) {
      Serial.println("Waiting for: " + (String) minutesWaiting + " minutes");
      previousMinutes = currentMinutes;
      minutesWaiting ++;

    } else {
      if (minutesWaiting == minutes) {
        isWaiting = false;
      }
      delay(1000);
    }
  }
}

void reconnect()
{
  while (!client.connected()) {
    if (client.connect(mqttClientId.c_str(), mqttUser, mqttPassword)) {
      Serial.println("connected to server");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}
