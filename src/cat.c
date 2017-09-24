#include <avr/io.h>
#include <stdint.h>
#include "cat.h"
#include "io_helper.h"

void init_cat(void) {
    ON(SENSOR_REG, SENSOR_PIN);
    DDR(SENSOR_REG) &= ~(1 << SENSOR_PIN);
}

uint8_t get_sensor(void) {
    return READ(SENSOR_REG, SENSOR_PIN);
}
