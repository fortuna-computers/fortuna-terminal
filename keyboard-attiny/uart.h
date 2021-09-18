#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void    uart_initialize();
    
void    uart_putchar(uint8_t c);
void    uart_putstr(const char* s);
void    uart_puthex(uint8_t v);

uint8_t uart_getchar();

#endif
