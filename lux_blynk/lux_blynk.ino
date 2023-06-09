#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <RTClib.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "ABCD1234";                     // Your Blynk authentication token
char ssid[] = "YourNetworkName";              // Your wifi ssid
char password[] = "YourNetworkPassword";      // Your wifi password

BH1750 lightMeter;                           // BH1750 sensor
RTC_DS3231 rtc;                              // DS3231 RTC module

#define VIRTUAL_PIN_LUX V1               // Initializing virtual pin in Blynk for LUX
#define VIRTUAL_PIN_TIME V2              // Initializing virtual pin in Blynk for Time

void setup()
{
  Serial.begin(9600);                    // baud rate for serial monitor
  
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);        // Initialize BH1750 sensor and provides continuous light intensity measurements with high resolution.
  rtc.begin();                          // Initialize DS3231 RTC module

  Blynk.begin(auth, ssid, password);      // Connect to WiFi
}

void loop()
{
  Blynk.run();
  
  float lux = lightMeter.readLightLevel();         // Read light intensity
  DateTime now = rtc.now();                        // Read time from RTC
  String time = now.timestamp(DateTime::TIMESTAMP_TIME);    // retrieves the current time from the DS3231 RTC module and store it as a string for further processing or displaying

  
  Blynk.virtualWrite(VIRTUAL_PIN_LUX, lux);          // Send light intensity to Blynk app
  Blynk.virtualWrite(VIRTUAL_PIN_TIME, time);        // Send time to Blynk app

  delay(1000);       // Update every second
}
