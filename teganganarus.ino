// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

void setup()
{  
  Serial.begin(9600);
  
  emon1.voltage(2, 1023, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(1, 16);       // Current: input pin, calibration.

  lcd.begin();

  lcd.setCursor(0,0);
  lcd.print("V=");
  lcd.setCursor(5,0);
  lcd.print("V");
  
  lcd.setCursor(8,0);
  lcd.print("I=");  

  lcd.setCursor(0,1);
  lcd.print("P=");
}

void loop()
{
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable


  int daya=(int)apparentPower;
  int tegangan=(int)supplyVoltage;

  int KW=((daya*0.001)*1700);

  lcd.setCursor(2,0);
  lcd.print(tegangan);

  lcd.setCursor(10,0);
  lcd.print(Irms);
  lcd.print("A ");

  lcd.setCursor(2,1);
  lcd.print(daya);
  lcd.print("W  ");

  lcd.setCursor(6,1);
  lcd.print("Rp.");
  lcd.print(KW);
  lcd.print("/kWh  ");

  

  Serial.print(supplyVoltage);
  Serial.print(" ");
  Serial.println(Irms);  

  delay(500);
  
}
