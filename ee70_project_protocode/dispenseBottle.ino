// Function for dispensing bottle
void dispenseBottle() {
  // Initiate servo movements
  if (bottleCount == 1) {
    servo1.write(100);
    delay(500);
    servo1.write(180);
  }
  else {
    servo1.write(100);
    delay(500);
    servo1.write(180);
    delay(1100);
    servo2.write(80);
    delay(500);
    servo2.write(0);
    delay(1000);
  }

  // decrement or set bottleCount to 0
  if (bottleCount > 0) {
    bottleCount--;

    if (bottleCount == 0) {
      // Send "Medicine Taken" notif to ESP-32 via UART
      Serial.println("1");

      // Wait for 5 seconds to process UART
      delay(5000);

      // Send "Supply Empty" notif to ESP-32 via UART
      Serial.println("3");
    }
    else {
      // Send "Medicine Taken" notif to ESP-32 via UART
      Serial.println("1");      
    }
  }
  else {
    bottleCount = 0;

    // Send "Supply empty" notif to ESP-32 via UART
    Serial.println("3");
  }
}