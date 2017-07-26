void openMenu() {

  bool exitMenu = 0;
  while ( !exitMenu )
  {
    readbtn();

    if ( btnLeft )
    {
      exitMenu = true;
    }
    else if ( btnUp && menuPosition - 1 >= 0 )
    {
      menuPosition--;
    }
    else if ( btnDown && menuPosition + 1 < iMENU )
    {
      menuPosition++;
    }
    else if ( btnSelect )
    {
      switch ( menuPosition )
      {
        case 0: Setpoint = changeTSP(Setpoint); break;
        case 1: hola(  ); break;
        case 2: hola( ); break;
        case 3:   exitMenu = true;                     break; //Salir y cancelar cambios
      }
    }


    if ( !exitMenu && millis() % 500 == 0 )
    {
      if (  menuPosition % rowsLCD == 0 )
      {
        for ( int i = menuPosition ; i < (menuPosition + rowsLCD) ; i++ )
        {
          lcd.setCursor(1, i % rowsLCD);
          lcd.print( i < iMENU ? txMENU[i] : "                " );
        }
      }

      if ( (menuPosition - (rowsLCD - 1)) % rowsLCD == 0 )
      {
        for ( int i = (menuPosition - (rowsLCD - 1)) ; i < ((menuPosition - (rowsLCD - 1)) + rowsLCD) ; i++ )
        {
          lcd.setCursor(1, i % rowsLCD);
          lcd.print( i < iMENU ? txMENU[i] : "                " );
        }
      }


      for ( int i = 0 ; i < rowsLCD ; i++ )
      {
        lcd.setCursor(0, i);
        lcd.print(" ");
      }
      lcd.setCursor(0, menuPosition % rowsLCD );
      lcd.write(ARROW);
    }
  }

  exitMenu     = false;
  menuPosition = 0;
  menu = 0;
  lcd.setCursor(0, 0); lcd.print("                        ");
  lcd.setCursor(0, 1); lcd.print("                        ");
}
