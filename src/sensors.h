/*******************************************************************************
 *
 *  File:          sensors.h
 * 
 *  Function:      sensors header file.
 * 
 *  Author:        Curtis Burke
 * 
 *  Company:       IES Industries, LLC
 * 
 *  Description:   Declares the Sensor class and supporting functions. To be used with sensor.cpp.
 *
 * Creation Date:   09-27-2021
 * Revision & Date: Rev 1 - Released (10-01-2021)
 * 
 * 
 ******************************************************************************/

#pragma once

// Include Libraries
#include <Arduino.h>

#ifndef SENSORS_H                                                                                                           // Check for previous definition
#define SENSORS_H                                                                                                           // Define

// Class Definition
class Sensor
{
    public: 
        uint8_t pin;                        // GPIO where the sensor is connected
        uint8_t id;                         // Number to be used in the LPP buffer for identification
        /*  Type                Hex
        *  Digital Input       0       
        *  Digital Output      1       
        *  Analog Input        2
        *  Analog Output       3
        *  Illuminance Sensor  65
        *  Presence Sensor     66
        *  Temperature Sensor  67
        *  Humidity Sensor     68
        *  Accelerometer       71
        *  Barometer           73
        *  Gyrometer           86
        *  GPS Location        88
        *  Counter Input       4
        *  Battery Voltage     FF
        */
        uint8_t type;
        uint16_t RawValue;                     // Raw value read from the sensor
        uint16_t AvgValue;                     // Converted Value
        uint32_t avgBuffer[];
        uint32_t CalibrationFactor;            // 


        void SensorInit(uint8_t sensor_id, uint8_t sensor_type, uint8_t sensor_pinGPIO);

};


// Function Definition
uint16_t readADC_Avg(Sensor sensor, uint16_t collectionInterval);
void gatherData(Sensor sensor);
float CovertRAWtoPSI(float rawValue);

#endif

