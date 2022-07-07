#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
//Nejprve je nutné stáhnout tyto tři knihovny
/*
 Adafruit_BusIO - https://github.com/adafruit/Adafruit_BusIO
 Adafruit_GFX - https://github.com/adafruit/Adafruit-GFX-Library
 Adafruit_SH110X - https://github.com/adafruit/Adafruit_SH110X
 */


#define i2c_Address 0x3c //Na této adrese je displej, pokud nebude fungovat zkuste vyměnit za 0x3d
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1); //Přiřadí displej, tloušťku a výšku

#define w 16
#define h 16
static const unsigned char PROGMEM bitmap[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};


void setup() {
  
  delay(250); // Počká než se OLED zapne
  display.begin(i2c_Address, true); //Začne displej 
  display.display();
  delay(2000);
  display.clearDisplay(); //Vyčistí displej, nutné zavolat display.display()
  //display.setContrast (100); //Nastavý světlost displeje pokud to umí

  //Zobrazí pixel drawPixel(x souřadnice, y souřadnice, barva pixelu (pro více barevné displeje.))
  display.drawPixel(10, 10, SH110X_WHITE); 
  display.display(); //Po každém malovacím povelu, povel .display() vykreslí zedané obrazce
  delay(2000); 
  display.clearDisplay();

  //Lze tak vykreslit i více pixelů nebo obrazců najednou
  int x=10;
  int y=10;
  display.drawPixel(x-1, y, SH110X_WHITE);
  display.drawPixel(x+1, y, SH110X_WHITE);
  display.drawPixel(x, y-1, SH110X_WHITE);
  display.drawPixel(x, y+1, SH110X_WHITE);
  display.display(); 
  delay(2000);
  display.clearDisplay();

  //Zobrazí linku drawLine(x začátečního bodu, y začátečního bodu, x koncového bodu, y koncového bodu, barva)
  display.drawLine(10,5,19,24,SH110X_WHITE); 
  display.display(); 
  delay(2000);
  

  //Zobrazí prázdný čtyřúhelník drawRect(x začátečního bodu,y začátečního bodu, délka na ose x, délka na ose y)
  display.drawRect(40,5,10,20,SH110X_WHITE); 
  refresh();

  //Zobrazí prázdný čtyřúhelník se zaoblenými rohy drawRect(x začátečního bodu,y začátečního bodu, délka na ose x, délka na ose y, poloměr rohů)
  display.drawRoundRect(70,5,10,20,3,SH110X_WHITE); 
  refresh();

  //Zobrazí prázdný čtyřúhelník drawRect(x začátečního bodu,y začátečního bodu, délka na ose x, délka na ose y)
  display.fillRect(100,5,10,20,SH110X_WHITE); 
  refresh();

  //Zobrazí prázdný čtyřúhelník drawRect(x začátečního bodu,y začátečního bodu, délka na ose x, délka na ose y, poloměr rohů)
  display.fillRoundRect(10,30,10,20,3,SH110X_WHITE); 
  refresh();

  //Zobrazí prázdný trojúhelník drawTriangle(x bodu A, y bodu A, x bodu B, y bodu B, x bodu C, y bodu C)
  display.drawTriangle(40,30,50,50,40,50,SH110X_WHITE);  
  refresh();

  //Zobrazí plný trojúhelník drawTriangle(x bodu A, y bodu A, x bodu B, y bodu B, x bodu C, y bodu C)
  display.fillTriangle(70,30,80,50,70,50,SH110X_WHITE);  
  refresh();
  
  display.clearDisplay();
  
  //Zobrazí bitmapu drawBitmap(x začátečního bodu, y začátečního bodu,bitmapa,tloušťka bitmapy v pixelech,výška bitmapy)
  display.drawBitmap(10,10,bitmap,w,h,SH110X_WHITE); 
  refresh();

   //Zobrazí prázdný kruh drawRect(x středu,y středu, poloměr)
  display.drawCircle(50,17,8,SH110X_WHITE); 
  refresh();

  //Zobrazí plný kruh drawRect(x středu,y středu, poloměr)
  display.fillCircle(80,17,8,SH110X_WHITE);
  refresh();

  display.clearDisplay();
  
  display.setTextSize(3); //Nastaví velikost textu (označuje tloušťku linek doporučuji mezi 1-9)
  display.setTextColor(SH110X_WHITE); //Nastavý barvu textu
  display.setCursor(0,0); //Nastavý kurzor na zadanou pozici 
  display.print("Hello."); //Napíše zadaný text
  display.setCursor(0,32);
  display.setTextSize(1);
  display.println("How are you?"); //Napíše zadaný text a přeskočí na další řádek
  display.println("qwertzuiopasdfgh");
  refresh();

  display.clearDisplay();
  display.fillRect(0,0,128,64,SH110X_WHITE); 
  refresh();
  
}

void loop() {
}
void refresh(){
  display.display(); 
  delay(2000);
  }
