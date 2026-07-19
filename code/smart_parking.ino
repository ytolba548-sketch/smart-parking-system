#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int ENTRY_TRIG_PIN = 2;
const int ENTRY_ECHO_PIN = 3;
const int EXIT_TRIG_PIN = 4;
const int EXIT_ECHO_PIN = 5;
const int SERVO_PIN = 9;
const int GREEN_LED_PIN = 6;
const int RED_LED_PIN = 7;
const int BUZZER_PIN = 8;

const int MAX_SPACES = 5;
int currentSpaces = MAX_SPACES;
const int DETECTION_DISTANCE = 10; 

Servo gateServo;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

long readDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034 / 2;
    return distance;
}

void updateDisplay() {
    if(currentSpaces > 0) {
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);
        lcd.setCursor(0,0);
        lcd.print("Parking Ready   ");
        lcd.setCursor(0,1);
        lcd.print("Slots: ");
        lcd.print(currentSpaces);
        lcd.print("       "); 
    } else {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, HIGH);
        lcd.setCursor(0,0);
        lcd.print("Parking Full    ");
        lcd.setCursor(0,1);
        lcd.print("Slots: 0        ");
    }
}

void openGate() {
    gateServo.write(90);
    tone(BUZZER_PIN, 2000);
    delay(200);
    noTone(BUZZER_PIN);
    delay(3000);
    gateServo.write(0);
}

void triggerFullAlarm() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Lot Full!");
    lcd.setCursor(0,1);
    lcd.print("Wait");

    for(int i=0; i<3; i++) {
        digitalWrite(RED_LED_PIN, HIGH);
        tone(BUZZER_PIN, 500);
        delay(300);
        digitalWrite(RED_LED_PIN, LOW);
        noTone(BUZZER_PIN);
        delay(300);
    }
    updateDisplay(); 
}

void checkEntrySensor() {
    long distance = readDistance(ENTRY_TRIG_PIN, ENTRY_ECHO_PIN);
    if(distance < DETECTION_DISTANCE) {
        if(currentSpaces > 0) {
            currentSpaces--;
            updateDisplay();
            openGate();
        } else {
            triggerFullAlarm();
        }
        delay(1000);
    }
}

void checkExitSensor() {
    long distance = readDistance(EXIT_TRIG_PIN, EXIT_ECHO_PIN);
    if(distance < DETECTION_DISTANCE) {
        if(currentSpaces < MAX_SPACES) {
            currentSpaces++;
            updateDisplay();
        }
        openGate();
        delay(1000);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(ENTRY_TRIG_PIN, OUTPUT);
    pinMode(ENTRY_ECHO_PIN, INPUT);
    pinMode(EXIT_TRIG_PIN, OUTPUT);
    pinMode(EXIT_ECHO_PIN, INPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    lcd.begin(16, 2); 
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Smart Parking");
    lcd.setCursor(0, 1);
    lcd.print("System Booting..");
    delay(2000); 

    gateServo.attach(SERVO_PIN);
    gateServo.write(0); 

    updateDisplay();
}

void loop() {
    checkEntrySensor();
    checkExitSensor();
    delay(50);
}
