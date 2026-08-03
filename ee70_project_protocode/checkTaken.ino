void checkTaken(bool w, byte x) {
  // Retreive Time
  DateTime now = rtc.now();
  currentTime = millis();

  if (w == true) {
    // Check for which alarm hour is active
    if (x == 1) {
      // Check if current time is 1 minute past alarm time
      if ((now.minute() >= (alarm1[1] + 1)) && (now.minute() <= (alarm1[1] + 60))) {
        // Send Notifications every 1 minute
        if (currentTime - previousTime > intervalTime) {
          // Send "Medicine NOT Taken" notif to ESP-32 via UART
          Serial.println("2");
          previousTime = currentTime;
        }
      }
    }
    else if (x == 2) {
      // Check if current time is 1 minute past alarm time
      if ((now.minute() >= (alarm2[1] + 1)) && (now.minute() <= (alarm2[1] + 60))) {
        // Send Notifications every 1 minute
        if (currentTime - previousTime > intervalTime) {
          // Send "Medicine NOT Taken" notif to ESP-32 via UART
          Serial.println("2");
          previousTime = currentTime;
        }
      }
    }
    else if (x == 3) {
      // Check if current time is 1 minute past alarm time
      if ((now.minute() >= (alarm3[1] + 1)) && (now.minute() <= (alarm3[1] + 60))) {
        // Send Notifications every 1 minute
        if (currentTime - previousTime > intervalTime) {
          // Send "Medicine NOT Taken" notif to ESP-32 via UART
          Serial.println("2");
          previousTime = currentTime;
        }
      }
    }
  }
}