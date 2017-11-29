 
#include <Adafruit_NeoPixel.h>
 
#define PIN      6
#define N_LEDS   8
const int buttonPinTechno = 2;     // the number of the pushbutton pin
const int buttonPinTsyganskoye = 3;     // the number of the pushbutton pin
int sensorValue=0;
int incomingByte = 0;   // for incoming serial data

int light_power=0;
int tsyganState = 0; 
int technoState = 0;
String RGB = ""; //store RGB code from BT

boolean RGB_Completed = false;
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  pinMode(buttonPinTechno, INPUT);
  pinMode(buttonPinTsyganskoye, INPUT);
  Serial.begin(9600);
    

}
 
void loop() {

 
    //checking buttons
      technoState = digitalRead(buttonPinTechno);
      tsyganState = digitalRead(buttonPinTsyganskoye);

     if (technoState == HIGH) {
      Serial.println("on");
        if(tsyganState == HIGH)
          {
                techno_tsygan();
           }
        else
          {
                techno();
          }
     } else {
       sensorValue = analogRead(A0);  // получаем текущее значение
       light_power=sensorValue*0.24926686217; 
       light(light_power);
     }
     //Serial.println("bluetoth test");
}
 
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i , c); // Draw new pixel
      strip.setPixelColor(i-3, 0); // Erase pixel a few steps back
      strip.show();
      delay(250);
  }
}
static void light(int power)
{   uint32_t color=strip.Color(power, power, power);

    for(uint16_t i=0; i<strip.numPixels()+4; i++)
    { 
      strip.setPixelColor(i , color); // Draw new pixel
      strip.show();
    }

}

static void techno()
{   
uint32_t color=strip.Color(255, 255, 255);

  for(uint16_t i=0; i<strip.numPixels()+4; i++)
    { 
      strip.setPixelColor(i , color); // Draw new pixel
      strip.show();
    }
    delay(100);
    for(uint16_t i=0; i<strip.numPixels()+4; i++)
    { 
      strip.setPixelColor(i, 0); // Erase pixel a few steps back
      strip.show();

    }
        delay(100);
}
static void techno_tsygan()
{    
  uint32_t color=get_random_color();
  for(uint16_t i=0; i<strip.numPixels()+4; i++)
    { 
      strip.setPixelColor(i , color); // Draw new pixel
      strip.show();
    }
    delay(100);
    for(uint16_t i=0; i<strip.numPixels()+4; i++)
    { 
      strip.setPixelColor(i, 0); // Erase pixel a few steps back
      strip.show();

    }
        delay(100);
       
        
}
uint32_t get_random_color()
{
        int r= random(0, 255);
        int g= random(0, 255);
        int b= random(0, 255);
        return strip.Color(r, g, b);
}


