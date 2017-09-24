#include <avr/io.h>

#ifndef LED_CONF_H
#define LED_CONF_H

#ifndef LED_REG
#define LED_REG B
#endif

rgbw_pins_t rgbw_pins = {.array = {0, 1, 2, 3}};

#endif // LED_CONF_H
