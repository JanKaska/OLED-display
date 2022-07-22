/*
 * EXAMPLE CODE FOR MAX17048 and OLED display with SH1106 driver IC 
 * REading data from MAX17048 and displaying them on the OLED.
 *
 * https://github.com/LasKKit/
 * laskarduino.cz
 * 2022
 *
 * Compile it as "ESP32-WROOM-DA"
 *
 *  Produkt jeste neni.
 *  Produkt jeste neni.
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h> //Nutné stáhnout knihovnu - https://github.com/adafruit/Adafruit_SH110X
#include "MAX17048.h" //Nutné stáhnout knihovnu MAX17048 - https://github.com/hideakitai/MAX17048

MAX17048 pwr_mgmt;

#define i2c_Address 0x3c //Na této adrese je displej, pokud nebude fungoval zkuste vyměnit za 0x3d
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1); //Přiřadí displej, tloušťku a výšku

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    pwr_mgmt.attatch(Wire); //připojí čip MAX17048 k desce
    delay(250);
    display.begin(i2c_Address, true); // Address 0x3C default
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setTextColor(SH110X_WHITE); //Nastaví barvu displeje
    display.setTextSize(1); //Nastaví velikost písma
    
}

void loop()
{
  
   display.setCursor(0,0); //Nastaví kurzor na základní pozici. 
   display.println((String)"Cteni z ADC pinu:"+pwr_mgmt.adc()); //Vypíše na display hodnotu naměřenou na ADC pinu
   display.println((String)"Napeti na beterii:"+pwr_mgmt.voltage()+"V"); //Vypíše na display napětí baterie
   display.println((String)"Nabiti baterie:"+pwr_mgmt.percent()+" \%"); //Vypíše na display příblyžné nabití baterie v procentech
   display.println((String)"Presne nabiti baterie:"+pwr_mgmt.accuratePercent()+" \%"); //Vypíše na display přesné nabití baterie v procentech
   display.display(); 
   Serial.println((String)"VCELL ADC : "+pwr_mgmt.adc());
   Serial.println((String)"VCELL V   : "+pwr_mgmt.voltage()+"V");
   Serial.println((String)"VCELL SOC : "+pwr_mgmt.percent()+" \%");
   Serial.println((String)"VCELL SOC : "+pwr_mgmt.accuratePercent()+" \%");
   Serial.println();
   delay(500);
   display.clearDisplay();
}
