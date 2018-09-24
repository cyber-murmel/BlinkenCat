#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h> 
#include <avr/sleep.h> 
#include <string.h>
#include "led.h"
#include "color.h"
#include "cat.h"

#define EEPROM_ADDR (0)

typedef enum {
    OFF,
    RED,
    GREEN,
    BLUE,
    WHITE,
    RAINBOW,
    SUN,
    NUM_STATES,
} state_t;

volatile state_t state = RED;

rgbw_t
    red   = {.rgbw_struct = {.red = 30, .green = 0, .blue =  0, .white =  0}},
    green = {.rgbw_struct = {  0,  30,   0,   0}},
    blue  = {.rgbw_struct = {  0,   0,  30,   0}},
    white = {.rgbw_struct = {  0,   0,   0,  30}},
    sun   = {.rgbw_struct = {255, 255, 255, 255}},
    off   = {.rgbw_struct = {  0,   0,   0,   0}};

void init_interrups(void) {
    GIMSK = 1 << PCIE;          // turns on pin change interrupts
    PCMSK = 1 << SENSOR_PIN;    // turn on interrupts on sensor pin
    sei();                      // enables interrupts
}

int main(void) {
    /* When reset, read whether program shall be run */
    uint8_t run = eeprom_read_byte (EEPROM_ADDR);
    /* invert value and write back to eeprom */
    eeprom_write_byte (EEPROM_ADDR, run ? 0 : 1);
    if(!run) {
        /* disable all interrupts and go to sleep */
        cli();
        sleep_mode();
    }
    uint16_t hue = 0;
    hsb_t hsb = {.hsb_struct = {0, 100, 100}};
    rgb_t rgb;
    rgbw_t rgbw;
    init_leds();
    init_cat();
    init_interrups();

    while(1) {
        switch(state) {
            case RED:
                pwm_color(red);
                break;
            case GREEN:
                pwm_color(green);
                break;
            case BLUE:
                pwm_color(blue);
                break;
            case WHITE:
                pwm_color(white);
                break;
            case SUN:
                pwm_color(sun);
                break;
            case RAINBOW:
                hsb.hsb_struct.hue = hue;
                rgb = hsb_to_rgb(hsb);
                memcpy(rgbw.rgbw_array, rgb.rgb_array, sizeof rgb);
                pwm_color(rgbw);
                hue = (hue + 1) % HUE_MAX;
                break;
            case OFF:
            default:
                pwm_color(off);
                break;
        }
    }

    return 0;
}

ISR(PCINT0_vect)
{
    cli();                                  // disables interrupts
    if(!get_sensor()) {
        state = (state + 1) % NUM_STATES;  // Increment volatile variable
    }
    sei();                                  // enables interrupts
}
