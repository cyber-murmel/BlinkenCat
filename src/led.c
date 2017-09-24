#include <avr/io.h>
#include "led.h"
#include "led_conf.h"
#include "io_helper.h"
#include "color.h"

void init_leds(void) {
    for(uint8_t i = 0 ; i < sizeof rgbw_pins.array; i++) {
        OFF(LED_REG, rgbw_pins.array[i]);
        DDR(LED_REG) |= (1 << rgbw_pins.array[i]);
    }
}

void pwm_color (rgbw_t color) {
    for(pwm_t pwm = 0; pwm < (1 << (8 * (sizeof(pwm_t))))-1; pwm++) {
        for(uint8_t i = 0 ; i < sizeof rgbw_pins.array; i++) {
            if(pwm < color.rgbw_array[i]) {
                ON(LED_REG, rgbw_pins.array[i]);
            } else {
                OFF(LED_REG, rgbw_pins.array[i]);
            }
        }
    }
}
