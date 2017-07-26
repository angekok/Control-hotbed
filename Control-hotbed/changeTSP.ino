int changeTSP(int oldTSP) {

  int  newTSP = oldTSP;
  menu = 10;
  lcd.setCursor(0, 0); lcd.print("                        ");
  lcd.setCursor(0, 1); lcd.print("                        ");

  while ( menu == 10)
  {
    lcd.setCursor(0, 0);
    lcd.print("T old:    ");
    lcd.setCursor(8, 0);
    lcd.print(oldTSP);
    lcd.setCursor(0, 1);
    lcd.print("T new:    ");
    lcd.setCursor(8, 1);
    lcd.print(newTSP);

    readbtn();
    if (btnUp) {
      newTSP++;
      lcd.setCursor(8, 1);
      lcd.print(newTSP);
    }
    if (btnDown) {
      newTSP--;
      lcd.setCursor(8, 1);
      lcd.print(newTSP);
    }
    if (btnSelect) {
      menu = 0;
      return newTSP;
      lcd.setCursor(0, 0); lcd.print("                        ");
      lcd.setCursor(0, 1); lcd.print("                        ");
    }
  }
}

