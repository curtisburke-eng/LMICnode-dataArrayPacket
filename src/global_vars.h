/*******************************************************************************
 *
 *  File:          global_vars.h
 * 
 *  Function:      global_vars header file.
 * 
 *  Author:        Curtis Burke
 * 
 *  Company:       IES Industries, LLC
 * 
 *  Description:   Allows for definition of global varibles for use thoughout the
 *                  full program. 
 *                 Any variables delcared here must be definied in the cpp file in which they 
 *                  are first used.
 *
 * Creation Date:   09-27-2021
 * Revision & Date: Rev 1 - Released (10-01-2021)
 * 
 * 
 ******************************************************************************/

#pragma once

// Include Libraries
#include "sensor.h"                                                                                                  // Sensor file

#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

// ---- GLOBAL Varaiable Declarations & Definitions ---------------------------------------------------------------------------------------------------------------------------

extern uint8_t payloadBuffer[]; 

#endif
