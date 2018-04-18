#include "eeprom/eeprom24xx.h"

extern I2C_HandleTypeDef hi2c2;

#define _EEPROM24XX_I2C hi2c2
#define _EEPROM_SIZE_KBIT 1
#define _TIMEOUT 10

//##########################################################################
bool EEPROM24XX_IsConnected(void)
{
	if (HAL_I2C_IsDeviceReady(&_EEPROM24XX_I2C, 0xa0, 10, _TIMEOUT) == HAL_OK)
		return true;
	else
		return false;
}
//##########################################################################
bool EEPROM24XX_Save(uint16_t Address, void *data, size_t size_of_data)
{
#if ((_EEPROM_SIZE_KBIT==1) || (_EEPROM_SIZE_KBIT==2))
	if (size_of_data > 8 * 1024)
		return false;
#endif
#if ((_EEPROM_SIZE_KBIT==4) || (_EEPROM_SIZE_KBIT==8) || (_EEPROM_SIZE_KBIT==16))
	if(size_of_data > 16 * 1024)
	return false;
#endif
#if ((_EEPROM_SIZE_KBIT==32) || (_EEPROM_SIZE_KBIT==64) || (_EEPROM_SIZE_KBIT==128))
	if (size_of_data > 32 * 1024)
	return false;
#endif

#if ((_EEPROM_SIZE_KBIT==1) || (_EEPROM_SIZE_KBIT==2))
	if (HAL_I2C_Mem_Write(&_EEPROM24XX_I2C, 0xa0, Address, I2C_MEMADD_SIZE_8BIT,
			(uint8_t*) data, size_of_data, _TIMEOUT) == HAL_OK)
#else
	if (HAL_I2C_Mem_Write(&_EEPROM24XX_I2C, 0xa0, Address,
					I2C_MEMADD_SIZE_16BIT, (uint8_t*) data, size_of_data, _TIMEOUT)
			== HAL_OK)
#endif
	{
		//HAL_Delay(2);
		return true;
	}
	else
		return false;
}
//##########################################################################
bool EEPROM24XX_Load(uint16_t Address, void *data, size_t size_of_data)
{
#if ((_EEPROM_SIZE_KBIT==1) || (_EEPROM_SIZE_KBIT==2))
	if (HAL_I2C_Mem_Read(&_EEPROM24XX_I2C, 0xa0, Address, I2C_MEMADD_SIZE_8BIT,
			(uint8_t*) data, size_of_data, _TIMEOUT) == HAL_OK)
#else
	if (HAL_I2C_Mem_Read(&_EEPROM24XX_I2C, 0xa0, Address, I2C_MEMADD_SIZE_16BIT,
					(uint8_t*) data, size_of_data, _TIMEOUT) == HAL_OK)
#endif
	{
		return true;
	}
	else
		return false;
}
