#include <SPI.h>
#include <SD.h>

const int sensorPin = A0; // Pin connected to the temperature sensor

// Variables to store sensor data
float temperature;
File dataFile;

void setup() 
{
  Serial.begin(9600);

  // Initialize the SD Card
  if (!SD.begin(10)) 
  {
    Serial.println("SD Card initialization failed!");
    while (1); // Stop execution if SD Card initialization fails
  }

  // Create a new file for data storage
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) 
  {
    // Write column headers
    dataFile.println("Timestamp,Temperature");
    dataFile.close();
  }
}

void loop() 
{
  // Read temperature from the sensor
  int sensorValue = analogRead(sensorPin);
  temperature = map(sensorValue, 0, 1023, 0, 500) / 10.0; // Adjust mapping as per sensor specifications

  // Append data to the file
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) 
  {
    
    String timestamp = String(millis());   // Create a timestamp

    // Write data to the file
    dataFile.print(timestamp);
    dataFile.print(",");
    dataFile.println(temperature);
    dataFile.close();

    // Print data to the serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }

  delay(1000); // Delay between readings
}
