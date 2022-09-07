class Refrigerator
{
    int defaultTemperature = 170;
    int compressorPin, defrostPin;

  public:
    void begin(int compressorPin, int defrostPin)
    {
      pinMode(compressorPin, OUTPUT);
      pinMode(defrostPin, OUTPUT);
    }

  public:
    void changeTemperature() {
      if (defaultTemperature > 20) {
        defaultTemperature  = 15;
      } else {
        defaultTemperature += 1;
      }
    }

  public:
    int getConfiguredTemperature()
    {
      return defaultTemperature;
    }

  public:
    int sleepingTimer()
    {
      int sleepCounter = true;
      bool sleepingMode = true;

      while (sleepingMode) {
        if (sleepCounter < 60 ) {
          sleepCounter++;
        } else {
          sleepCounter = 0;
          sleepingMode = false;
        }
      }
    }

  public:
    String coolingMode(int currTemperature)
    {
      if (currTemperature > defaultTemperature) {
        sleepingTimer();
        digitalWrite(compressorPin, HIGH);
        return "Waiting 10 minutes";
      } else {
        digitalWrite(compressorPin, LOW);
        return "Cooling";
      }
    }

  public:
    void defrostMode(bool defrostStatus)
    {
      if (defrostStatus) {
        digitalWrite(defrostPin, HIGH);
      } else {
        digitalWrite(defrostPin, LOW);
        defrostStatus = false;
      }
    }

  public:
    String run(int currentTemperature, int runningTime)
    {
      if (runningTime == 6) {
        defrostMode(true);
        return "Defrost";

      } else {
        defrostMode(false);
        return coolingMode(currentTemperature);

      }
    }

};
