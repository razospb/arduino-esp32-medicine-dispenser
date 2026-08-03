void pageSched() {
  char* meridiem;
  byte displayHour;

  // Display Schedule 1
  meridiem = amPM(alarm1[0]);
  displayHour = twelveHour(alarm1[0]);
  sprintf(sched, "Sched 1: %02d:%02d %s", displayHour, alarm1[1], meridiem);
  lcd.setCursor(0,0);
  lcd.print(sched);

  // Display Schedule 2
  meridiem = amPM(alarm2[0]);
  displayHour = twelveHour(alarm2[0]);
  sprintf(sched, "Sched 2: %02d:%02d %s", displayHour, alarm2[1], meridiem);
  lcd.setCursor(0,1);
  lcd.print(sched);

  // Display Schedule 3
  meridiem = amPM(alarm3[0]);
  displayHour = twelveHour(alarm3[0]);
  sprintf(sched, "Sched 3: %02d:%02d %s", displayHour, alarm3[1], meridiem);
  lcd.setCursor(0,2);
  lcd.print(sched);

  // Display the current dispenser status.
  lcd.setCursor(0, 3);
  if (!alarmActive) {
    sprintf(sched, "Bottles Left: %02d", bottleCount);
    lcd.print(sched);
  } else {
    lcd.print("Take Medicine!!!");
  }
}

// Sets the value of meridiem depending on hour
char* amPM(byte hour) {
  char* period;
  if (hour < 12) {
    return "AM";
  }
  return "PM";
}

// Converts 24hr format to 12hr format
byte twelveHour(byte hour) {
  if (hour >= 13) {
    return hour - 12;
  }
  
  if (hour == 0) {
      return 12;
  }
  
  return hour;
}