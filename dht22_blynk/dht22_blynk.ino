#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define DHTPIN 3      
#define DHTTYPE DHT22

char auth[] = "12345678";
char ssid[] = "Narzo 20";
char pass[] = "87654321";

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  dht.begin();
}

void loop() 
{
  Blynk.run();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();      

  if (isnan(temperature) || isnan(humidity)) 
  {
    Serial.println("Failed to read from DHT22 sensor");
    return;
  }

  Blynk.virtualWrite(T1, temperature); 
  Blynk.virtualWrite(H1, humidity);    

  delay(1000); 
}
