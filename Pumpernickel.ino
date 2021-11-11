
// Title:         Temperature and Barometer ToastSat Program
// Last Updated:  September 29th, 2021
// Author:        < Tomas Harmer,  ,   >
// Breif:         Program gets Temperature and Pressure
// analog pin:    



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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
