double sensorT(byte P1) {

  //parametros sensor T
  float Vin = 5.0;   // [V]        Supply voltage in the Voltage-Divider
  float Raux = 112310; // [ohm]      Secondary resistor in the Voltage-Divider
  float R0 = 10000;  // [ohm]      NTC nominal value at 25ºC
  float T0 = 293.15; // [K] (25ºC)
  float Vout = 0.0;  // [V]        Voltage given by the Voltage-Divider
  float Rout = 0.0;  // [ohm]      Current NTC resistance
  
  /* if you don't know beta, you must use this parameters
  float T1 = 273;    // [K]        Temperature at first testing point
  float T2 = 373;    // [K]        Temperature at second testing point
  float RT1 = 19750; // [ohms]     Resistance at 273K (0ºC)
  float RT2 = 2150;  // [ohms]     Resistance at 373K (100ºC)
  float beta = 0.0;  // [K]        Beta parameter
  double Rinf = 0.0;  // [ohm]      Rinf parameter
  */
  
  double TempKel = 0.0; // [K]        Temperature output in Kelvin
  double TempCel = 0.0; // [ºC]       Temperature output in Celsius


  //Global parameters calculation
  //beta=(log(RT1/RT2))/((1/T1)-(1/T2));
  float beta = 4036;
  double Rinf = R0 * exp(-beta / T0);


  //Current NTC resistance value calculation (through Vout)
  Vout = Vin * ((double)(analogRead(P1)) / 1024.0);
  Rout = (Raux * Vout / (Vin - Vout));

  //Temperature calculation
  TempKel = (beta / log(Rout / Rinf));
  TempCel = -1 * (TempKel - 273.15);

  return TempCel;
}
