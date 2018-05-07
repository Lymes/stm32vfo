/*
 * Utils.h
 *
 *  Created on: Apr 8, 2018
 *      Author: lymes
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>
#include <stddef.h>


namespace VFO
{

char *valToStr(int32_t val, char *buf, size_t bufSize, char sepChar);
char *voltageToStr(int32_t val, char *buf, size_t bufSize);

char* utf8to1251(char *utf8);
char* utf8to1251Dest(const char *utf8, char* dest, size_t len);


} /* namespace VFO */

#endif /* UTILS_H_ */
