// Libraries

// Display 
#include <TFT_eSPI.h>
#include "bmp.h"
#include <FS.h>
#include <SPI.h>

// DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

//---------------------------------------------------------

// Constants & Variables

#define AA_FONT_SMALL "NotoSansBold15"
#define AA_FONT_LARGE "NotoSansBold36"

#define ONE_WIRE_PIN 27  // DS18B20 D+ PIN

// Theese values are assigned for first run
float maxtemp = -200.0;
float mintemp = 100.0;
float t = 0.0;
float oldtemp = -100.0;
bool tick = false;

//---------------------------------------------------------

// Initialisation

// Display
TFT_eSPI tft = TFT_eSPI();

// 1-Wire
OneWire oneWire(ONE_WIRE_PIN);

// Probe driver
DallasTemperature sensors(&oneWire);


//---------------------------------------------------------

// Functions

// Boot check
void fsCheck() {
  // FS
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield();
  }
  Serial.println("\r\nSPIFFS available!");

  // Fonts
  if (not(SPIFFS.exists("/NotoSansBold15.vlw")) || not(SPIFFS.exists("/NotoSansBold36.vlw"))) {
    Serial.println("\r\nFont missing in SPIFFS, did you upload it?");
    while(1) yield();
  }
  else Serial.println("\r\nFonts found OK.");
}

//---------------------------------------------------------

// Boot image 
void bootSplash() {

  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0,0,240,135,splash);
}

//---------------------------------------------------------

// Loads temperature description
void loadScreen() {
  
  tft.setRotation(1);
  
  tft.loadFont(AA_FONT_SMALL);
  tft.fillScreen(TFT_BLACK);
  
  tft.setCursor(40, 10);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("NOW:");
  
  tft.setCursor(40, 60);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.println("MIN:");
  
  tft.setCursor(40, 110);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.println("MAX:");
  
  tft.unloadFont();
   
  tft.pushImage(0,52,30,30,ice);  // Print ICE icon
  tft.pushImage(0,105,30,30,fire);// Print FIRE icon

}

//---------------------------------------------------------

// Creates a REC symbol on display
void running_rec() {
  
  if (tick) {
    tft.fillRect(0,0,30,30,TFT_BLACK);
  }
  else {
    tft.pushImage(0,0,30,30,rec);
  }
  tick = not tick;
}

//---------------------------------------------------------

// Update Display

void updateDisplay(float t) {

  running_rec(); 

  tft.loadFont(AA_FONT_LARGE);
  
  if (t != oldtemp) {
  tft.fillRect(100, 0, 120, 45, TFT_BLACK);
  tft.setCursor(100, 0);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println(t);
  
    // Check for new min record
    if (t < mintemp) {
      tft.fillRect (100, 45, 120, 45, TFT_BLACK);
      tft.setCursor(100, 50);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.println(t);
      mintemp = t;
    }

    // Check for new max record
    if (t > maxtemp) {
      tft.fillRect (100, 90, 120, 45, TFT_BLACK);
      tft.setCursor(100, 100);
      tft.setTextColor(TFT_ORANGE, TFT_BLACK);
      tft.println(t);
      maxtemp = t;

    }
  }
  oldtemp = t;
  tft.unloadFont();

}

//---------------------------------------------------------
//---------------------------------------------------------

// Setup

void setup() {
  Serial.begin(115200);
  tft.begin();
  sensors.begin();
  
  bootSplash();

  fsCheck();
  
  delay(2000);
  
  loadScreen();
}

//---------------------------------------------------------
//---------------------------------------------------------

// Loop

void loop() {
  // If you have another sensor you can substitute these two line
  // and use the same function (just note or change float type) 
  sensors.requestTemperatures();
  t = sensors.getTempCByIndex(0);
  
  updateDisplay(t);

  delay(500);
}
