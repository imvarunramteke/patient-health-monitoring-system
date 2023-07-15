#include <LiquidCrystal.h>

const int lcdRs = 12, lcdEn = 11, lcdD4 = 5, lcdD5 = 4, lcdD6 = 3, lcdD7 = 2;
LiquidCrystal lcd(lcdRs, lcdEn, lcdD4, lcdD5, lcdD6, lcdD7);

int buzzerPin = 8; // Pin for the buzzer
int ledPin = 9; // Pin for the LED
const int airSensorPin = A0; // Pin for the air quality sensor (MQ135)
int threshold = 250; // Threshold level for air quality

void setup() {
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  pinMode(airSensorPin, INPUT); // Set air quality sensor pin as input
  
  Serial.begin(9600); // Initialize serial communication
  
  lcd.clear(); // Clear the LCD display
  lcd.begin(16, 2); // Set the LCD display size (columns, rows)
}

void loop() {
  int airQuality = analogRead(airSensorPin); // Read air quality sensor value
  
  Serial.print("Air Quality: "); // Print message in the serial monitor
  Serial.println(airQuality); // Print air quality value in the serial monitor
  
  lcd.setCursor(0, 0); // Set the cursor position on the LCD (column 0, row 0)
  lcd.print("Air Quality: "); // Print message on the LCD
  lcd.print(airQuality); // Print air quality value on the LCD
  
  if (airQuality > threshold) { // Check if air quality exceeds the threshold
    lcd.setCursor(1, 1); // Set the cursor position on the LCD (column 1, row 1)
    lcd.print("AQ Level HIGH"); // Print message on the LCD
    Serial.println("AQ Level HIGH"); // Print message in the serial monitor
    tone(ledPin, 1000, 200); // Generate tone on the LED pin
    digitalWrite(buzzerPin, HIGH); // Turn ON the buzzer
  }
  else {
    digitalWrite(ledPin, LOW); // Turn OFF the LED
    digitalWrite(buzzerPin, LOW); // Turn OFF the buzzer
    lcd.setCursor(1, 1); // Set the cursor position on the LCD (column 1, row 1)
    lcd.print("AQ Level Good"); // Print message on the LCD
    Serial.println("AQ Level Good"); // Print message in the serial monitor
  }
  
  delay(500); // Delay for stability
}
