#include <PID_v1.h>
#include <stdio.h>
#include <math.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Temperature sensor parameter
const byte numbersensorT = 3;
const byte PINsensorT1 = 1;// Pin sensor temperature. Which pin will be the input of the Voltage-Divider
const byte PINsensorT2 = 2;
const byte PINsensorT3 = 3;


const byte fan1PWM = 3;
const byte fan2PWM = 5;
const byte fan3PWM = 6; 
const byte bedPWM = 9;     // 

const byte   Pin_de_medicion = 5; // Pin analogico 5

// PID parameter
double  OutFan; double OutBed;
double Setpoint = 22;
double TempC = 0.0; // [ºC]       Temperature output in Celsius
//PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, POn, Direction) 
PID fanPID(&TempC, &OutFan, &Setpoint, 1, 0.498, 0.077,P_ON_M, REVERSE);
PID bedPID(&TempC, &OutBed, &Setpoint, 1, 0.498, 0.077,P_ON_M, DIRECT);



// lcd parameter
int menu = 0;
boolean exitMenu        = false;
byte menuPosition       = 0;
bool btnLeft  = false;
bool btnRight = false;
bool btnUp    = false;
bool btnDown  = false;
bool btnSelect = false;
const byte iArrow[8]    = { B00000, B00100, B00110, B11111, B00110, B00100, B00000, B00000 };
const byte ARROW        = 0;
const byte rowsLCD      = 2;     // rows number LCD
const byte columnsLCD   = 16;    // Columns number del LCD

/*  MENU TEXT */
const byte iMENU = 4;
const char *txMENU[] = {
  "Cambio SP     ", // Max columnsLCD - 1 caracter
  "Opcion 1         ",
  "Opcion 2       ",
  "Salir          "
};

//funciones
void readbtn(); //read botones lcd
void openMenu(); //Menu usuario lcd
void hola();    //funcion en blanco, borrar despues
double sensorT(); //read temperature sensor
double sensorTmean();

void setup()
{

  Serial.begin(9600);

  pinMode(PINsensorT1, INPUT); //Pin sensor
  pinMode(PINsensorT2, INPUT); //Pin sensor
  pinMode(PINsensorT3, INPUT); //Pin sensor

  //test turn on LCD
  lcd.begin(columnsLCD, rowsLCD);              // start the library
  lcd.setCursor(0, 0); lcd.print("Menu Shield ");
  lcd.setCursor(0, 1); lcd.print("  D:  ");
  delay(1000);
  lcd.clear();


  //turn on PID
  fanPID.SetMode(AUTOMATIC);
bedPID.SetMode(AUTOMATIC);
  //test turn on fan, max power during 3 seg
  analogWrite(fan1PWM, 255);
  delay(3000);
  analogWrite(fan1PWM, 0);
  delay(1000);
  lcd.setCursor(0, 0); lcd.print("                        ");
  lcd.setCursor(0, 1); lcd.print("                        ");
}

void loop()
{
  /* mapea el valor de entrada a un valor entre 0 y 255. Esto no es necesario, borrar a menos que se ocupe en el calefactor
    if (Serial.available()) {
    Setpoint = Serial.parseInt();
    Setpoint = map(Setpoint, 0, 9, 0, 900);
    }
  */

  //TempC = sensorT(pin);
TempC=sensorTmean(numbersensorT, PINsensorT1, PINsensorT2, PINsensorT3);
  
  //computation PID and PWM output
  fanPID.Compute();
  bedPID.Compute();
  analogWrite(fan1PWM, OutFan);
  analogWrite(fan2PWM, OutFan);
  analogWrite(fan3PWM, OutFan);

  
  analogWrite(bedPWM, OutBed);
  //analogWrite(5, 255);

  // user PC
  Serial.print("SetPoint:");
  Serial.print(Setpoint);
  Serial.print("      Temperature: ");
  Serial.print(TempC, 2);
  Serial.print("      Error: ");
  Serial.print(Setpoint - TempC);
  Serial.print("      Output: ");
  Serial.println(fan1PWM, 2);
  
  
  // user LCD
  lcd.setCursor(0, 0); lcd.print("T=");
  lcd.setCursor(3, 0); lcd.print(int(TempC));
  lcd.setCursor(6, 0); lcd.print("PW=");
  lcd.setCursor(9, 0); lcd.print(int(fan1PWM));
  lcd.setCursor(13, 0); lcd.print(millis() / 1000);
  lcd.setCursor(0, 1); lcd.print("SP=");
  lcd.setCursor(3, 1); lcd.print(int(Setpoint));
  lcd.setCursor(10, 1); lcd.print("E=");
  lcd.setCursor(12, 1); lcd.print(int(Setpoint - TempC));


  readbtn();
  //if (btnSelect) Setpoint=changeTSP(Setpoint);  //  open new setpoint  T° menu
  if (btnSelect) openMenu();  //abre menu lcd

  Serial.println(menu);

}
