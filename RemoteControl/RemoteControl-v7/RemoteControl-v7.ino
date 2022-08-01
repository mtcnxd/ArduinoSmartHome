#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "Definitions.h"

void setup() {
  pinMode(pin, OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP());
  digitalWrite(pin, HIGH);
}
void loop(void) {
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  client.print(String("GET ") + path + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: keep-alive\r\n\r\n");
  delay(500); // wait for server to respond
  String section = "header";

  while (client.available()) {
    String line = client.readStringUntil('\r');
    // Serial.print(line);    // we’ll parse the HTML body here

    if (section == "header") { // headers..
      Serial.print(".");
      if (line == "\n") { // skips the empty space at the beginning
        section = "json";
      }
    }
    else if (section == "json") { // print the good stuff
      section = "ignore";
      String result = line.substring(1);      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);

      if (!json_parsed.success()) {
        Serial.println("parseObject() failed");
        return;
      }

      // Aqui se agregara la funcion de validacion fisica
      

      // Make the decision to turn off or on the LED
      if (strcmp(json_parsed["light"], "true") == 0) {
        digitalWrite(pin, LOW);
        Serial.println("LED ON");
      } else {
        digitalWrite(pin, HIGH);
        Serial.println("led off");
      }
    }
  }
  Serial.print("closing connection. ");
}
