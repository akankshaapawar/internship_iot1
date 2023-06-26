
#include <Arduino_MKRENV.h>
#include "thingProperties.h"

void setup() {
  // Initialize serial
  Serial.begin(9600);

  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  timer = millis(1000);
}

void loop() 
{
  ArduinoCloud.update();


    if (!ENV.begin()) 
    {
      Serial.println("Failed to initialize MKR ENV shield!");
      while (1);
    }

    temperature = ENV.readTemperature();
    humidity = ENV.readHumidity();

    // print each of the sensor values
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity    = ");
    Serial.print(humidity);
    Serial.println(" %");

}
