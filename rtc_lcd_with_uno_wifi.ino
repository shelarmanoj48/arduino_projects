#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD (I2C address, columns, rows)
LiquidCrystal_I2C lcd(0x3F, 16, 2); // Change 0x27 to your LCD's I2C address if needed
#define RTC_ADDRESS 0x68
// Initialize the RTC
RTC_DS1307 rtc;

void setup() {
  // Start serial communication
  Serial.begin(9600);
  Wire.begin();
  // Initialize the LCD
  lcd.begin(16,2);
  lcd.backlight();

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  //rtc.adjust(DateTime(2025, 2, 12, 11, 54, 20));
  
  // Set the time if the RTC is not running
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, setting the time!");
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2025, 2, 12, 11, 43, 20));
  }
}

void loop() {
  // Get the current date and time from the RTC
  DateTime now = rtc.now();

  // Display the time on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.hour());
  Serial.println(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  Serial.println(now.minute());
  lcd.print(':');
  lcd.print(now.second());
  Serial.println(now.second());

  // Display the date on the LCD
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(now.day());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.year());

  // Wait for a second before updating
  delay(1000);
}
