/*
 * EXAMPLE CODE FOR OLED DISPLAY WITH SHT40 SENSOR
 * Reading data from SHT40 and displaying them on the OLED
 *
 * https://github.com/LasKKit/
 * laskarduino.cz
 * 2022
 *
 * Compile it as "ESP32-WROOM-DA"
 *
 *  https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_SHT4x.h>

Adafruit_SHT4x sht4 = Adafruit_SHT4x(); //Přiřadí senzor
#define i2c_Address 0x3c //Na této adrese je displej, pokud nebude fungoval zkuste vyměnit za 0x3d
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1); //Přiřadí displej, tloušťku a výšku

void setup() {
  Serial.begin(57600);
  delay(250); // počká než se OLED zapne
  display.begin(i2c_Address, true); //začne displej
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2); // Nastavte 1 pokud chcete mít celý text na jednom řádku
  display.setTextColor(SH110X_WHITE);
  sht4.begin();//Začne senzor 
  sht4.setPrecision(SHT4X_HIGH_PRECISION);sht4.setHeater(SHT4X_NO_HEATER); //Nastavení senzoru
}

void loop() {
  sensors_event_t humidity, temp;
  sht4.getEvent(&humidity, &temp);
  Serial.println(temp.temperature); //Vypíše teplotu pro kontorolu do Seriálu
  Serial.println(humidity.relative_humidity); //Vypíše vlhkost pro kontorolu do Seriálu
  display.setCursor(0,0);
  display.println((String)"Teplota:"+temp.temperature+"C"); //Zobrazí teplotu na display
  display.println((String)"Vlhkost:"+humidity.relative_humidity+"%"); //Zobrazí vlhkost na display
  display.display(); 
  delay(500);
  display.clearDisplay();
}
