#ifndef PROJECT_H
#define PROJECT_H

// Standard libraries
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Libraries for pin addresses for different peripherals
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

// Libraries for UART peripherials for debugging with PuTTy
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

// Libraries for controlling and communicating with the VL53L7CX sensors
#include "driverlib/i2c.h"
#include "VL53L7CX/Platform/platform.h"
#include "VL53L7CX/VL53L7CX_ULD_API/inc/vl53l7cx_api.h"

// Library for debugging when compiling
#include "driverlib/debug.h"

// Defines

// Prototypes

/*Function to add a variable delay into the code (Assumes clock is 16MHz)*/
void Delay(uint32_t ms);

/*Initializes the required preipherals for the I2C protocol*/
void I2CInit(void);

/*Initializes the required peripherals for the UART protocol*/
void ConfigureUART(void);

#endif // PROJECT_H