/**
 * This lab repo contains code to use a buzzer with a DHT11 sensor and LCD.
 * Kaplan Tonelli - November 2026
 */

#include <DHT.h>
#include <LiquidCrystal.h>

const int dhtPin = 2;
// define the buzzer pin
const int buzzerPin = 3;
const int rs = 7;
const int en = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

const int pause = 2500;

// set up objects
DHT dht(dhtPin, DHT11);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/**
 * @brief Converts a temperature from Celsius to Fahrenheit.
 *
 * @param tempC Temperature in Celsius
 * @return Temperature in Fahrenheit
 */
float celsiusToFahrenheit(float tempC) {
  return tempC * 1.8 + 32;
}

void setup() {
  dht.begin();

  // initialize the 16x2 LCD
  lcd.begin(16, 2);

  // set the buzzer pin as an ouput pin
  pinMode(buzzerPin, OUTPUT);

}

void loop() {
    float tempCelsius = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Convert the temperature to Fahrenheit
    float tempFahrenheit = celsiusToFahrenheit(tempCelsius);

    // position cursor at start of row 1
    lcd.setCursor(0, 0);

    // Display temp in Fahrenheit
    // format - Temp: xx.x F
    lcd.print("Temp: ");
    lcd.print(tempFahrenheit, 1);
    lcd.print("F");

    // position cursor at start of row 2
    lcd.setCursor(0,1);
    // format - Humidity: xx.x%
    lcd.print("humidity: ");
    lcd.print(humidity, 1);
    lcd.print("%");

    // Play if way too hot or way too dry
    if (tempFahrenheit >= 80) {
      tone(buzzerPin, 440);
      delay(500);
      noTone(buzzerPin);
      delay(1500);

    }
    else if (humidity <= 15) {
      tone(buzzerPin, 440);
      delay(500);
      noTone(buzzerPin);
      delay(1500);

    }  
    // Play if too hot or too dry
    else if (tempFahrenheit >= 75) {
      tone(buzzerPin, 440);
      delay(200);
      noTone(buzzerPin);
      delay(2500);

    }
    else if (humidity <= 20) {
      tone(buzzerPin, 440);
      delay(200);
      noTone(buzzerPin);
      delay(2500);
    }
}