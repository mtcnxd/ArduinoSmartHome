#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP085.h>

class Incubator
{
    Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
    Adafruit_BMP085 bmp;
    int setPointTemperature = 30;
    int pinHeater = 10;
    int pinBuzzer = 16;
    int pinPush = 13;
    int pinLed = 15;
    int selectedMode = 1;
    float currentValue = 0;    
    bool pressed = false;

  public :
    void begin() {
      bmp.begin();
      pinMode(pinBuzzer, OUTPUT);
      pinMode(pinLed, OUTPUT);
      pinMode(pinPush, INPUT_PULLUP);
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      delay(500);
      display.clearDisplay();
    }

  private:
    float getTemperature() {
      digitalWrite(pinLed, HIGH);
      delay(10);
      digitalWrite(pinLed, LOW);
      return bmp.readTemperature();
    }

  private:
    float getAltitude() {
      digitalWrite(pinLed, HIGH);
      delay(10);
      digitalWrite(pinLed, LOW);
      return bmp.readAltitude();
    }

  private:
    float getPressure() {
      digitalWrite(pinLed, HIGH);
      delay(10);
      digitalWrite(pinLed, LOW);
      return bmp.readPressure();
    }

  private :
    void beepTone() {
      digitalWrite(pinBuzzer, HIGH);
      delay(200);
      digitalWrite(pinBuzzer, LOW);
    }

  private:
    void selectMode()
    {
      Serial.println("change Mode");
      if (selectedMode >= 3) {
        selectedMode = 1;
      } else {
        selectedMode++;
      }
      this->beepTone();
    }

  private :
    void showDataDisplay(String title, float value)
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 5);
      display.println(title);
      display.setTextSize(2);
      display.setCursor(0, 18);
      display.printf("%.2f", value);
      display.display();
    }

  public:
    void RunButtons() {
      bool pushButtonPressed = !digitalRead(pinPush);
      delay(50);

      if (pushButtonPressed && !pressed) {
        this->selectMode();
        pressed = true;
      } else if (!pushButtonPressed && pressed) {
        pressed = false;
      }
    }

  public :
    void RunMain() {
      if (selectedMode == 1) {
        currentValue = this->getTemperature();
        this->showDataDisplay("TEMPERATURE (C)", currentValue);
        Serial.println("current Temperature: " + (String) currentValue);
      }

      if (selectedMode == 2) {
        currentValue = this->getAltitude();
        this->showDataDisplay("ALTITUDE (M)", currentValue);
        Serial.println("current Altitude: " + (String) currentValue);
      }

      if (selectedMode == 3) {
        currentValue = this->getPressure();
        this->showDataDisplay("PRESSURE (Pa)", currentValue);
        Serial.println("current Pressure: " + (String) currentValue);
      }

    }

};
