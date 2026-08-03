/*
 * Arduino & ESP32 Medicine Intake Scheduler and Pill Bottle Dispenser
 *
 * Main firmware for the Arduino Uno R3.
 *
 * Originally developed as an undergraduate Embedded Systems course project.
 * Archived for reference and educational purposes.
 *
 * Copyright (c) 2026
 * Sean Patrick Razo
 * Thoinby Ace Tangan
 * Fiona Mae Brazal
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the repository root for details.
 */

// Include necessary component libraries
#include <Servo.h>
#include <NewPing.h>
#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD variables
LiquidCrystal_I2C lcd(0x27, 20, 4);

// RTC variables
char time[32];
char sched[32];
bool alarmActive = false;
bool isAlarmActive = false;
bool isAlarm1 = false;
bool isAlarm2 = false;
bool isAlarm3 = false;
RTC_DS3231 rtc;
byte Hour, Minute, Second;

// Schedule Arrays
byte alarm1[3] = {8, 0, 0};
byte alarm2[3] = {16, 0, 0};
byte alarm3[3] = {0, 0, 0};

// Ultrasonic variables
#define pin_Trigger 8
#define pin_Echo 7
#define maxDistance 400 //cm
NewPing sonar(pin_Trigger, pin_Echo, maxDistance);
int sonarDistance = 0;

// Alarm Control variables
#define pin_pot A0
int knobVal;
bool bool_selectAlarm = false;
bool bool_setHour = false;
bool bool_setMinute = false;
unsigned long previousTime, currentTime, intervalTime;
byte setCounter, hourCounter, minuteCounter, chosenAlarm, alarmType;

// LED, Buzzer, Buttons
#define pin_LED1 5
#define pin_LED2 6
#define pin_Buzz 9
#define pin_Override 13
#define pin_setAlarm A1
#define pin_reload A2
bool override = false;

// Servo variables
Servo servo1;
Servo servo2;
byte bottleCount = 6;
byte bottleCount_default = 6;

// Function Prototypes (for anti-error in compiling)
void printTime();
void dispenseBottle();
void showPage1();
void disableAlarms();
char* amPM(byte x);
byte twelveHour(byte x);
void selectAlarm();
void setHour();
void setMinute();
void checkTaken(bool w, byte x);



/////////////////////////////////////////////////////
//                  SETUP AND LOOP                 //
/////////////////////////////////////////////////////

void setup() {
  // Set necessary pinmodes
  pinMode(pin_LED1, OUTPUT);
  pinMode(pin_LED2, OUTPUT);
  pinMode(pin_Buzz, OUTPUT);
  pinMode(pin_Override, INPUT);
  pinMode(pin_setAlarm, INPUT);
  pinMode(pin_reload, INPUT);

  // Begin elements
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  
  // LCD initialization
  lcd.init();
  lcd.clear();         
  lcd.backlight();

  // Set default states
  previousTime = 0;
  intervalTime = 60000;
  
  //Servo Code
  servo1.attach(5);
  servo1.write(180);
  servo2.attach(6);
  servo2.write(0);

  // Uncomment for resetting time via PC
  // rtc.adjust(DateTime(__DATE__, __TIME__));
  // DateTime t = DateTime(rtc.now().unixtime()+8);
  // rtc.adjust(t);
}

void loop() {
  // Show Homescreen on idle
  pageSched();

  // measure the ping time in cm
  sonarDistance = sonar.ping_cm();
  
  // Override all controls (for Demonstration purposes)
  if (digitalRead(pin_Override) == HIGH) {
    override = true;
  }

  // Controls for setting alarm
  if (digitalRead(pin_setAlarm) == HIGH) {
    bool_selectAlarm = true;
    bool_setHour = true;
    bool_setMinute = true;

    // Initiate alarm selection
    delay(300);
    lcd.clear();
    while (bool_selectAlarm == true){
      selectAlarm();
    }

    // Initiate hour selection
    lcd.clear();
    while (bool_setHour == true) {
      setHour();
    }

    // Initiate minute selection
    lcd.clear();
    while (bool_setMinute == true) {
      setMinute();
    }
  }

  // Alarm Code — Sound buzzer and Display Reminder
  isAlarm1 = checkAlarm(alarm1[0], alarm1[1], alarm1[2]);
  isAlarm2 = checkAlarm(alarm2[0], alarm2[1], alarm2[2]);
  isAlarm3 = checkAlarm(alarm3[0], alarm3[1], alarm3[2]);
  if (isAlarm1 == true || isAlarm2 == true || isAlarm3 == true || override == true) {
    // Determine alarm type
    if (isAlarm1 == true) {
      alarmType = 1;
    }
    else if (isAlarm2 == true) {
      alarmType = 2;
    }
    else if (isAlarm3 == true) {
      alarmType = 3;
    }
    
    // Sound alarm & display reminder
    digitalWrite(pin_Buzz, HIGH);
    alarmActive = true;
  }

  // Check which alarm type is active
  checkTaken(alarmActive, alarmType);

  // Execute Bottle Dispensing
  if (alarmActive == true && sonarDistance <= 4) {
    // Disable Alarm
    digitalWrite(pin_Buzz, LOW);
    disableAlarms();
    
    // Execute actions; otherwise, notify of empty tray
    if (bottleCount > 0) {
      dispenseBottle();
    }
    else {
      // Send "Supply empty" notif to ESP-32 via UART
      Serial.println("3");
    }

    // Clear LCD for Homescreen
    lcd.clear();
  }

  // Refreshes bottle count when tray is reloaded
  if (digitalRead(pin_reload) == HIGH) {
    digitalWrite(pin_Buzz, HIGH);
    delay(200);
    digitalWrite(pin_Buzz, LOW);
    bottleCount = bottleCount_default;
    pageSched();
  }
}
