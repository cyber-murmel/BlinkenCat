#include <stdint.h>
#include "color.h"
#include "cos.h"
#include "cos_lut.h"

uint8_t hue_to_curve(uint16_t hue) {
    hue %= HUE_MAX;
    uint16_t x = hue % (sizeof cos_lut);
    if(hue < (HUE_MAX / 6)) {
        return (255 - COS(x)) >> 1;
    }
    else if (hue < (2 * (HUE_MAX / 6))) {
        return 127+(COS((sizeof cos_lut)-x-1) >> 1);
    }
    else if (hue < (3 * (HUE_MAX / 6))) {
        return 127+(COS(x) >> 1);
    }
    else if (hue < (4 * (HUE_MAX / 6))) {
        return (255 - COS((sizeof cos_lut)-x-1)) >> 1;
    }
    else {
        return 0;
    }
}

rgb_t hsb_to_rgb(hsb_t hsb) {
    rgb_t result;

    result.rgb_struct.red = hue_to_curve(hsb.hsb_struct.hue);
    result.rgb_struct.green = hue_to_curve(hsb.hsb_struct.hue + (HUE_MAX / 3));
    result.rgb_struct.blue = hue_to_curve(hsb.hsb_struct.hue + (2 * HUE_MAX / 3));

    return result;
}
