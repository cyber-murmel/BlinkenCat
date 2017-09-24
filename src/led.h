#include <avr/io.h>
#include "color.h"

#ifndef LED_H
#define LED_H

typedef struct {
    uint8_t red, green, blue, white;
} rgbw_pins_s_t;

typedef union {
    rgbw_pins_s_t struct_t;
    uint8_t array[4];
} rgbw_pins_t;

void init_leds(void);

void pwm_color(rgbw_t color);

#endif // LED_H
