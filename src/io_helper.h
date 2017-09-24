#include <avr/io.h>

#ifndef IO_HELPER_H
#define IO_HELPER_H

#define DDR_(X) DDR##X
#define DDR(X) DDR_(X)
#define PORT_(X) PORT##X
#define PORT(X) PORT_(X)
#define PIN_(X) PIN##X
#define PIN(X) PIN_(X)

#define OFF(REG, POS) PORT(REG) &= ~(1 << POS)
#define ON(REG, POS) PORT(REG) |= (1 << POS)
#define READ(REG, POS) (PIN(REG)&(1 << POS))>>POS

#endif // IO_HELPER_H
