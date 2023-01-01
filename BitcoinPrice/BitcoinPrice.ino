#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("LGFridge");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  std::unique_ptr<BearSSL::WiFiClientSecure> client (new BearSSL::WiFiClientSecure);

  client->setInsecure();
  HTTPClient https;

  if (https.begin(*client, "https://api.bitso.com/v3/ticker/?book=btc_usd")) {
    int httpCode = https.GET();

    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();

        const size_t capacity = 2 * JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(2) + 6 * JSON_OBJECT_SIZE(1) + 3 * JSON_OBJECT_SIZE(2) + 2 * JSON_OBJECT_SIZE(4) + 2 * JSON_OBJECT_SIZE(5) + 4 * JSON_OBJECT_SIZE(8) + 550;
        DynamicJsonDocument doc(capacity);

        DeserializationError error = deserializeJson(doc, payload);
        JsonObject obj = doc.as<JsonObject>();

        String book = obj["payload"]["book"];
        String last = obj["payload"]["last"];

        Serial.println(book + " Price: $" + last);
        showDataDisplay(book, last);

      }
    } else {
      Serial.printf("GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("Unable to connect\n");
  }

  delay(5000);

}

void showDataDisplay(String book, String price)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(book);
  display.setTextSize(2);
  display.setCursor(0, 18);
  display.println("$" + price);
  display.display();
}
