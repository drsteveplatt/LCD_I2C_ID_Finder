// LCD ID checker
// Finds the ID of the attached LCD display
// Displays the ID on the LCD's screen
// Also prints messages to Serial

// This combines the ICD scanner with a simple display routine
// All of the work is done in setup();

// It assumes that the normal serial adapter is attached to the LCD

#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
// It assumes that the Wire normal connection is used
//          Uno/Nano    Mega
//  SDA ->    A4          20
//  SCL ->    A5          21

#include <Wire.h>
//#include <LCD.h>
#include <LiquidCrystal_I2C.h>

void setup() {

  Wire.begin();
  Serial.begin(115200);

}

void loop() {
  byte error, address;
  bool found;
  static int counter = 0;
  // find a device
  Serial.println("Scanning started...");
  for(address=0; address<127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if(error==0) {
      Serial.print("Device found at 0x");
      if(address<16) Serial.print("0");
      Serial.println(address, HEX);
      break;
    }
  }

  // display the results on the device
  {
    LiquidCrystal_I2C lcd(address,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
    lcd.begin(16,2);
    lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.home();
    lcd.print("Address: 0x");
    if(address<16) lcd.print("0");
    lcd.print(address, HEX);

    lcd.setCursor(0,1);
    lcd.print("Run "); lcd.print(counter++);
  }

  delay(5000);
}
