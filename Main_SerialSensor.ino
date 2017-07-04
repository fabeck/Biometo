#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <EEPROM.h>
#include <SD.h>
#include <MySignals.h>
#include "Wire.h"

// Display
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


//Variables
int Iteration = 0;
int check = 0;
int valuePulse;
int valueSPO2;
int pulsioximeter_state = 0;


//declares File
File myFile;



void setup() {

  // Reads Iteration and increases by 1
  Iteration = EEPROM.read(0);
  Iteration = Iteration + 1;
  EEPROM.write(0, Iteration);


  //Show Iteration on Display
  tft.begin();
  tft.setCursor(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print(String("Iteration = ") + String(Iteration));
  delay(50);

  //Print display
  tft.setCursor(0, 20);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("SD-Card");

  tft.setCursor(0, 40);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Sensor:");

  tft.setCursor(0, 60);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Data Saved:");


  //Checks File
  SD.begin(4);
  myFile = SD.open("meas.txt", FILE_WRITE);

  if (myFile) {
    myFile.println(String("Measurement Nr. ") + String(Iteration));
    myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    tft.setCursor(150, 20);
    tft.setTextColor(ILI9341_RED);
    tft.println("error");
  }

  //Initialize MySignals
  //Serial.begin(19200);

  MySignals.begin();
  MySignals.initSensorUART();
  MySignals.enableSensorUART(PULSIOXIMETER);

  Serial.begin(19200);
}


void loop() {
  // put your main code here, to run repeatedly:
  /*
  myFile = SD.open("meas.txt", FILE_WRITE);
  if (myFile) {
    myFile.println("loop saving");
  }
  else {
    tft.setCursor(150, 40);
    tft.setTextColor(ILI9341_RED);
    tft.println("error");
  }*/
  MySignals.enableSensorUART(PULSIOXIMETER);
  Serial.println();
  pulsioximeter_state = MySignals.getPulsioximeter();
  if (pulsioximeter_state == 1)
  {
    Serial.print(F("Pulse:"));
    Serial.print(MySignals.pulsioximeterData.BPM);
    Serial.print(F("bpm / SPO2:"));
    Serial.print(MySignals.pulsioximeterData.O2);
    Serial.println(F("%"));
  }
  else if (pulsioximeter_state == 2)
  {
    Serial.println(F("Not valid data"));
  }
  else
  {
    Serial.println(F("No available data"));
  }
  MySignals.disableSensorUART();
 // myFile.close();
delay(200);
}
