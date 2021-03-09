#ifndef _QUARKTS_AVR_UART_H_
#define _QUARKTS_AVR_UART_H_


#include "quarkts_avr.h"
#include "tau_uart.h"

void uart_rx_fn(qEvent_t);

void quarkts_uart_init(uint32_t);
qUINT16_t quarkts_uart_available();
qUINT16_t quarkts_uart_rx_length();
uint8_t quarkts_avr_read();
#endif