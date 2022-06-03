
///////////////////////////////////////////// SENSOR TEMP

#include <OneWire.h>                 
#include <DallasTemperature.h>
#define Pin 2                        
OneWire ourWire(Pin);                
DallasTemperature sensors(&ourWire); 
float temp = 0; 

///////////////////////////////////////////// OLED

#include <Wire.h>      
#include <Adafruit_GFX.h>   
#include <Adafruit_SSD1306.h>   
 
#define ANCHO 128     
#define ALTO 64       

#define OLED_RESET 4      // necesario por la libreria 
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  

///////////////////////////////////////////// NEOPIXEL

#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

///////////////////////////////////////////// CICLO FOR

int pasoTemp2 = 0;
int frioMedio = 0;
int medioFrio = 0;
int medioCaliente = 0;
int calienteMedio = 0;


void setup() {  ///////////////////////////////////////////// VOID SETUP


pixels.begin();
pixels.show(); 
Serial.begin(9600);
sensors.begin();   
Wire.begin();        
oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
}

void loop() {  ///////////////////////////////////////////// VOID LOOP

sensors.requestTemperatures(); 

temp = sensors.getTempCByIndex(0);

//Serial.println(temp);

///////////////////////////////////////////// NEOPIXEL

///////////////////////////////////////////// FRIO

if ( temp < 15.0 ) 

{

Serial.println("FRIO");

pixels.setPixelColor(0,0,170,228);

pixels.show();

frioMedio = 0;

medioCaliente = 0;

}

///////////////////////////////////////////// MEDIO

if ( temp < 25.0 && frioMedio == 0) 

{

medioCaliente = 0;

for (int i = 0; i <= 255 ; i++){

delay(2);

pixels.setPixelColor(0,0,i,0);

pixels.show();

frioMedio = 1;

}

}

if ( temp < 25.0 && calienteMedio == 0) 

{

medioCaliente = 0;

for (int i = 255; i >= 0 ; i--){

delay(2);

pixels.setPixelColor(0,i,0,0);

pixels.show();

}

for (int i = 0; i <= 255 ; i++){

delay(2);

pixels.setPixelColor(0,0,i,0);

pixels.show();

calienteMedio = 1;

}

}


///////////////////////////////////////////// CALIENTE

if (temp > 25.0 && medioCaliente == 0) 

{
  

for (int i = 255; i >= 0 ; i--){

delay(2);

pixels.setPixelColor(0,0,i,0);

pixels.show();

}

{

for (int i = 0; i <= 255 ; i++){

delay(2);

pixels.setPixelColor(0,i,0,0);

pixels.show();

medioCaliente = 1;

calienteMedio = 0;
}

}

}

///////////////////////////////////////////// OLED
      
Serial.print(sensors.getTempCByIndex(0)); 
Serial.println(" Grados");

    oled.clearDisplay();
    oled.setTextSize(3);
    oled.setTextColor(WHITE);
    oled.setCursor(0,0);
    //oled.println("Temp: ");
    oled.println(" ");
    oled.print(sensors.getTempCByIndex(0),1);
    oled.println(" C");
    oled.display();
    delay(500);
  
}
