void checkTaken(bool alarmEnabled, byte alarmNumber) {
  // Retrieve Time
  DateTime now = rtc.now();
  currentTime = millis();

  if (alarmEnabled) {
    // Determine which scheduled alarm is currently active
    if (alarmNumber == 1) {
      // Check whether the reminder window is active (1–60 minutes after the alarm)
      if ((now.minute() >= (alarm1[1] + 1)) && (now.minute() <= (alarm1[1] + 60))) {
        // Send a reminder notification once every minute
        if (currentTime - previousTime > intervalTime) {
          // Notify the ESP32 that the medicine has not yet been taken
          Serial.println(MSG_NO_RESPONSE);
          previousTime = currentTime;
        }
      }
    } else if (alarmNumber == 2) {
      // Check whether the reminder window is active (1–60 minutes after the alarm)
      if ((now.minute() >= (alarm2[1] + 1)) && (now.minute() <= (alarm2[1] + 60))) {
        // Send a reminder notification once every minute
        if (currentTime - previousTime > intervalTime) {
          // Notify the ESP32 that the medicine has not yet been taken
          Serial.println(MSG_NO_RESPONSE);
          previousTime = currentTime;
        }
      }
    } else if (alarmNumber == 3) {
      // Check whether the reminder window is active (1–60 minutes after the alarm)
      if ((now.minute() >= (alarm3[1] + 1)) && (now.minute() <= (alarm3[1] + 60))) {
        // Send a reminder notification once every minute
        if (currentTime - previousTime > intervalTime) {
          // Notify the ESP32 that the medicine has not yet been taken
          Serial.println(MSG_NO_RESPONSE);
          previousTime = currentTime;
        }
      }
    }
  }
}