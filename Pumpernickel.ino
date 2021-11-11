
// Title:         Temperature and Barometer ToastSat Program
// Last Updated:  September 29th, 2021
// Author:        < Tomas Harmer,  ,   >
// Breif:         Program gets Temperature and Pressure
// analog pin:    

//-------------------------------------------------------------------------------------
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened properly, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}
//-------------------------------------------------------------------------------------
/*
//Temperature-------------------------------------------------

int sensor_pin = 0;
int analog_data;
float temperatureC; 

//Pressure----------------------------------------------------

#include <SFE_BMP180.h>
#include <Wire.h>
#define ALTITUDE 1655.0 
SFE_BMP180 pressure_sensor;

  //////////////////////////////////////////////////////////////////////////
void setup()
{
  //Temperature-----------------------------------------------
  // start up temperature sensor 
  Serial.begin(9600);

  //Pressure--------------------------------------------------
  // start up the pressure sensor 
  pressure_sensor.begin(); 
}
//////////////////////////////////////////////////////////////////////////
void loop()
{
  // read the analog input
  analog_data = analogRead(sensor_pin);
  
  // convert analog input to a temperature value
  temperatureC = (analog_data - 0.5) * 100; 
  
  // print out our values 
  Serial.print("Analog Value: ");
  Serial.println(analog_data);
  
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");
  Serial.println("");

// pressure
  char status;
    double T,P,p0,a;
    
    //Temperature----------------------------
    
    // You must first get a temperature measurement to perform a pressure reading.
    status = pressure.startTemperature();
    delay(status);
    
    // Retrieve the completed temperature measurement, measurement is stored in the variable T.
    status = pressure.getTemperature(T);


    //Pressure----------------------------
    // Start a pressure measurement: the parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
    status = pressure.startPressure(3);
    delay(status);
    
    // Retrieve the completed pressure measurement, measurement is stored in the variable P.
    status = pressure.getPressure(P,T);
    
    // Retrieve the relative (sea-level) pressure, measurement is stored in the variable p0. 
    p0 = pressure.sealevel(P, ALTITUDE);
    
    // Retreive the current altitude from the pressure reading
    a = pressure.altitude(P,p0);
    
    // include a delay to not overwork the sensor 
    --------------------------------------
  delay(5000); 
  
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
