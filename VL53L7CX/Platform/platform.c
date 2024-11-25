/**
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "platform.h"
#include <string.h>
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

uint8_t _I2CBuffer[256];

uint8_t _I2CWrite(VL53L7CX_Platform *p_platform, uint8_t *pData, uint32_t count) {
    uint8_t status = I2C_MASTER_ERR_NONE;

    I2CMasterSlaveAddrSet(p_platform->baseI2C, p_platform->address, false);
    I2CMasterDataPut(p_platform->baseI2C, pData[0]);
    I2CMasterControl(p_platform->baseI2C, I2C_MASTER_CMD_BURST_SEND_START);

    status += I2CMasterErr(p_platform->baseI2C);
    if (status) {
        return status;
    }

    while(I2CMasterBusy(p_platform->baseI2C)) {}

    for (uint32_t i = 1; i < count - 1; i++) {
        I2CMasterDataPut(p_platform->baseI2C, pData[i]);
        I2CMasterControl(p_platform->baseI2C, I2C_MASTER_CMD_BURST_SEND_CONT);

        status += I2CMasterErr(p_platform->baseI2C);
        if (status) {
            return status;
        }

        while(I2CMasterBusy(p_platform->baseI2C)) {}
    }
    I2CMasterDataPut(p_platform->baseI2C, pData[count - 1]);
    I2CMasterControl(p_platform->baseI2C, I2C_MASTER_CMD_BURST_SEND_FINISH);

    status += I2CMasterErr(p_platform->baseI2C);
    if (status) {
        return status;
    }
    
    while(I2CMasterBusy(p_platform->baseI2C)) {}
    return status;
}

uint8_t _I2CRead(VL53L7CX_Platform *p_platform, uint8_t *pData, uint32_t count) {
    uint8_t status = I2C_MASTER_ERR_NONE;

    I2CMasterSlaveAddrSet(p_platform->baseI2C, p_platform->address, true);
    I2CMasterControl(p_platform->baseI2C, I2C_MASTER_CMD_BURST_RECEIVE_START);

    status += I2CMasterErr(p_platform->baseI2C);
    if (status) {
        return status;
    }

    while (I2CMasterBusy(p_platform->baseI2C)) {}
    pData[0] = I2CMasterDataGet(p_platform->baseI2C);

    for (uint32_t i = 1; i < count - 1; i++) {
        I2CMasterControl(p_platform->baseI2C, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

        status += I2CMasterErr(p_platform->baseI2C);
        if (status) {
            return status;
        }

        while (I2CMasterBusy(p_platform->baseI2C)) {}
        pData[i] = I2CMasterDataGet(p_platform->baseI2C);
    }
    
    I2CMasterControl(p_platform->baseI2C, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

    status += I2CMasterErr(p_platform->baseI2C);
    if (status) {
        return status;
    }

    while (I2CMasterBusy(p_platform->baseI2C)) {}
    pData[count - 1] = I2CMasterDataGet(p_platform->baseI2C);
    return status;
}

uint8_t VL53L7CX_RdByte(
		VL53L7CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t *p_value)
{
	uint8_t status = I2C_MASTER_ERR_NONE;
	_I2CBuffer[0] = RegisterAdress>>8;
	_I2CBuffer[1] = RegisterAdress&0xFF;

	status += _I2CWrite(p_platform, _I2CBuffer, 2);
    if( status ){
        goto done;
    }
    status += _I2CRead(p_platform, p_value, 1);
    if (status != 0) {
        goto done;
    }
done:

	return status;
}

uint8_t VL53L7CX_WrByte(
		VL53L7CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t value)
{
	uint8_t status = I2C_MASTER_ERR_NONE;
	
    _I2CBuffer[0] = RegisterAdress>>8;
    _I2CBuffer[1] = RegisterAdress&0xFF;
    _I2CBuffer[2] = value;

    status += _I2CWrite(p_platform, _I2CBuffer, 3);

	return status;
}

uint8_t VL53L7CX_WrMulti(
		VL53L7CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t *p_values,
		uint32_t size)
{
	uint8_t status = I2C_MASTER_ERR_NONE;
	
	if (size > sizeof(_I2CBuffer) - 1) {
        return 16;
    }
    _I2CBuffer[0] = RegisterAdress>>8;
    _I2CBuffer[1] = RegisterAdress&0xFF;
    memcpy(&_I2CBuffer[2], p_values, size);
    status += _I2CWrite(p_platform, _I2CBuffer, size + 2);

	return status;
}

uint8_t VL53L7CX_RdMulti(
		VL53L7CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t *p_values,
		uint32_t size)
{
	uint8_t status = I2C_MASTER_ERR_NONE;
	
	_I2CBuffer[0] = RegisterAdress>>8;
    _I2CBuffer[1] = RegisterAdress&0xFF;
    status += _I2CWrite(p_platform, _I2CBuffer, 2);
    if (status != 0) {
        goto done;
    }
    status += _I2CRead(p_platform, p_values, size);
    if (status != 0) {
        goto done;
    }
done:
	
	return status;
}

uint8_t VL53L7CX_Reset_Sensor(
		VL53L7CX_Platform *p_platform)
{
	uint8_t status = 0;
	
	/* (Optional) Need to be implemented by customer. This function returns 0 if OK */
	
	/* Set pin LPN to LOW */
	/* Set pin AVDD to LOW */
	/* Set pin VDDIO  to LOW */
	VL53L7CX_WaitMs(p_platform, 100);

	/* Set pin LPN of to HIGH */
	/* Set pin AVDD of to HIGH */
	/* Set pin VDDIO of  to HIGH */
	VL53L7CX_WaitMs(p_platform, 100);

	return status;
}

void VL53L7CX_SwapBuffer(
		uint8_t 		*buffer,
		uint16_t 	 	 size)
{
	uint32_t i, tmp;
	
	/* Example of possible implementation using <string.h> */
	for(i = 0; i < size; i = i + 4) 
	{
		tmp = (
		  buffer[i]<<24)
		|(buffer[i+1]<<16)
		|(buffer[i+2]<<8)
		|(buffer[i+3]);
		
		memcpy(&(buffer[i]), &tmp, 4);
	}
}	

/*Assuming clock is 16MHz*/
uint8_t VL53L7CX_WaitMs(
		VL53L7CX_Platform *p_platform,
		uint32_t TimeMs)
{
	(void) (p_platform);
	for (volatile uint32_t i = DELAY_1MS * TimeMs; i > 0; i--) {}
	return I2C_MASTER_ERR_NONE; 
}
