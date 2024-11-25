#ifndef VL53L1X_H_
#define VL53L1X_H_

#include "i2c.h"
#include "gpio.h"

typedef struct vl53l1x {
	// I2C information
	uint32_t 			baseI2C;
	uint8_t  			address;

	// LPn
	uint32_t			baseLPn;
	uint32_t			pin;
} VL53L1X;

void TOF_BootMultipleSensors(VL53L1X** const sensors, uint8_t count);

void TOF_InitStruct(VL53L1X* const sensor, uint32_t* hi2c, uint8_t address, uint32_t* xshut_port, uint32_t xshut_pin);
void TOF_BootSensor(VL53L1X* const sensor);

void TOF_TurnOn(VL53L1X* const sensor);
void TOF_TurnOff(VL53L1X* const sensor);

void TOF_StartRanging(VL53L1X* const sensor);
void TOF_StopRanging(VL53L1X* const sensor);

uint16_t TOF_GetDistance(VL53L1X* const sensor);

#endif // VL53L1X_H_
