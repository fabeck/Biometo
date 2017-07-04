#include <Wire.h>

#include <MySignals.h>
#include <sounddata.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <EEPROM.h>
#include <SD.h>


// Display
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


//Variables
int Iteration = 0;
int check = 0;

//Senor Variables

//SP02
int valuePulse
uint8_t pulsoximeter_state = 0
int valueSPO2


//declares File
File myFile;


void setup() {
  // put your setup code here, to run once:

  // Reads Iteration and increases by 1
/* Serial.begin(9600);

    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
*/
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

  tft.setCursor(150, 20);
  tft.setTextColor(ILI9341_GREEN);
  tft.print("ok");

  tft.setCursor(0, 40);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Data access:");

  tft.setCursor(150, 40);
  tft.setTextColor(ILI9341_GREEN);
  tft.print("OK");

//initialize Sensors

  MySignals.begin();
  MySignals.initSensorUART();
  MySignals.enableSensorUART(PULSIOXIMETER);



  

  //Checks SD-Card
  /*
    tft.setCursor(0,20);
    check = SD.begin(4);
    if (check == 1){
      tft.setTextColor(ILI9341_GREEN);
      tft.print("SD-Card ok");
    } else
    {
      tft.setTextColor(ILI9341_RED);
      tft.print("SD-Card not ok");
      return;
    }
    delay(50);
  */



  //Checks File
  SD.begin(4);
  myFile = SD.open("meas.txt", FILE_WRITE);

  if (myFile) {
    myFile.println(String("Measurement Nr. ") + String(Iteration));
    myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    tft.setCursor(150, 40);
    tft.setTextColor(ILI9341_RED);
    tft.println("failure");
  }

}



void loop() {
  // put your main code here, to run repeatedly:

  myFile = SD.open("meas.txt", FILE_WRITE);
  myFile.println("I am an arbitrary string written in the Loop");
  myFile.println("I hope i am in the second row");
  myFile.println("I hope i am in the third row");
  myFile.println("");
  myFile.println("I hope i am in the fifth row");
  myFile.println("");
  myFile.println("");
  myFile.close();

}
