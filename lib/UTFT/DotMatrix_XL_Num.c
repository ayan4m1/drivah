// DotMatrix_XL_Num.c
// Font type    : Numeric (10 characters)
// Font size    : 32x50 pixels
// Memory usage : 2004 bytes

#if defined(__AVR__)
	#include <avr/pgmspace.h>
	#define fontdatatype const uint8_t
#elif defined(__PIC32MX__)
	#define PROGMEM
	#define fontdatatype const unsigned char
#elif defined(__arm__)
	#define PROGMEM
	#define fontdatatype const unsigned char
#endif

fontdatatype DotMatrix_XL_Num[2004] PROGMEM={
0x20,0x32,0x30,0x0A,
0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 0
0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x80,0x00,0x01,0xF7,0xC0,0x00,0x01,0xF7,0xC0,0x00,0x01,0xF7,0xC0,0x00,0x00,0xE3,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 1
0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x38,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x38,0x7D,0xF7,0xDF,0x7C,0x7D,0xF7,0xDF,0x7C,0x7D,0xF7,0xDF,0x7C,0x38,0xE3,0x8E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 2
0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x38,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x38,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 3
0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x38,0x7D,0xF7,0xDF,0x7C,0x7D,0xF7,0xDF,0x7C,0x7D,0xF7,0xDF,0x7C,0x38,0xE3,0x8E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 4
0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x38,0x7D,0xF7,0xDF,0x7C,0x7D,0xF7,0xDF,0x7C,0x7D,0xF7,0xDF,0x7C,0x38,0xE3,0x8E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x38,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x38,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 5
0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x7D,0xF7,0xDF,0x00,0x38,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 6
0x00,0x00,0x00,0x00,0x38,0xE3,0x8E,0x38,0x7D,0xF7,0xDF,0x7C,0x7D,0xF7,0xDF,0x7C,0x7D,0xF7,0xDF,0x7C,0x38,0xE3,0x8E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x01,0xF0,0x00,0x00,0x01,0xF0,0x00,0x00,0x01,0xF0,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 7
0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 8
0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x7C,0x00,0x00,0x7C,0x38,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x38,0x01,0xF7,0xDF,0x7C,0x01,0xF7,0xDF,0x7C,0x01,0xF7,0xDF,0x7C,0x00,0xE3,0x8E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x8E,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x01,0xF7,0xDF,0x00,0x00,0xE3,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // 9
};
