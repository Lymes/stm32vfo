#ifndef	_EEPROM_24XX_H
#define	_EEPROM_24XX_H

#include "stm32f1xx_hal.h"

// 	eeprom 24cxxx library				version 1V00
//	Writen by "Nima Askari"			www.github.com/NimaLTD

#include <stdbool.h>

#ifdef __cplusplus
 extern "C" {
#endif

bool EEPROM24XX_IsConnected(void);
bool EEPROM24XX_Save(uint16_t Address, void *data, size_t size_of_data);
bool EEPROM24XX_Load(uint16_t Address, void *data, size_t size_of_data);

#ifdef __cplusplus
 }

 namespace VFO
 {

 class Eeprom24
 {
 	uint16_t _addr;

 public:
 	Eeprom24() : Eeprom24( 0 ) {}
 	Eeprom24( uint16_t addr ) { _addr = addr; }
 	virtual ~Eeprom24() {}

 	bool isConnected(void) { return ::EEPROM24XX_IsConnected(); }
 	bool save(void *data, size_t size_of_data) { return ::EEPROM24XX_Save(_addr, data, size_of_data); }
 	bool load(void *data, size_t size_of_data) { return ::EEPROM24XX_Load(_addr, data, size_of_data); }

 };

 } /* namespace VFO */

#endif


#endif
