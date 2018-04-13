/*
 *  kbd.h
 *
 *  The simple interrupt driven button driver
 *  Supports two events - keypressed & longkey
 *
 *  Created on: 5 Sep 2017
 *  Version 0.0
 *
 *  Created by Piotr Jankowski
 *  http://www.diymat.co.uk
 *
 */

#ifndef KBD_H_
#define KBD_H_

#include <stdint.h>

#define KBDCALLBACKENABLED 	1
#define KEYEVENTSCALLBACKS  1

typedef enum
{
	NOKEY, KEY, LONGKEY, DOUBLECLICK, KEYUP, KEYDOWN, KEYERROR,
} KEYSTROKES_T;

typedef enum
{
	HI = 0, LO = 1,
} KEYTYPE_T;

typedef struct
{
	GPIO_TypeDef *gpio;
	union
	{
		uint8_t status_data;
		struct
		{
			uint8_t type :1;
			uint8_t pressed :1;
			uint8_t wait_for_realease :1;
			uint8_t ignore_release :1;
			uint8_t wait_for_DC :1;
			uint8_t previous_key :1;
			uint8_t debouncing :1;
			uint8_t debounced :1;
		};
	};
	uint8_t pinmask;
	uint16_t counter;
	char status;
#if KBDCALLBACKENABLED == 1
	void (*callback)(int, int);
#endif
} BUTTON_Status_T;

#define __KBD_DIVIDER		8
#define NKEYS	  			5
#define DEBOUNCE			(50 / __KBD_DIVIDER)
#define LONGCLICK			(1500 / __KBD_DIVIDER)
#define DC_GAP				(300 / __KBD_DIVIDER)

#if KEYEVENTSCALLBACKS == 1

typedef void (*KBD_Callback_T)(int, int);
KBD_Callback_T KBD_SetCallbacks(int key, void (*kbdcallback)(int, int));

#endif

#if KBDCALLBACKENABLED == 0
int KBD_addKey(GPIO_TypeDef *gpio, int pin, int type);
#else
int KBD_addKey(GPIO_TypeDef *gpio, int pin, int type, void (*)(int, int));
#endif

int KBD_GetKey(int key);
void KBD_SetKey(int key, int st);
void KBD_ISR_Callback(void);

#endif /* KBD_H_ */
