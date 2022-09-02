/*
  FUNCTIONS BLOCKS
*/

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

bool pushButtonPressed(bool pushButton)
{
  bool buttonStatus = false;
  if (pushButton) {
    if (!isPushPressed) {
      buttonStatus = true;
    }
    isPushPressed = true;
  
  } else {
    isPushPressed = false;
  }

  return buttonStatus;
}
