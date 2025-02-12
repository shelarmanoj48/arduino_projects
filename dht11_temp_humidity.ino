#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2     // Pin where the DHT11 is connected
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Wire.begin();
  lcd.begin(16,2);  // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  dht.begin();  // Initialize the DHT sensor
}

void loop() {
  delay(1000);  // Wait a few seconds between measurements

  float h = dht.readHumidity();  // Read humidity
  float t = dht.readTemperature();  // Read temperature in Celsius

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed to read");
    lcd.setCursor(0, 1);
    lcd.print("from DHT sensor!");
    return;
  }

  // Display the temperature and humidity on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print(" %");
}
