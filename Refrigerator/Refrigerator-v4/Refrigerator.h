class Refrigerator
{
    int defaultTemperature = 170;
    int compressorPin = 0;
    int defrostPin = 2;

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
    int getDefaultTemperature()
    {
      return defaultTemperature;
    }

  public:
    String coolingMode(int currTemperature)
    {
      if (currTemperature > defaultTemperature) {
        digitalWrite(compressorPin, HIGH);
        return "Cooling";
      } else {
        digitalWrite(compressorPin, LOW);
        return "Waiting";
      }
    }

  public:
    void defrostMode(bool defrostStatus)
    {
      if (defrostStatus) {
        digitalWrite(defrostPin, HIGH);
      } else {
        digitalWrite(defrostPin, LOW);
      }
    }

  public:
    String run(int currTemperature, int runningTime)
    {
      if (runningTime > 20) {
        defrostMode(true);
        return "Defrost";

      } else {
        defrostMode(false);
        return coolingMode(currTemperature);

      }
    }

};
