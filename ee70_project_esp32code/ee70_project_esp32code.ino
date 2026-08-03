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

// UART pin assignments for communication with the Arduino Uno.
constexpr uint8_t RX_PIN = 16;
constexpr uint8_t TX_PIN = 17;

// UART communication state.
int messageCode;
bool hasNewData = false;

constexpr int MSG_MEDICINE_TAKEN = 1;
constexpr int MSG_NO_RESPONSE    = 2;
constexpr int MSG_SUPPLY_EMPTY   = 3;

// Wi-Fi reconnection timer.
unsigned long previousMillis = 0;
const unsigned long WIFI_RECONNECT_INTERVAL = 30000;

// Replace these placeholders with your own Wi-Fi credentials.
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Telegram Bot configuration.
#define BOTtoken "YOUR_TELEGRAM_BOT_TOKEN"  // your Bot Token (Get from Botfather)

// Use @myidbot to obtain your Telegram Chat ID.
#define CHAT_ID "YOUR_CHAT_ID"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  // Initialize serial communication.
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  // Set built-in LED to output as visual indicator
  pinMode(2, OUTPUT);

  // Connect to the configured Wi-Fi network.
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  // Configure the Wi-Fi interface.
  digitalWrite(2, HIGH);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Add root certificate for api.telegram.org
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  
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
  if (Serial2.available()) {
    messageCode = Serial2.parseInt();
    hasNewData = true;
  }

  if (hasNewData) {
    // Turn on LED during processing
    digitalWrite(2, HIGH);
    switch (messageCode) {
      case MSG_MEDICINE_TAKEN:
        Serial.println("Sending: Medicine Taken");
        bot.sendMessage(CHAT_ID, "💊 MEDICINE TAKEN 💊\n\nLola Flora has successfully taken her prescribed medicines at this hour!", "");
        break;
      case MSG_NO_RESPONSE:
        Serial.println("Sending: No Response");
        bot.sendMessage(CHAT_ID, "❗ NO RESPONSE ❗\n\nIt seems that Lola Flora is yet to take her medicines! Why don't you check on her to see if something is wrong?", "");
        break;
      case MSG_SUPPLY_EMPTY:
        Serial.println("Sending: Supply Empty");
        bot.sendMessage(CHAT_ID, "🫙 MEDICINE SUPPLY EMPTY 🫙\n\nNo medicines left! Refill the supply as soon as possible!", "");
        break;
    }
    hasNewData = false;
    delay(10);
    // Turn off LED during processing
    digitalWrite(2, LOW);

    // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
    unsigned long currentMillis = millis();
    if ((WiFi.status() != WL_CONNECTED) &&
        (currentMillis - previousMillis >= WIFI_RECONNECT_INTERVAL)) {
      Serial.print(millis());
      Serial.println("Reconnecting to WiFi...");
      WiFi.disconnect();
      WiFi.reconnect();
      previousMillis = currentMillis;
    }
  }
}