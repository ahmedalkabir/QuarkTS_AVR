#include "quarkts_avr_uart.h"
#include <stdio.h>
#include "qqueues.h"
#include <avr/interrupt.h>

// private variables
uint8_t uart_rx_buffer[128];
qQueue_t uart_rx_queue;
qTask_t uart_rx_task;
uint8_t uart_rx_size = 0;

void quarkts_uart_init(uint32_t baudrate){
    tau_uart_init(baudrate);
    qQueue_Setup(&uart_rx_queue, uart_rx_buffer, sizeof(uint8_t), 128);
    qOS_Add_EventTask(&uart_rx_task, uart_rx_fn, qLowest_Priority, NULL);
}


qUINT16_t quarkts_uart_rx_length(){
    return uart_rx_size;
}

uint8_t quarkts_avr_read(){
    if(uart_rx_size > 0){
        uart_rx_size -= 1;
        uint8_t recv_byte = 0;
        if(qQueue_Receive(&uart_rx_queue, (void *)&recv_byte)){
            return recv_byte;
        }else {
            return 0;
        }
    }
    return 0;
}

void uart_rx_fn(qEvent_t evt){
    printf("[uart_rx_fn] called\n");
    qBool_t status = qTask_EventFlags_Check(&uart_rx_task, AVAILABLE_RX, qFalse, qTrue);
    if(status){
        putchar(quarkts_avr_read());
    }

    if(uart_rx_size <= 0){
        qTask_EventFlags_Modify(&uart_rx_task, AVAILABLE_RX, QEVENTFLAG_CLEAR);
    }
}

// interrupts
ISR(USART_RX_vect){
    qQueue_SendToBack(&uart_rx_queue, (void *)&UDR0);
    uart_rx_size += 1;
    qTask_EventFlags_Modify(&uart_rx_task, AVAILABLE_RX, QEVENTFLAG_SET);
}