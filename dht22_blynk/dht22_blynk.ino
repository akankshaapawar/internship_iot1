#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define DHTPIN 3   // DHT22 sensor connected to GPIO pin 3   
#define DHTTYPE DHT22     // DHT type

char auth[] = "12345678";          //your authority token
char ssid[] = "Narzo 20";          //your wifi ssid
char pass[] = "87654321";          //your wifi password

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(115200);      //baud rate for serial monitor
  Blynk.begin(auth, ssid, pass);       //blynk connection

  dht.begin();               //sensor begin
}

void loop() 
{
  Blynk.run();

  float temperature = dht.readTemperature();         // Read temperature in Celsius
  float humidity = dht.readHumidity();               // Read humidity

  if (isnan(temperature) || isnan(humidity))         //If either the temperature or humidity value is NaN(not a valid number)
  {
    Serial.println("Failed to read from DHT22 sensor");     //prints to the Serial Monitor
    return;
  }

  Blynk.virtualWrite(T1, temperature);       // Send temperature value to T1
  Blynk.virtualWrite(H1, humidity);          // Send humidity value to H1


  delay(1000);      // Update every 1 seconds
}
