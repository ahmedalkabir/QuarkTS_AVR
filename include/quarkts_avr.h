#ifndef QUARK_TS_H
#define QUARK_TS_H

#include <stdio.h>
#include "tau_avr.h"
#include "QuarkTS.h"
#include <avr/interrupt.h>

#define AVAILABLE_RX QEVENTFLAG_01
#define POSSIBLE_TO_READ QEVENTFLAG_02

void quarkts_avr_init();
qUINT32_t disable_interrupt();
void enable_interrupt(qUINT32_t);
int uart_printf(char, FILE *);

#endif