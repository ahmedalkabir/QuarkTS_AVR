#ifndef QUARK_TS_H
#define QUARK_TS_H

#include <stdio.h>
#include "tau_avr.h"
#include "QuarkTS.h"
#include <avr/interrupt.h>

void quarkts_avr_init();
int uart_printf(char, FILE *);

#endif