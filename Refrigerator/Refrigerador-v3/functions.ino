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

void setRunningTime()
{
  delay(1500);
  Serial.println("Setting Time");
  RTC.setHourMode(CLOCK_H24);
  RTC.setDateTime("01-01-2023", "00:00:00");
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
  int currentTime = 0;

  if (currentTime <= defrostTime) {
    while (defrost) {
      Serial.println("Making defrost " + (String) currentTime + " seconds");
      digitalWrite(pinHeater, LOW);
      digitalWrite(pinCompressor, HIGH);
      delay(1000);
      currentTime++;
    }
    defrost = false;

  } else {
    digitalWrite(pinHeater, HIGH);
    digitalWrite(pinCompressor, LOW);
  }

}

void cooling(int temperature)
{
  Serial.println("Current temperature: " + (String) temperature);

  if (temperature >= configTemp) {
    digitalWrite(pinCompressor, LOW);

  } else {
    bool waiting = true;
    int counter = 0;

    while (waiting) {
      digitalWrite(pinCompressor, HIGH);
      if (counter < 600) {
        Serial.println("Turn off compressor: " + (String) counter);
        counter++;
        delay(1000);
      } else {
        waiting = false;
      }
    }
  }
  
}

void saveTemperature(int addr, int val)
{
  EEPROM.write(addr, val);
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
