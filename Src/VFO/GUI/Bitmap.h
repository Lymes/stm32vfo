/*
 * Bitmap.h
 *
 *  Created on: Apr 11, 2018
 *      Author: lymes
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdint.h>


struct Bitmap {
	uint8_t height;
	uint8_t width;
	uint16_t data[];
};


#endif /* BITMAP_H_ */
