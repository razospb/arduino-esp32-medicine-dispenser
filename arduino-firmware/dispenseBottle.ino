// Dispense a medicine bottle and update the remaining supply.
void dispenseBottle() {
  // Dispense one bottle using the servo mechanism.
  servo1.write(100);
  delay(500);
  servo1.write(180);
  
  if (bottleCount > 1) {
    delay(1100);
    servo2.write(80);
    delay(500);
    servo2.write(0);
    delay(1000);
  }

  // Update the remaining bottle count.
  if (bottleCount > 0) {
    bottleCount--;

    if (bottleCount == 0) {
      // Send "Medicine Taken" notif to ESP-32 via UART
      Serial.println(MSG_MEDICINE_TAKEN);

      // Allow the ESP32 time to process the first notification.
      delay(5000);

      // Send "Supply Empty" notif to ESP-32 via UART
      Serial.println(MSG_SUPPLY_EMPTY);
    } else {
      // Send "Medicine Taken" notif to ESP-32 via UART
      Serial.println(MSG_MEDICINE_TAKEN);
    }
  } else {
    bottleCount = 0;

    // Send "Supply empty" notif to ESP-32 via UART
    Serial.println(MSG_SUPPLY_EMPTY);
  }
}