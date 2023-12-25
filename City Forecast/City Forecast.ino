#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>      
#include "SSD1306Wire.h"

const char* ssid = ""; // Enter WiFi name
const char* password = ""; // Enter WiFi password

const String startpoint = "http://api.openweathermap.org/data/2.5/weather?q=";
const String endpoint = "&APPID=";
const String key = ""; // Enter yout API key

String City = "";
String line = "";
String temp_str = "";
String humidity_str = "";

WiFiClient wifi_client;
HTTPClient http_Webclient;

StaticJsonDocument<1024> doc;

SSD1306Wire display(0x3c, SDA, SCL);


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println();

  WiFi.begin(ssid, password);

  display.init();
      
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  // Wait for the Wi-Fi connection
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i);
    Serial.print(".");
  }
  Serial.println("Connection established!");

  Serial.print("Enter city name : "); // City forecast you want 

}

void loop() {
  if (Serial.available()) {
      String city = Serial.readStringUntil('\n');
      Serial.println(city);
      City = city;
  }
  if ((WiFi.status() == WL_CONNECTED) && (City.length() > 0 )) {
    Serial.println("Start Connection to server...");
    
    http_Webclient.begin(wifi_client, startpoint + City + endpoint + key);
    int httpCode = http_Webclient.GET();

    if (httpCode > 0) {
      Serial.printf("Req. from a client is handled by the server: Code = %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http_Webclient.getString();
        Serial.println(payload);
        line = http_Webclient.getString();
      }
    }
    else {
      Serial.printf("HTTP Connection failed : %s\n", http_Webclient.errorToString(httpCode).c_str());
    }
    http_Webclient.end();
    
  }
  DeserializationError error = deserializeJson(doc, line);

  JsonObject weather_0 = doc["weather"][0];
  String weather = weather_0["main"];
  double temperature = doc["main"]["temp"];
  double humidity = doc["main"]["humidity"];

  temp_str += "Temperature : ";
  temp_str += String(temperature - 273.15);
  
  humidity_str += "Humidity : ";
  humidity_str += String(humidity);

  display.drawString(0, 0, "City: " + City);
  display.drawString(0, 15, "Weather: " + weather);
  display.drawString(0, 30, temp_str);
  display.drawString(0, 45, humidity_str);
  display.display();

  delay(20000);
  
  // Text Initialization 
  display.clear();
  weather = "";
  temp_str = "";
  humidity_str = "";
   
}
