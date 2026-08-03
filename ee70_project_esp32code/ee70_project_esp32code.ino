/*
 * Arduino & ESP32 Medicine Intake Scheduler and Pill Bottle Dispenser
 *
 * ESP32 firmware responsible for Wi-Fi connectivity
 * and Telegram notifications.
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
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Define values for UART comms
#define RX 16
#define TX 17

// Serial variables
int data;
bool newData = false;

// Interval variables
unsigned long previousMillis = 0;
unsigned long interval = 30000;

// Replace with network credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Initialize Telegram BOT
#define BOTtoken "YOUR_TELEGRAM_BOT_TOKEN"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
#define CHAT_ID "YOUR_CHAT_ID"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  // Begin serial commminications
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX, TX);

  // Set built-in LED to output as visual indicator
  pinMode(2, OUTPUT);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  // Connect to WiFi codes
  digitalWrite(2, HIGH);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  digitalWrite(2, LOW);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(2, HIGH);
  bot.sendMessage(CHAT_ID, "Connected to Dispenser", "");
  digitalWrite(2, LOW);
}

void loop() {
  // If new data is received in Serial2, execute actions
  if (Serial2.available() > 0) {
    data = Serial2.parseInt();
    newData = true;
  }

  if (newData == true) {
    // Turn on LED during processing
    digitalWrite(2, HIGH);
    switch (data) {
      case 1:
        Serial.println("Sending notif 1...");
        bot.sendMessage(CHAT_ID, "💊 MEDICINE TAKEN 💊\n\nLola Flora has successfully taken her prescribed medicines at this hour!", "");
        break;
      case 2:
        Serial.println("Sending notif 2...");
        bot.sendMessage(CHAT_ID, "❗ NO RESPONSE ❗\n\nIt seems that Lola Flora is yet to take her medicines! Why don't you check on her to see if something is wrong?", "");
        break;
      case 3:
        Serial.println("Sending notif 3...");
        bot.sendMessage(CHAT_ID, "🫙 MEDICINE SUPPLY EMPTY 🫙\n\nNo medicines left! Refill the supply as soon as possible!", "");
        break;
    }
    newData = false;
    delay(10);
    // Turn ooff LED during processing
    digitalWrite(2, LOW);

    // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
    unsigned long currentMillis = millis();
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
      Serial.print(millis());
      Serial.println("Reconnecting to WiFi...");
      WiFi.disconnect();
      WiFi.reconnect();
      previousMillis = currentMillis;
    }
  }
}