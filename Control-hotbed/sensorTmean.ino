double sensorTmean(byte numberTs, byte PinT1, byte PinT2, byte PinT3) {

  int Threshold = 4; // Definimos el umbral
  //byte T[numberTs]={PinT1,PinT2,PinT3};


  const byte numReadings = 10;

  double readings[numReadings]; // Lecturas de la entrada analogica
  byte ii = 0; // El indice de la lectura actual

  double total = 0; // Total


  for (int jj = 0; jj <= numberTs - 1; jj++) {
    for (int i = 0; ii <= numReadings; ii++) {
      // Restamos la ultima lectura:
      total = total - readings[ii];
      // Leemos del sensor:
      readings[ii] = sensorT(jj);
      // Añadimos la lectura al total:
      total = total + readings[ii];
      // Avanzamos a la proxima posicion del array
    }
  }
  // Calculamos el promedio:
  double mean = total / numReadings;
  return mean;
}
