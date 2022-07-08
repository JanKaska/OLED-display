#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_SHT4x.h>

Adafruit_SHT4x sht4 = Adafruit_SHT4x(); //Přiřadí senzor
#define i2c_Address 0x3c //Na této adrese je displej, pokud nebude fungoval zkuste vyměnit za 0x3d
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1); //Přiřadí displej, tloušťku a výšku

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  delay(250); // počká než se OLED zapne
  display.begin(i2c_Address, true); //začne displej
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2); // Nastavte 1 pokud chcete mít celý text na jednom řádku
  display.setTextColor(SH110X_WHITE);
  sht4.begin())//Začne senzor 
  sht4.setPrecision(SHT4X_HIGH_PRECISION);sht4.setHeater(SHT4X_NO_HEATER); //Nastavení senzoru
}

void loop() {
  // put your main code here, to run repeatedly:
  
  sensors_event_t humidity, temp;
  sht4.getEvent(&humidity, &temp);
  Serial.println(temp.temperature); //Vypíše teplotu pro kontorolu do Seriálu
  Serial.println(humidity.relative_humidity); //Vypíše vlhkost pro kontorolu do Seriálu
  display.setCursor(0,0);
  display.println((String)"Teplota:"+temp.temperature+"C"); //Zobrazí teplotu na display
  display.println((String)"Vlhkost:"+humidity.relative_humidity+"%"); //Zobrazí vlhkost na display
  display.display(); 
  delay(1000);
  display.clearDisplay();
}
