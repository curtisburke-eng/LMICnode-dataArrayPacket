/*******************************************************************************
 *
 *  File:          sensors.cpp
 * 
 *  Function:      sensors program file.
 * 
 *  Author:        Curtis Burke
 * 
 *  Company:       IES Industries, LLC
 * 
 *  Description:   Defines the Sensor class functions. 
 *                 The main function for gathering sensor data. 
 *
 * Creation Date:   09-27-2021
 * Revision & Date: Rev 1 - Released (10-01-2021)
 * 
 * 
 ******************************************************************************/

// -- DEFINITIONS ----------------------------------------------------------------------------------------------------------------------------------------------------------

// Include Libraries
#include <Arduino.h>                                                                                                        // For use with the arduino ___ chip

// Include Function Files
#include "global_vars.h"
#include "sensors.h"                                                                                                 // To gather data from sensors & package correctly for transmission

// Varaiable Declarations 



// -- FUNCTIONS ----------------------------------------------------------------------------------------------------------------------------------------------------------
void Sensor::SensorInit(uint8_t sensor_id, uint8_t sensor_type, uint8_t sensor_pinGPIO) {
    // Called by gatherData()
    //      Sensor declarations are local to the sensors.cpp file
    //      thus can be accesses by any function within sensors.cpp.
    //
    //      This function is called to ensure all sensor data is initialized before collectiion. 
    //      and because I was having issues defining values for elements within the struct
    //      in the variable declaration section (i.e. outside of a function).
    //

    pin = sensor_pinGPIO;
    pinMode(pin, INPUT);
    id = sensor_id;
    type = sensor_type;

}


float CovertRAWtoPSI(float rawValue)
{   
    //
    // As of Rev 1.0 this is unused
    //    Data is sent as an adc value to be converted on the frontend. 
    //

    float convertedData = rawValue;

    return convertedData;
}

uint16_t readADC_Avg(Sensor sensor, uint16_t collectionInterval)
{
  // This is called by the gatherData() function and loops for 
  //    the number of seconds equal to the colllectionInterval 
  //    The returned value is the average over that interval
  //        (moving average digital filter)
  //

  uint16_t sum = 0;

  for(int i=0; i < collectionInterval; i++)
  {

    sensor.RawValue = analogRead(sensor.pin);   // this is a widening cast and should happen automatically (uint32_t should not be needed)
    sensor.avgBuffer[i] = sensor.RawValue;

    sum += sensor.avgBuffer[i];

    delay(1000);
  }

  return (sum/collectionInterval);          // check int division

}

void addDatatoBuffer(Sensor sensor) {

  payloadBuffer[0] = sensor.id;                 // Sensor identifier
  payloadBuffer[1] = sensor.type;               // Int code correspnding to sensor type
  
  uint8_t msb = sensor.AvgValue >> 8;           // Save the leftmost 8 bits to msb
  uint8_t lsb = sensor.AvgValue;                // because lsb is declared as uint8_t only the rightmost 8 bits are saved 

  payloadBuffer[2] = msb;
  payloadBuffer[3] = lsb;

}


void gatherData(Sensor sensor) 
{
    // This function is called from the processWork() 
    // function when the doWork job is executed.
    //
    // This is where the main work is performed.
    //      Collect & Filter Raw Data, Convert Data, 
    //      Add the Data to the Buffer
    //
    //      Sensors are set up in the setup section of
    //       the LMIC-node.cpp (main) function.
    //
    //      Debugging lines were left in (commented) for furture refernce and 
    //        implimentation with other sensors.
    // 
    
    // Collect Raw Data
    //pressureSensor.RawValue = analogRead(pressureSensor.pin);           // Collect instantanious reading for comparison to average. 
    sensor.AvgValue = readADC_Avg(sensor, 30);                            // collects data and averages over the collection interval. For multiple sensors, call again but decrease the collection interval for each call. 
    
    // Print Data for Debug
    //Serial.print("Raw: ");
    //Serial.print(pressureSensor.RawValue);                              // Print Raw Reading
    Serial.print("Averaged: ");
    Serial.println(sensor.AvgValue);                                      // Print Filtered Output

    // Convert Data
    //pressureSensor.DataValue = CovertRAWtoPSI(pressureSensor.RawValue);

    // Add Sensor Data to Buffer
    addDatatoBuffer(sensor);


    
}   // End gatherData()

 
