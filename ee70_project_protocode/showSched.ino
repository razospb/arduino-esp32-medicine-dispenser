void pageSched() {
  char* dayNight;
  byte hourConv;

  // Print Schedule 1
  dayNight = amPM(alarm1[0]);
  hourConv = twelveHour(alarm1[0]);
  sprintf(sched, "Sched 1: %02d:%02d %s", hourConv, alarm1[1], dayNight);
  lcd.setCursor(0,0);
  lcd.print(sched);

  // Print Schedule 2
  dayNight = amPM(alarm2[0]);
  hourConv = twelveHour(alarm2[0]);
  sprintf(sched, "Sched 2: %02d:%02d %s", hourConv, alarm2[1], dayNight);
  lcd.setCursor(0,1);
  lcd.print(sched);

  // Print Schedule 3
  dayNight = amPM(alarm3[0]);
  hourConv = twelveHour(alarm3[0]);
  sprintf(sched, "Sched 3: %02d:%02d %s", hourConv, alarm3[1], dayNight);
  lcd.setCursor(0,2);
  lcd.print(sched);

  // Print 4th line information
  lcd.setCursor(0, 3);
  if (alarmActive == false) {
    sprintf(sched, "Bottles Left: %02d", bottleCount);
    lcd.print(sched);
  }
  else {
    lcd.print("Take Medicine!!!");
  }
}

// Sets the value of dayNight depending on hour
char* amPM(byte x) {
  char* time;
  if (x < 12) {
    time = "AM";
  }
  else if (x >= 12) {
    time = "PM";
  }
  return time;
}

// Converts 24hr format to 12hr format
byte twelveHour(byte x) {
  byte time;
  if (x >= 13) {
    time = x - 12;
  }
  else if (x == 0) {
    time = 12;
  }
  else {
    time = x;
  }
  return time;
}