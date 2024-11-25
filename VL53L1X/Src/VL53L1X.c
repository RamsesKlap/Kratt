#include "VL53L1X.h"
#include "VL53L1X_api.h"
#include 

VL53L1X* active_sensor;

void TOF_InitStruct(VL53L1X* const sensor, uint32_t* hi2c, uint8_t address, uint32_t* xshut_port, uint32_t xshut_pin) {
	sensor->baseI2C = hi2c;
	sensor->address = address;

	sensor->baseLPn = xshut_port;
	sensor->pin = xshut_pin;
}

void TOF_TurnOn(VL53L1X* const sensor) {
	active_sensor = sensor;
	// HAL_GPIO_WritePin(sensor->xshut_port, sensor->xshut_pin, 1);
}

void TOF_TurnOff(VL53L1X* const sensor) {
	active_sensor = sensor;
	// HAL_GPIO_WritePin(sensor->xshut_port, sensor->xshut_pin, 0);
}

void TOF_BootMultipleSensors(VL53L1X** const sensors, uint8_t count) {
	for (uint8_t n = 0; n < count; n++) {
		TOF_TurnOff(sensors[n]);
	}

	for (uint8_t n = 0; n < count; n++) {
		TOF_BootSensor(sensors[n]);
	}
}

void TOF_BootSensor(VL53L1X* const sensor) {
	active_sensor = sensor;
	TOF_TurnOn(sensor);
    HAL_Delay(2); // Sometimes this is too fast and line can't settle

	// Assume sensor wasn't initialised and is using default address
	uint8_t correct_address = sensor->address;
	sensor->address = 0x52 >> 1;

	// Set new address to sensor if necessary
	uint16_t id = 0;
	if (VL53L1X_GetSensorId(sensor->address, &id) == 0) {
		VL53L1X_SetI2CAddress(sensor->address, correct_address);
	}

	// Initialise sensor
	sensor->address = correct_address;
	if (VL53L1X_GetSensorId(sensor->address, &id) == 0) {
		VL53L1X_SensorInit(sensor->address);
		VL53L1X_StartRanging(sensor->address);
	} else {
	    // Initialization failed
	}
}

void TOF_StartRanging(VL53L1X* const sensor) {
	active_sensor = sensor;
	VL53L1X_StartRanging(sensor->address);
}

void TOF_StopRanging(VL53L1X* const sensor) {
	active_sensor = sensor;
	VL53L1X_StopRanging(sensor->address);
}

uint16_t TOF_GetDistance(VL53L1X* const sensor) {
	active_sensor = sensor;

	uint16_t reading = 0;
	VL53L1X_GetDistance(sensor->address, &reading);
	return reading;
}
