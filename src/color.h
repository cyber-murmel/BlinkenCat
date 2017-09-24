#include <stdint.h>
#include "cos.h"

#ifndef COLOR_H
#define COLOR_H

#define HUE_MAX (6 *  COS_LUT_LEN)

typedef uint8_t pwm_t;

typedef struct {
    pwm_t red, green, blue;
} rgb_s_t;

typedef struct {
    pwm_t red, green, blue, white;
} rgbw_s_t;

typedef struct {
    uint16_t hue;
    pwm_t saturation, brightnes;
} hsb_s_t;

typedef union {
    rgb_s_t rgb_struct;
    pwm_t rgb_array[3];
} rgb_t;

typedef union {
    rgbw_s_t rgbw_struct;
    pwm_t rgbw_array[4];
    struct rgb_plus_w_s {rgb_s_t rgb_struct; uint8_t white;} rgb_plus_w;
} rgbw_t;

typedef union {
    hsb_s_t hsb_struct;
} hsb_t;

rgb_t hsb_to_rgb(hsb_t hsb);

#endif // COLOR_H
