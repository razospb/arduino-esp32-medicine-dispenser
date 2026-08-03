void selectAlarm() {
  lcd.setCursor(0, 0);
  lcd.print("Edit Alarm #:");

  // Read the current state of potentiometer & map values
  knobVal = analogRead(pin_pot);
  setCounter = map(knobVal, 0, 1023, 1, 4);

  // Print current alarm# selection
  lcd.setCursor(14, 0);
  lcd.print(setCounter);

  // Confirms the alarm# selection
  if (digitalRead(pin_setAlarm) == HIGH) {
    delay(1000);
    chosenAlarm = setCounter;
    lcd.clear();
    bool_selectAlarm = false;
  }
}

void setHour() {
  lcd.setCursor(0, 0);
  lcd.print("Set Hour #:");

  // Read the current state of potentiometer
  knobVal = analogRead(pin_pot);
  hourCounter = map(knobVal, 0, 1023, 0, 24);
  
  // Print the current hour# selection
  // Formatting for 12 AM
  if (hourCounter == 0) {
    lcd.setCursor(12, 0);
    lcd.print(12);
    lcd.setCursor(15, 0);
    lcd.print("AM");
  }
  // Formatting for 1 AM - 9 AM
  if (hourCounter > 0 && hourCounter < 10) {
    lcd.setCursor(13, 0);
    lcd.print(hourCounter);
    lcd.setCursor(12, 0);
    lcd.print(" ");
    lcd.setCursor(15, 0);
    lcd.print("AM");
  }
  // Formatting for 10 AM - 11 AM
  else if (hourCounter >= 10 && hourCounter < 12) {
    lcd.setCursor(12, 0);
    lcd.print(hourCounter);
    lcd.setCursor(15, 0);
    lcd.print("AM");
  }
  // Formatting for 12 PM
  else if (hourCounter == 12) {
    lcd.setCursor(12, 0);
    lcd.print(hourCounter);
    lcd.setCursor(15, 0);
    lcd.print("PM");
  }
  // Formatting for 1 PM - 9 PM
  else if (hourCounter > 12 && hourCounter < 22) {
    lcd.setCursor(13, 0);
    lcd.print(hourCounter - 12);
    lcd.setCursor(12, 0);
    lcd.print(" ");
    lcd.setCursor(15, 0);
    lcd.print("PM");
  }
  // Formatting for 10 PM - 11 PM
  else if (hourCounter >= 22) {
    lcd.setCursor(12, 0);
    lcd.print(hourCounter - 12);
    lcd.setCursor(15, 0);
    lcd.print("PM");
  }

  // Confirms the hour# selection then overwrite sched
  if (digitalRead(pin_setAlarm) == HIGH) {
    delay(300);
    switch (chosenAlarm) {
      case 1:
        alarm1[0] = hourCounter;
        break;
      case 2:
        alarm2[0] = hourCounter;
        break;
      case 3:
        alarm3[0] = hourCounter;
        break;
    }
    lcd.clear();
    bool_setHour = false;
  }
}

void setMinute() {
  lcd.setCursor(0, 0);
  lcd.print("Set Minute #:");

  // Read the current state of potentiometer
  knobVal = analogRead(pin_pot);
  minuteCounter = map(knobVal, 0, 1023, 0, 60);

  // Print the current minute# selection
  if (minuteCounter < 10) {
    lcd.setCursor(14, 0);
    lcd.print(minuteCounter);
    lcd.setCursor(15, 0);
    lcd.print(" ");
  }
  else {
    lcd.setCursor(14, 0);
    lcd.print(minuteCounter);
  }

  // Confirms the minute# selection then overwrite sched
  if (digitalRead(pin_setAlarm) == HIGH) {
    delay(300);
    switch (chosenAlarm) {
      case 1:
        alarm1[1] = minuteCounter;
        break;
      case 2:
        alarm2[1] = minuteCounter;
        break;
      case 3:
        alarm3[1] = minuteCounter;
        break;
    }
    lcd.clear();
    bool_setMinute = false;
  }
}