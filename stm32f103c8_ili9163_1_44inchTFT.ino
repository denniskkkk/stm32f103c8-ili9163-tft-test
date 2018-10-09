#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#define __144_RED_PCB__//128x128
//#define __144_BLACK_PCB__//128x128
//#define __22_RED_PCB__//240x320
/*
#define _TFTWIDTH      128//the REAL W resolution of the TFT
#define _TFTHEIGHT    128//the REAL H resolution of the TFT
#define _GRAMWIDTH        128
#define _GRAMHEIGH        128//Heh? Yes! My display uses offset!
#define _GRAMSIZE   _GRAMWIDTH * _GRAMHEIGH //
#define __COLORSPC    1// 1:GBR - 0:RGB
#define __GAMMASET3   //uncomment for another gamma (1,2,3)
#define __OFFSET    //this is the offset of my display, 160 - 128 = 32
*/
// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

/*
Teensy3.x and Arduino's
You are using 4 wire SPI here, so:
 MOSI:  PA7 i2C 11//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 SCK    PA5 i2C
 MISO:  12//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 SCK:   13//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 LED = 3v3
 REDBOARD 1.44"
 
 the rest of pin below:
 */

#define __CS PA4
#define __DC PA3
#define __RST PB1
/*
Teensy 3.x can use: 2,6,9,10,15,20,21,22,23
Arduino's 8 bit: any
DUE: check arduino site
If you do not use reset, tie it to +3V3
*/


TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC, __RST);

void setup() {
 // pinMode (__RST , OUTPUT);
  //digitalWrite (__RST, LOW);
  Serial.begin(115200);
  Serial.println("ILI9341 Test!"); 
 // delay (200);
 // digitalWrite (__RST, HIGH);
  
  tft.begin();
  //tft.homeAddress ();
  tft.setBitrate(16000000);  
  tft.scroll(0);
  tft.clearScreen ();
  //tft.startPushData(0,0,0,0);
}

void loop(){
  //testLines(random(0x00ff,0xffff));
//  delay(100);
  tft.drawLine(2,0,127,0,RED); 
  tft.drawLine(127,0,127,127,RED); 
  tft.drawLine(127,127,0,127,RED); 
  tft.drawLine(2,127,2,0,RED); 
  
  delay (2000);
  testText();
  delay(1000);
  
}


unsigned long testText() {
  tft.fillScreen();
  unsigned long start = micros();
  tft.setCursor(0,0);
  tft.setTextColor(WHITE);  
  tft.setTextSize(1);

  tft.println("Hello World!");
  tft.setTextColor(YELLOW); 
  tft.setTextSize(2);

  tft.println(1234.56);
  tft.setTextColor(RED);    
  tft.setTextSize(3);

  tft.println(0xDEAD, HEX);
  tft.println();
 
  tft.setTextColor(GREEN);
  tft.setTextSize(4);
  tft.println("Hello");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  tft.fillScreen();
  unsigned long start, t;
  int           x1, y1, x2, y2,
  w = tft.width(),
  h = tft.height();
  tft.fillScreen();
  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing
  tft.fillScreen();
  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;
  tft.fillScreen();
  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;
  tft.fillScreen();
  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  return micros() - start;
}
