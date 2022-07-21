#include <SPI.h>
#include <Wire.h>
//Nutné stáhnout tyto knihovny
#include <Adafruit_GFX.h> //- https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SH110X.h> // - https://github.com/adafruit/Adafruit_SH110X
#include <Adafruit_Sensor.h> // - https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_BME280.h> // - https://github.com/adafruit/Adafruit_BME280_Library

#define SEALEVELPRESSURE_HPA (1013.25) //nastavý tlak na úrovni moře
Adafruit_BME280 bme; //Nastaví čidlo 

#define i2c_Address 0x3c
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1); //Nastavý display


void setup() {
  bme.begin(); //Začne cidlo
  delay(250);
  display.begin(i2c_Address, true); //Začne OLED display 
  display.display();
  delay(2000);
  display.clearDisplay(); 
  display.setTextColor(SH110X_WHITE); //Nastavý barvu textu
  display.setTextSize(1); //Nastvý velikost textu
}

void loop() {
  // put your main code here, to run repeatedly:
   display.setCursor(0,0);
   display.println((String)"Teplota:"+bme.readTemperature()+"C"); //Zobrazí na displeji teplotu z čidla
   display.println((String)"Tlak:"+bme.readPressure() / 100.0F+"hPa"); //Zobrazí na displeji tlak z čidla
   display.println((String)"Vlhkost:"+bme.readHumidity()+"%"); //Zobrazí na displeji vlhkost z čidla
   display.println((String)"Nadmorská vyska:"+bme.readAltitude(SEALEVELPRESSURE_HPA)+"m"); ////Zobrazí na displeji nadmořskou výšku vypočtenou z údajů z čidla
   display.display(); 
   delay(500);
   display.clearDisplay();
}  
