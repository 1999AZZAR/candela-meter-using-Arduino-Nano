#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the I2C address and LCD dimensions
const int button1Pin = 2; // Digital pin for button 1
const int button2Pin = 3; // Digital pin for button 2

unsigned long previousMillis = 0;
const long interval = 500; // Interval for displaying readings
bool menu1Active = true; // Track which menu is active

const int ldrTopPin = A0;     // Analog pin for LDR positioned at the top
const int ldrRightPin = A1;   // Analog pin for LDR positioned on the right
const int ldrBottomPin = A2;  // Analog pin for LDR positioned at the bottom
const int ldrLeftPin = A3;    // Analog pin for LDR positioned on the left
const int voltagePin = A6;    // Analog pin for voltage measurement
const int distancePin = A7;   // Analog pin for distance measurement

float candelaTop, candelaRight, candelaBottom, candelaLeft; // Global variables
String dominantDirection;
float averagecandela;

// #define PI 3.14159265358979323846 // Define the value of PI

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();  // Get the current time

  // Check if it's time to perform the next reading
  if (currentMillis - previousMillis >= interval) {
    // Save the last time a reading was taken
    previousMillis = currentMillis;
    // Read values from the four LDRs, voltage, and distance pins
    int luxTop = analogRead(ldrTopPin);
    int luxRight = analogRead(ldrRightPin);
    int luxBottom = analogRead(ldrBottomPin);
    int luxLeft = analogRead(ldrLeftPin);
    int voltageValue = analogRead(voltagePin);
    int distanceValue = analogRead(distancePin);

    // Calculate lux, voltage, and distance based on the analogRead values
    float luxTopNormalized = map(luxTop, 8, 1023, 10000, 0); // Adjust the mapping based on LDR characteristics
    float luxRightNormalized = map(luxRight, 8, 1023, 10000, 0); // Adjust the mapping based on LDR characteristics
    float luxBottomNormalized = map(luxBottom, 8, 1023, 10000, 0); // Adjust the mapping based on LDR characteristics
    float luxLeftNormalized = map(luxLeft, 8, 1023, 10000, 0); // Adjust the mapping based on LDR characteristics
    float voltage = map(voltageValue, 0, 1023, 120, 37)/10.0; // Adjust the mapping based on voltage measurement
    float distance = map(distanceValue, 0, 1023, 1, 1000)/100.0; // Adjust the mapping based on distance measurement

    // Calculate the candela value using the formula for each direction
    // rumus 1
    // float area = (4 * PI) * (distance * distance); // Assuming a spherical area
    // candelaTop = area * (luxTopNormalized/voltage);
    // candelaRight = area * (luxRightNormalized/voltage);
    // candelaBottom = area * (luxBottomNormalized/voltage);
    // candelaLeft = area * (luxLeftNormalized/voltage);
    // rumus 2
    // float area = (4 * PI) * (distance * distance);
    // candelaTop = (luxTopNormalized * area) / (voltage * (distance * distance));
    // candelaRight = (luxRightNormalized * area) / (voltage * (distance * distance));
    // candelaBottom = (luxBottomNormalized * area) / (voltage * (distance * distance));
    // candelaLeft = (luxLeftNormalized * area) / (voltage * (distance * distance));
    // rumus 3
    float area = (4 * PI * (distance * distance)) * voltage;
    candelaTop = luxTopNormalized/area;
    candelaRight = luxRightNormalized/area;
    candelaBottom = luxBottomNormalized/area;
    candelaLeft = luxLeftNormalized/area;

    averagecandela = (candelaTop + candelaRight + candelaBottom + candelaLeft) / 4;

    // Determine the dominant direction
    if (candelaTop > candelaRight && candelaTop > candelaBottom && candelaTop > candelaLeft) {
    dominantDirection = "Top";
    } else if (candelaRight > candelaBottom && candelaRight > candelaLeft && candelaRight > candelaTop) {
    dominantDirection = "Right";
    } else if (candelaRight > candelaBottom && candelaRight > candelaLeft && candelaRight == candelaTop) {
    dominantDirection = "Top Right";
    } else if (candelaRight == candelaBottom && candelaRight > candelaLeft && candelaRight > candelaTop) {
    dominantDirection = "Bottom Right";
    } else if (candelaLeft > candelaTop && candelaLeft > candelaRight && candelaLeft > candelaBottom) {
    dominantDirection = "Left";
    } else if (candelaLeft == candelaTop && candelaLeft > candelaRight && candelaLeft > candelaBottom) {
    dominantDirection = "top left";
    } else if (candelaLeft > candelaTop && candelaLeft > candelaRight && candelaLeft == candelaBottom) {
    dominantDirection = "Bottom Left";
    } else if (candelaBottom > candelaLeft && candelaBottom > candelaRight && candelaBottom > candelaTop) {
    dominantDirection = "Bottom";
    } else {
    dominantDirection = "middle";
    }

    // Print the calculated candela values and dominant direction
    Serial.print("Candela (Top): ");
    Serial.println(candelaTop);
    Serial.print("Candela (Right): ");
    Serial.println(candelaRight);
    Serial.print("Candela (Bottom): ");
    Serial.println(candelaBottom);
    Serial.print("Candela (Left): ");
    Serial.println(candelaLeft);
    Serial.print("Dominant Direction: ");
    Serial.println(dominantDirection);
    Serial.print("average :");
    Serial.println(averagecandela);

    if (menu1Active) {
      displayHome();
    } else {
      displaysensorval();
    }
  }

  // Check if button 1 is pressed to switch menus
  if (digitalRead(button1Pin) == LOW) {
    menu1Active = !menu1Active;
    delay(200); // Debounce delay
  }

  // Check if button 2 is pressed to switch menus
  if (digitalRead(button2Pin) == LOW) {
    menu1Active = !menu1Active;
    delay(200); // Debounce delay
  }
}

void displayHome() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("--Home--");
  lcd.setCursor(0, 1);
  lcd.print("Average : ");
  lcd.print(averagecandela);
  lcd.setCursor(0, 2);
  lcd.print("Dominant: ");
  lcd.print(dominantDirection);
}

void displaysensorval() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Top   : ");
  lcd.print(candelaTop);
  lcd.setCursor(0, 1);
  lcd.print("Right : ");
  lcd.print(candelaRight);
  lcd.setCursor(0, 2);
  lcd.print("Bottom: ");
  lcd.print(candelaBottom);
  lcd.setCursor(0, 3);
  lcd.print("Left  : ");
  lcd.print(candelaLeft);
}
