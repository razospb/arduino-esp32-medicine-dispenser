byte checkAlarm(byte x, byte y, byte z) {
  // Retreive Time
  DateTime now = rtc.now();

  // Check if time matches selected alarm
  if (now.hour() == x && now.minute() == y && now.second() == z) {
    return true;
  }
  else  
    return false;
}

void disableAlarms() {
  isAlarm1 = false;
  isAlarm2 = false;
  isAlarm3 = false;
  alarmActive = false;
  override = false;
  alarmType = 0;
}