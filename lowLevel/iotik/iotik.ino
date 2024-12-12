#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>
#include <BME280I2C.h>
#include <Wire.h>
#include "SparkFun_SGP30_Arduino_Library.h"
#include <BH1750.h>

#define SOIL_MOISTURE    34 // A6
#define SOIL_TEMPERATURE 35 // A7
// откалиброванные значения АЦП
const float air_value    = 1587.0;
const float water_value  = 800.0;
const float moisture_0   = 0.0;
const float moisture_100 = 100.0;

const float k_voltage = 6.27; // коэффициент поправки напряжения АЦП ESP32 для ~4.45В

BME280I2C bme;
BH1750 lightMeter;
SGP30 sgp30;


char output[256];

float temp, hum, pres;
float tempSoil; // АЦП разрядность (12) = 4095 
float humiditySoil;
float lux;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
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
}

void loop() {
  sgp30.measureAirQuality();
  bme.read(pres, temp, hum);
  makeJSON();
  float adc0 = analogRead(SOIL_MOISTURE);
  float adc1 = analogRead(SOIL_TEMPERATURE);
  tempSoil = ((adc1 / 4095.0 * k_voltage) - 0.5) * 100.0; // АЦП разрядность (12) = 4095 
  humiditySoil = map(adc0, air_value, water_value, moisture_0, moisture_100);
  
  lux = lightMeter.readLightLevel();
  Serial.println(output);

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
