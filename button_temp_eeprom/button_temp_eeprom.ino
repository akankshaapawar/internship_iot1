#include <EEPROM.h>

const int buttonPin = 2;    // Pin for the push button
const int ledPin = 13;      // Pin for the LED
const int eepromAddress = 0; // EEPROM memory address to store the temperature

int desiredTemperature = 25;  // Initial desired temperature
int buttonState = HIGH;       // Current state of the button
int lastButtonState = HIGH;   // Previous state of the button

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // Read the desired temperature from EEPROM
  desiredTemperature = EEPROM.read(eepromAddress);

  // Set the LED state based on the desired temperature
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
}

void loop() {
  
  buttonState = digitalRead(buttonPin);     // Read the state of the button

  
  if (buttonState == LOW && lastButtonState == HIGH) // Check if the button is pressed and released
  {
    
    desiredTemperature++;   // Increment the desired temperature by 1

    
    EEPROM.write(eepromAddress, desiredTemperature);    // Store the new desired temperature in EEPROM

    // Blink the LED to indicate the temperature change
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  }

  
  lastButtonState = buttonState;    // Update the button state
}
