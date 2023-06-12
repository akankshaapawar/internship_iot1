#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

RTC_DS1307 rtc;  // Create an instance of the RTC_DS1307 class

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  lcd.begin(16, 2);   // Initialize the LCD display with 16 columns and 2 rows
  lcd.backlight();    // Turn on the backlight

  Wire.begin();   // Initialize the I2C communication
  rtc.begin();    // Initialize the RTC module

  // to set the current date and time
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() 
{
  // Read temperature data, lux data and rtc data
  DateTime now = rtc.now();
  float temperature = readTemperature();
  int lux = readLux();

  lcd.clear();    // Clear the LCD display
  lcd.setCursor(0, 0);    // Set the cursor to the first column of the first row
  //Print temperature and lux data
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C   Lux: ");
  lcd.print(lux);
  
  lcd.setCursor(0, 1);    // Set the cursor to the first column of the second row
  lcd.print("Date: ");
  lcd.print(now.day());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.year());
  lcd.print("  Time: ");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());

  delay(1000);    //delay of 1 sec
}

float readTemperature() // read temperature from a sensor
{
  return 0;
}

int readLux() // read lux from a sensor
{
  return 0;
}
