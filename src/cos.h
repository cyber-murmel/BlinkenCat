#include <avr/pgmspace.h>

#ifndef COS_H
#define COS_H

extern const uint8_t cos_lut[] PROGMEM;
extern const uint16_t COS_LUT_LEN;

#define COS(X) pgm_read_byte( &cos_lut[X])

#endif
