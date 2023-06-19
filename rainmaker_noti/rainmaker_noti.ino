#include <WiFi.h>   // Include the WiFi library
#include <EspRainmaker.h>   // Include the ESP Rainmaker library

const char* ssid = "YOURSSID";   // Your WiFi network SSID
const char* password = "YOURPASSWORD";    // Your WiFi network password

const char* deviceName = "YourDevice";    // Your desired device name
const char* deviceType = "esp32";         // Your desired device type
const char* deviceSecret = "YourDeviceSecret";      // Your device secret
const char* rainmakerEmail = "YourRainmakerEmail";    // Your ESP Rainmaker account email
const char* rainmakerPassword = "YourRainmakerPassword";    // Your ESP Rainmaker account password


EspRainmaker rainmaker;   // Create an instance of the EspRainmaker class

void setup() 
{
  Serial.begin(115200);     // Initialize serial monitor
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
// Initialize the ESP Rainmaker
  rainmaker.begin(deviceName, deviceType, deviceSecret, rainmakerEmail, rainmakerPassword);
}

void loop() 
{
  rainmaker.handle();   // Handle ESP Rainmaker tasks
  delay(1000);
}
