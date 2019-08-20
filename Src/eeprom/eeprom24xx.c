#include "eeprom/eeprom24xx.h"

extern I2C_HandleTypeDef hi2c2;

#define EEPROM_I2C 			hi2c2
#define EEPROM_ADDRESS      0xA0
#define EEPROM_PAGESIZE     16
#define EEPROM_TIMEOUT      100


bool EEPROM24XX_IsConnected(void)
{
	uint8_t numTrials = 0;
	while ( HAL_I2C_IsDeviceReady( &EEPROM_I2C, EEPROM_ADDRESS, 50, EEPROM_TIMEOUT ) != HAL_OK )
	{
		HAL_Delay( 2 );
		if ( numTrials++ > 5 )
		{
			return false;
		}
	}
	return true;
}


bool EEPROM24XX_Save(uint16_t Address, uint8_t *data, size_t size_of_data)
{
	uint8_t numTrials = 0;
	uint16_t counter = 0;
	while ( counter < size_of_data )
	{
		uint16_t diff = size_of_data - counter;
		if ( diff >= EEPROM_PAGESIZE )
		{
			if ( HAL_I2C_Mem_Write( &EEPROM_I2C, EEPROM_ADDRESS,
					Address + counter, I2C_MEMADD_SIZE_8BIT,
					&data[counter], EEPROM_PAGESIZE, EEPROM_TIMEOUT ) != HAL_OK )
			{
				if ( numTrials++ > 5 )
				{
					return false;
				}
				continue;
			}
			counter += EEPROM_PAGESIZE;
		}
		else
		{
			//and the remaining ones...low packet size
			if ( HAL_I2C_Mem_Write( &EEPROM_I2C, EEPROM_ADDRESS,
					Address + counter, I2C_MEMADD_SIZE_8BIT,
					&data[counter], diff, EEPROM_TIMEOUT ) != HAL_OK )
			{
				if ( numTrials++ > 5 )
				{
					return false;
				}
				continue;
			}
			counter += diff;
		}
		HAL_Delay( 2 );
	}

	return true;
}


bool EEPROM24XX_Load(uint16_t Address, uint8_t *data, size_t size_of_data)
{
	uint8_t numTrials = 0;
	uint16_t counter = 0;
	while ( counter < size_of_data )
	{
		uint16_t diff = size_of_data - counter;

		if (diff >= EEPROM_PAGESIZE)
		{
			if ( HAL_I2C_Mem_Read( &EEPROM_I2C, EEPROM_ADDRESS,
					Address + counter, I2C_MEMADD_SIZE_8BIT,
					&data[counter], EEPROM_PAGESIZE, EEPROM_TIMEOUT ) != HAL_OK )
			{
				if ( numTrials++ > 5 )
				{
					return false;
				}
				continue;
			}
			counter += EEPROM_PAGESIZE;
		}
		else
		{
			// and the remaining ones...low packet size
			if ( HAL_I2C_Mem_Read( &EEPROM_I2C, EEPROM_ADDRESS,
					Address + counter, I2C_MEMADD_SIZE_8BIT,
					&data[counter], diff, EEPROM_TIMEOUT ) != HAL_OK )
			{
				if ( numTrials++ > 5 )
				{
					return false;
				}
				continue;
			}
			counter += diff;
		}
		HAL_Delay( 2 );
	}

	return true;
}
