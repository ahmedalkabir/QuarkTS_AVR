#include "tau_uart.h"
#include "quarkts_avr.h"

#define TIMER_TICK 0.001 // 1ms

void quarkts_avr_init()
{
    TCCR0A |= (1 << WGM01);              // CTC mode
    TCCR0B |= (1 << CS00) | (1 << CS01); // CPU_CLOCK / 64
    TIMSK0 |= (1 << OCIE0A);             // enable compare match A interrupt
    // as it will be called every 1ms
    TCNT0 = 0;
    OCR0A = 249;

    // enable interrupt
    sei();

    qOS_Setup(NULL, TIMER_TICK, NULL);
    qCritical_SetInterruptsED(enable_interrupt, disable_interrupt);

    static FILE m_stdout = FDEV_SETUP_STREAM(uart_printf, NULL, _FDEV_SETUP_WRITE);

    stdout = &m_stdout;
}

int uart_printf(char data, FILE *stream){
    tau_uart_write_byte((uint8_t)data);
    return 0;
}

// interrupt function
ISR(TIMER0_COMPA_vect)
{
    qClock_SysTick();
}

qUINT32_t disable_interrupt(){
    // save current context
    qUINT32_t current_status = (qUINT32_t)(SREG);
    cli(); // disable interrupt

    return current_status;
}

void enable_interrupt(qUINT32_t reg){
    SREG = (qUINT8_t)(reg & 0xFF);
    sei();// enable interrupt
}