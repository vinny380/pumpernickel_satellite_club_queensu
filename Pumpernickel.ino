
// Title:         Temperature and Barometer ToastSat Program
// Last Updated:  September 29th, 2021
// Author:        < Tomas Harmer,  ,   >
// Breif:         Program gets Temperature and Pressure
// analog pin:    

//-------------------------------------------------------------------------------------
#include <SPI.h>
#include <SD.h>

File myFile;

//Temperature-------------------------------------------------

int sensor_pin = 0;
int analog_data;
float temperatureC; 

//Pressure----------------------------------------------------

#include <SFE_BMP180.h>
#include <Wire.h>
#define ALTITUDE 1655.0 
SFE_BMP180 pressure;


  //________________________________________________________________________________________________________________________________________________________________
void setup() {
  //________________________________________________________________________________________________________________________________________________________________
  
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
  
  
  
   //Temperature-----------------------------------------------
  // start up temperature sensor 
  Serial.begin(9600);

  //Pressure--------------------------------------------------
  // start up the pressure sensor 
   Serial.begin(9600);
  Serial.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
  
  
 
}

  //________________________________________________________________________________________________________________________________________________________________
void loop() {
  //________________________________________________________________________________________________________________________________________________________________
  
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
char status;
  double T,P,p0,a;

  // Loop here getting pressure readings every 10 seconds.

  // If you want sea-level-compensated pressure, as used in weather reports,
  // you will need to know the altitude at which your measurements are taken.
  // We're using a constant called ALTITUDE in this sketch:
  
  Serial.println();
  Serial.print("provided altitude: ");
  Serial.print(ALTITUDE,0);
  Serial.print(" meters, ");
  Serial.print(ALTITUDE*3.28084,0);
  Serial.println(" feet");
  
  // If you want to measure altitude, and not pressure, you will instead need
  // to provide a known baseline pressure. This is shown at the end of the sketch.

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Print out the measurement:
      Serial.print("temperature: ");
      Serial.print(T,2);
      Serial.print(" deg C, ");
      Serial.print((9.0/5.0)*T+32.0,2);
      Serial.println(" deg F");
      
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          // Print out the measurement:
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");

          // The pressure sensor returns abolute pressure, which varies with altitude.
          // To remove the effects of altitude, use the sealevel function and your current altitude.
          // This number is commonly used in weather reports.
          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
          // Result: p0 = sea-level compensated pressure in mb

          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
          Serial.println(" inHg");

          // On the other hand, if you want to determine your altitude from the pressure reading,
          // use the altitude function along with a baseline pressure (sea-level or other).
          // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
          // Result: a = altitude in m.

          a = pressure.altitude(P,p0);
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
          Serial.println(" feet");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  delay(5000);  // Pause for 5 seconds.
    
    // include a delay to not overwork the sensor 
    --------------------------------------
  
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
