#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Replace with your network info
const char* ssid = "your SSID";
const char* password = "your PASSWORD";

// Replace with your MQTT broker IP address
const char* mqttServer = "MQTT SERVER IP";
const int mqttPort = 1883;
const char* mqttUser = "your MQTT USERNAME";
const char* mqttPassword = "your MQTT PASSWORD";

// Create an instance of the BME280 sensor
Adafruit_BME280 bme;

// Create an instance of the MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

const int NUM_READINGS = 10;    // Constants for statistics representation

float temperatureReadings[NUM_READINGS];    // Array to store temperature readings

// Connect to Wi-Fi and MQTT broker
void connectToWiFi() {
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectToMQTT() 
{
  client.setServer(mqttServer, mqttPort);
  
  while (!client.connected()) 
  {
    Serial.println("Connecting to MQTT...");
  
    if (client.connect("arduinoClient", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed with state: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

// Read temperature from the sensor
float readTemperature() 
{
  return bme.readTemperature();
}

// Calculate statistics
float calculateAverage() 
{
  float sum = 0;
  for (int i = 0; i < NUM_READINGS; i++) 
  {
    sum += temperatureReadings[i];
  }
  return sum / NUM_READINGS;
}

float calculateMinimum() 
{
  float minTemp = temperatureReadings[0];
  for (int i = 1; i < NUM_READINGS; i++) 
  {
    if (temperatureReadings[i] < minTemp) 
    {
      minTemp = temperatureReadings[i];
    }
  }
  return minTemp;
}

float calculateMaximum() 
{
  float maxTemp = temperatureReadings[0];
  for (int i = 1; i < NUM_READINGS; i++) 
  {
    if (temperatureReadings[i] > maxTemp) 
    {
      maxTemp = temperatureReadings[i];
    }
  }
  return maxTemp;
}

// Publish statistics to the MQTT topic
void publishStatistics(float avgTemp, float minTemp, float maxTemp) 
{
  char avgStr[8];
  char minStr[8];
  char maxStr[8];
  
  sprintf(avgStr, "%.2f", avgTemp);
  sprintf(minStr, "%.2f", minTemp);
  sprintf(maxStr, "%.2f", maxTemp);
  
  client.publish("temperature/average", avgStr);
  client.publish("temperature/minimum", minStr);
  client.publish("temperature/maximum", maxStr);
}

void setup() 
{
  Serial.begin(115200);
  
  // Connect to Wi-Fi and MQTT broker
  connectToWiFi();
  connectToMQTT();
  
  // Initialize the BME280 sensor
  if (!bme.begin(0x76)) 
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
  // Initialize the temperature readings array
  for (int i = 0; i < NUM_READINGS; i++) 
  {
    temperatureReadings[i] = 0.0;
  }
}

void loop() 
{
  // Read temperature from the sensor
  float temperature = readTemperature();
  
  // Shift readings in the array
  for (int i = NUM_READINGS - 1; i > 0; i--) 
  {
    temperatureReadings[i] = temperatureReadings[i - 1];
  }
  
  temperatureReadings[0] = temperature;   // Store the latest temperature reading
  
  // Calculate statistics
  float averageTemperature = calculateAverage();
  float minimumTemperature = calculateMinimum();
  float maximumTemperature = calculateMaximum();
  
  publishStatistics(averageTemperature, minimumTemperature, maximumTemperature);    // Publish statistics to MQTT topic
  
  delay(5000);      // Delay before taking the next reading
}
