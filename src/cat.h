#ifndef CAT_H
#define CAT_H

#ifndef SENSOR_REG
#define SENSOR_REG B
#endif

#ifndef SENSOR_PIN
#define SENSOR_PIN 4
#endif

void init_cat(void);

uint8_t get_sensor(void);

#endif //CAT_H
