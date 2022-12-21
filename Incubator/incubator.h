#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

class Incubator
{
    Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
    Servo myservo;
    bool position = true;
    int pinHeater = 10;
    int setPointTemperature = 38;
    int currentTemperature = 0;

  public :
    void begin() {
      myservo.attach(5);
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


  private:
    void showBitcoinPrice(float price) {
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("BITCOIN PRICE");
      display.setTextSize(2);
      display.setCursor(0, 10);
      display.printf("$%.2f", price);
      display.display();
    }

  public :
    void Run() {
      currentTemperature = this->getTemperature();
      Serial.println("Current Temperature: " + (String) currentTemperature);

      if (currentTemperature < setPointTemperature) {
        digitalWrite(pinHeater, HIGH);
        showBitcoinPrice(16912.20);

      } else {
        Serial.println("Waiting...");
        digitalWrite(pinHeater, LOW);

      }

    }

};
