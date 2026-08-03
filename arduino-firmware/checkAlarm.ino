bool checkAlarm(byte x, byte y, byte z) {
  // Retrieve current RTC time
  DateTime now = rtc.now();

  // Return true if the current time matches the scheduled alarm
  return (
    now.hour()   == hour &&
    now.minute() == minute &&
    now.second() == second
  );
}

// Reset all alarm states after an alarm has been handled.
void disableAlarms() {
  isAlarm1 = false;
  isAlarm2 = false;
  isAlarm3 = false;
  alarmActive = false;
  override = false;
  alarmType = 0;
}