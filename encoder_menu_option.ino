#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the I2C LCD (address, columns, rows)
LiquidCrystal_I2C lcd(0x3F, 16, 2); // Change 0x27 to your LCD's I2C address

// Rotary Encoder Pins
const int clkPin = 2;
const int dtPin = 3;
const int swPin = 4;

// Menu Variables
int menuLevel = 0;       // 0: Main, 1: Veg/Non-Veg, 2: Submenu
int mainMenuIndex = 0;   // Current main menu selection (Veg/Non-Veg)
int subMenuIndex = 0;    // Current submenu selection
unsigned long lastButtonPress = 0;

// Encoder Variables
int lastStateCLK = LOW;  // Declare lastStateCLK globally

// Menu Arrays
const char* mainMenu[2] = {"Veg", "Non-Veg"};
const char* vegMenu[5] = {"Dal Tadka", "Thali", "Biryani", "Pulav", "Matter Paneer"};
const char* nonVegMenu[5] = {"Surmai Thali", "Chicken Thali", "Biryani", "Prawns", "Mutton"};

void setup() {
  // Set encoder pins as inputs
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);

  // Initialize I2C LCD
  Wire.begin();
  lcd.begin(16,2);
  lcd.backlight();
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("Welcome to.....");
  lcd.setCursor(0, 1);
  lcd.print("Arduino Kitchen");
  delay(4000);
  lcd.clear();

  // Display the main menu
  displayMainMenu();
}

void loop() {
  // Handle rotary encoder rotation
  handleEncoder();

  // Handle button press
  handleButton();
}

void handleEncoder() {
  int currentStateCLK = digitalRead(clkPin);

  if (currentStateCLK != lastStateCLK) {
    if (digitalRead(dtPin) != currentStateCLK) {
      // Clockwise rotation
      if (menuLevel == 0) {
        mainMenuIndex = (mainMenuIndex + 1) % 2; // Toggle between Veg and Non-Veg
      } else if (menuLevel == 1) {
        subMenuIndex = (subMenuIndex + 1) % 5; // Scroll through submenu options
      }
    } else {
      // Counterclockwise rotation
      if (menuLevel == 0) {
        mainMenuIndex = (mainMenuIndex - 1 + 2) % 2; // Toggle between Veg and Non-Veg
      } else if (menuLevel == 1) {
        subMenuIndex = (subMenuIndex - 1 + 5) % 5; // Scroll through submenu options
      }
    }
    updateDisplay();
    lastStateCLK = currentStateCLK; // Update lastStateCLK
  }
}

void handleButton() {
  if (digitalRead(swPin) == LOW) {
    if (millis() - lastButtonPress > 400) { // Debounce delay
      lastButtonPress = millis();

      if (menuLevel == 0) {
        // Enter Veg or Non-Veg submenu
        menuLevel = 1;
        subMenuIndex = 0;
        displaySubMenu();
      } else if (menuLevel == 1) {
        // Double press to return to main menu
        if (millis() - lastButtonPress < 400) {
          menuLevel = 0;
          displayMainMenu();
        } else {
          // Single press (select option)
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Selected:");
          lcd.setCursor(0, 1);
          if (mainMenuIndex == 0) {
            lcd.print(vegMenu[subMenuIndex]);
          } else {
            lcd.print(nonVegMenu[subMenuIndex]);
          }
          delay(2000); // Display selection for 2 seconds
          displaySubMenu(); // Return to submenu
        }
      }
    }
  }
}

void updateDisplay() {
  if (menuLevel == 0) {
    displayMainMenu();
  } else if (menuLevel == 1) {
    displaySubMenu();
  }
}

void displayMainMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Menu:");
  lcd.setCursor(0, 1);
  lcd.print(mainMenu[mainMenuIndex]);
}

void displaySubMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mainMenu[mainMenuIndex]);
  lcd.setCursor(0, 1);
  if (mainMenuIndex == 0) {
    lcd.print(vegMenu[subMenuIndex]);
  } else {
    lcd.print(nonVegMenu[subMenuIndex]);
  }
}
