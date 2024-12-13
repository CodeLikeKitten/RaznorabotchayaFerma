#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>
#include <BME280I2C.h>
#include <Wire.h>
#include "SparkFun_SGP30_Arduino_Library.h"
#include <BH1750.h>

#include "pinout.h"
#include "consts.h"

#include <WiFi.h>
#include <NetworkClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>


BME280I2C bme;
BH1750 lightMeter;
SGP30 sgp30;

WebServer server(80);

char output[256];

float temp, hum, pres;
float tempSoil; 
float humiditySoil;
float lux;

void handleRoot() {
  String t;
  t = WebPage();
  server.send(200, "text/html", t);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (sgp30.begin() == false) {
    Serial.println("No SGP30 Detected. Check connections.");
    while (!sgp30.begin());
  }
  sgp30.initAirQuality();

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  lightMeter.begin();


  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);    
  WiFi.setHostname(MyHostName);
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");


  if (MDNS.begin(MyHostName)) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
    Serial.println("ABOABOBASDA");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

long long last_measure_time = 0;

void loop() {

  if (millis() - last_measure_time > meausure_time)
  {
    sgp30.measureAirQuality();
    bme.read(pres, temp, hum);
    makeJSON();
    float adc0 = analogRead(SOIL_MOISTURE);
    float adc1 = analogRead(SOIL_TEMPERATURE);
    tempSoil = ((adc1 / 4095.0 * k_voltage) - 0.5) * 100.0; 
    humiditySoil = map(adc0, air_value, water_value, moisture_0, moisture_100);
    
    lux = lightMeter.readLightLevel();
    Serial.println(output);
    last_measure_time = millis();
  }
  server.handleClient();
}

void makeJSON()
{
  JsonDocument doc;
  doc["temp"] = temp;
  doc["pressure"] = pres;
  doc["humidity"] = hum;
  doc["CO2"] = sgp30.CO2;
  doc["TVOC"] = sgp30.TVOC;
  doc["Soil temperature"] = tempSoil;
  doc["Soil humidity"] = humiditySoil;
  doc["Illumination"] = lux;
  serializeJson(doc, output);
}

String WebPage(){
  String index = "";
  String t;
  t = output;
  index += "<!DOCTYPE html>";
  index += "<html lang='en' class='js-focus-visible'>";
  index += "<head></head>";
  index += "<body><p>";
  index += t;
  index += "</p></body>";
  index += "</html>";
  return index;
}