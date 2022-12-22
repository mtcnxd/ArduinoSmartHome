#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

class Incubator
{
    Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
    Servo myservo;
    bool position = true;
    int pinHeater = 10;
    int pinBuzzer = 16;
    int setPointTemperature = 38;
    int currentTemperature = 0;
    int contador = 0;

  public :
    void begin() {
      myservo.attach(5);
      pinMode(pinBuzzer, OUTPUT);
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      display.clearDisplay();
    }

  private:
    int getTemperature() {
      currentTemperature = analogRead(A0);
      return map(currentTemperature, 0, 1024, 0, 100);
    }

  private:
    void moveServoMotor(bool position) {
      if (position) {
        for (int i = 0; i <= 180; i++) {
          myservo.write(i);
          delay(10);
        }

      } else {
        for (int i = 180; i >= 0; i--) {
          myservo.write(i);
          delay(10);
        }
      }

    }

  private :
    void beepTone() {
      for (int i = 0; i <= 2; i++) {
        digitalWrite(pinBuzzer, HIGH);
        delay(200);
        digitalWrite(pinBuzzer, LOW);
        delay(200);
      }
    }


  private:
    void showCounter(int price) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print(price);
      display.display();
    }

  public :
    void Run() {
      currentTemperature = this->getTemperature();
      Serial.println("Current counter: " + (String) contador);

      if (currentTemperature < setPointTemperature) {
        digitalWrite(pinHeater, HIGH);

        if (contador > 50) {
          contador = 0;
          beepTone();
        } else {
          showCounter(contador);
          contador ++;
        }

      } else {
        Serial.println("Waiting...");
        digitalWrite(pinHeater, LOW);

      }

    }

};
