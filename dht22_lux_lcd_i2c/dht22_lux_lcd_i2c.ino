#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD object with the I2C address, number of columns, and number of rows

void setup() 
{
  lcd.begin(16, 2); // Initialize the LCD display with 16 columns and 2 rows
  lcd.backlight(); // Turn on the backlight

  Wire.begin(); // Initialize the I2C communication
}

void loop() 
{
  // Read temperature and humidity data and lux data
  float temperature = readTemperature();
  float humidity = readHumidity();
  int lux = readLux();

  lcd.clear();          // Clear the LCD display

  lcd.setCursor(0, 0);        // Set the cursor to the first column of the first row

  // Print the temperature data
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  delay(1000);
  
  // Print the Humidity data
  lcd.print("Hum : ");
  lcd.print(humidity);
  lcd.print(" %");
  delay(1000);
  
  lcd.setCursor(0, 1);    // Set the cursor to the first column of the second row

  // Print the lux data
  lcd.print("Lux: ");
  lcd.print(lux);
  delay(1000);
  
}

float readTemperature()   // read temperature from a sensor
{
  return 0; 
}

float readHumidity()   // read humidity from a sensor
{
  return 0; 
}

int readLux()     // read lux from a sensor
{
  return 0; // Dummy value for demonstration
}
