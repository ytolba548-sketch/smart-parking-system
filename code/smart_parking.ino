/******************************************************************************
 * Project: Smart Parking System - Weekly Mini Hackathon
 * 
 * Team Members:
 * - Yahia Mahmoud (System Architecture & Integration - Leader)
 * - Omar (Embedded Software Engineer - Code logic)
 * - Raneem (Hardware Simulation Engineer - Tinkercad circuit)
 * 
 * Description: 
 * A fully automated, state-machine driven embedded solution designed to manage
 * vehicle entry, track available parking slots, and provide real-time user 
 * feedback using an Arduino Uno, ultrasonic sensors, a servo motor, and an LCD.
 ******************************************************************************/

// ==========================================
// 2. Library Inclusions
// ==========================================
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Using I2C LCD as specified in architecture

// ==========================================
// 3. Hardware Pin Definitions (Strictly per Master Pinout)
// ==========================================
// Entry Ultrasonic Sensor
const int ENTRY_TRIG_PIN = 2;
const int ENTRY_ECHO_PIN = 3;

// Exit Ultrasonic Sensor
const int EXIT_TRIG_PIN = 4;
const int EXIT_ECHO_PIN = 5;

// Barrier Gate (Servo)
const int SERVO_PIN = 9;

// Status Indicators
const int GREEN_LED_PIN = 6;
const int RED_LED_PIN = 7;
const int BUZZER_PIN = 8;

// ==========================================
// 4. Global Variables & State Management
// ==========================================
const int MAX_SPACES = 5;
int currentSpaces = MAX_SPACES;

// Threshold for ultrasonic sensor to detect a vehicle (in cm)
const int DETECTION_DISTANCE = 10; 

// ==========================================
// 5. Component Initialization
// ==========================================
// Initialize the servo object
Servo gateServo;

// Initialize the LCD display (Address 0x27 or 0x3F, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// ==========================================
// 6. Custom Helper Functions (Templates)
// ==========================================

/**
 * @brief Continuously pings the entry ultrasonic sensor.
 *        If a vehicle is detected within threshold and space is available,
 *        it initiates the entry sequence. If full, triggers alarm.
 */
void checkEntrySensor() {
  // TODO: Implement ultrasonic distance measurement for entry
  // TODO: Implement software debounce to prevent false positives
  // TODO: Call openGate() if space > 0, else call triggerFullAlarm()
}

/**
 * @brief Continuously pings the exit ultrasonic sensor.
 *        If a vehicle is detected leaving, it initiates the exit sequence
 *        and increments available slots.
 */
void checkExitSensor() {
  // TODO: Implement ultrasonic distance measurement for exit
  // TODO: Call openGate() to let vehicle out and increment currentSpaces
}

/**
 * @brief Refreshes the LCD display with the current available slots.
 *        Updates LED status based on capacity (Green=Available, Red=Full).
 */
void updateDisplay() {
  // TODO: Update LCD text with currentSpaces
  // TODO: Set GREEN_LED_PIN HIGH and RED_LED_PIN LOW if currentSpaces > 0
  // TODO: Set RED_LED_PIN HIGH and GREEN_LED_PIN LOW if currentSpaces == 0
}

/**
 * @brief Handles the barrier gate sequence.
 *        Rotates servo to 90 degrees, emits a short beep, waits for vehicle
 *        to pass, and closes the gate back to 0 degrees. Updates slots.
 */
void openGate() {
  // TODO: Implement servo movement to open
  // TODO: Implement short buzzer beep
  // TODO: Implement delay or wait logic for vehicle clearance
  // TODO: Implement servo movement to close
}

/**
 * @brief Handles the lot full error state.
 *        Flashes the red LED, displays "Lot Full! Wait" on LCD, 
 *        and emits a long warning beep.
 */
void triggerFullAlarm() {
  // TODO: Implement long buzzer tone
  // TODO: Implement Red LED flash logic
  // TODO: Update LCD warning message
}

// ==========================================
// 7. setup() Function
// ==========================================
void setup() {
  // Initialize Serial Communication for debugging
  Serial.begin(9600);
  Serial.println("Initializing Smart Parking System...");

  // Configure Pin Modes
  pinMode(ENTRY_TRIG_PIN, OUTPUT);
  pinMode(ENTRY_ECHO_PIN, INPUT);
  
  pinMode(EXIT_TRIG_PIN, OUTPUT);
  pinMode(EXIT_ECHO_PIN, INPUT);

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("System Booting..");
  delay(2000); // Short delay to show boot message

  // Attach and set initial Servo position (Closed = 0 degrees)
  gateServo.attach(SERVO_PIN);
  gateServo.write(0); 

  // Initial Display Update
  updateDisplay();
  
  Serial.println("System Ready.");
}

// ==========================================
// 8. loop() Function
// ==========================================
void loop() {
  // 1. Check if a vehicle wants to enter
  checkEntrySensor();
  
  // 2. Check if a vehicle wants to exit
  checkExitSensor();
  
  // 3. Keep display and status LEDs updated
  updateDisplay();
  
  // Note: Avoid long blocking delays in loop() to ensure responsive sensors
  delay(50); // Small loop delay for stability
}
