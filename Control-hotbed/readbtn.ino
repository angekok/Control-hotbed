void readbtn()  //read Buttons
{
  int val  = analogRead(A0);
  btnLeft  = false;
  btnRight = false;
  btnUp    = false;
  btnDown  = false;
  btnSelect = false;

  if ( val < 50 )
    btnRight = true;
  else if ( val < 250 )
    btnUp    = true;
  else if ( val < 450 )
    btnDown  = true;
  else if ( val < 650 )
    btnLeft  = true;
  else if ( val < 850 )
    btnSelect  = true;

  while ( (btnLeft || btnRight || btnDown || btnUp || btnSelect) && analogRead(A0) < 1000 );
}
