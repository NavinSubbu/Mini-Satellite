/*
Pin Connections for SD card Module
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10 
*/

#include <SPI.h>
#include <SD.h>

#define SensorPin  A0 //Sensor Pin
const int chipSelect = 10; //Chipselect of SD card Module

void setup() {
  
  Serial.begin(9600);
  pinMode(SensorPin,INPUT);
 /* while (!Serial) {
    ;
  }*/
  Serial.println("Initializing SD card...");


  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {

    String dataString = ""; //Creating an empty string
    int value = analogRead(SensorPin); //Reading the Sensor Value
    dataString += String(value); //Storing it in the string

  File dataFile = SD.open("Datalog.txt", FILE_WRITE); //Opening the Text file

 //If file found and available
  if (dataFile) {
    dataFile.println(dataString); //Storing in Text file
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString); //Display in Serial Monitor
  }
  
  // If file isn't Open, throw error
  else {
    Serial.println("error opening Datalog.txt");
  }
}
