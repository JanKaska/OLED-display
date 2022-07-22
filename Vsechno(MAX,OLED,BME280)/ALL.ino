#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //Doplňující knihovna k SH110x, nutné stáhnout s ní
#include <Adafruit_SH110X.h> //Nutné stáhnout knihovnu - https://github.com/adafruit/Adafruit_SH110X
#include "MAX17048.h" //Nutné stáhnout knihovnu MAX17048 - https://github.com/hideakitai/MAX17048
#include <Adafruit_Sensor.h> // - https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_BME280.h> // - https://github.com/adafruit/Adafruit_BME280_Library

#define SEALEVELPRESSURE_HPA (1013.25) //nastavý tlak na úrovni moře (Není použito jestly nepotřebuješ můžeš smazat)
Adafruit_BME280 bme; //Nastaví čidlo 

MAX17048 pwr_mgmt; //Nastavý Pwr modul MAX17048 

#define i2c_Address 0x3c //Na této adrese je displej, pokud nebude fungoval zkuste vyměnit za 0x3d
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1); //Přiřadí displej, tloušťku a výšku

//Bitmapa WiFi symbolu
static const unsigned char PROGMEM bitmap[] = { 
B00011000,B01100110, B10000001,B00011000,B00100100,B00000000, B00011000
};

void setup() {
  Wire.begin();
  pwr_mgmt.attatch(Wire); //připojí čip MAX17048 k desce
  bme.begin(); //Začne cidlo
  delay(250);
  display.begin(i2c_Address, true); // Address 0x3C default
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE); //Nastaví barvu displeje
  display.setTextSize(1); //Nastaví velikost písma
}

void loop() {
BatteryStatus(pwr_mgmt.percent()); //Zobrazí momentální stav baterie v levém horním rohu
WiFiStatus(); //Zobrazí status wifi (bez úpravy nefunguje)
display.drawLine(0,15,128,15,SH110X_WHITE); //Oddělí statusy od zobrazovaného textu
display.setCursor(2,20); //První řádek textu
display.println((String)"Teplota:"+bme.readTemperature()+"C"); //Zobrazí na prvním řádku teplotu z čidla
display.setCursor(2,30); //Druhý řádek textu
display.println((String)"Tlak:"+bme.readPressure() / 100.0F+"hPa"); //Zobrazí na druhém řádku tlak z čidla
display.setCursor(2,40); //Třetí řádek textu
display.println((String)"Vlhkost:"+bme.readHumidity()+"%"); //Zobrazí třetím řádku vlhkost z čidla
//display.setCursor(2,50); //Čtvrtý řádek textu(momentál není potřeba)
//display.println(""); //Sem zadat text pro čtvrtý řádek
display.display();
delay(500);
display.clearDisplay();
}
void BatteryStatus(int procnt){ //Zobrazí status baterie podle dat z MAX17048
  display.drawRect(6,4,3,1,SH110X_WHITE);
  display.drawRect(5,5,5,7,SH110X_WHITE);
  int fullnes = procnt/100. * 5.; 
  display.fillRect(6,11,3,-fullnes,SH110X_WHITE);
  display.setCursor(12,5);
  display.println((String)procnt+"%");
  }
void WiFiStatus(){ //Prozatím nic nedělá, je nutné přidat wifi knihovnu a odkomentovat switch case
  display.setCursor(50,5);
  display.drawBitmap(40,2,bitmap,8,7,SH110X_WHITE);
  display.println((String)"Not connected.");
  //display.println((String));
  /*
   switch(WiFi.status()) {
      case WL_DISCONNECTED:
          display.println((String)"Not connected.");
        break;
      case WL_CONNECTED:
          display.println((String)"Connected. "+WiFi.RSSI());
        break;
      default: 
         display.println((String)"Not connected.");
        break;
      
    }
  */
}
