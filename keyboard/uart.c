#include "uart.h"

#include <avr/io.h>

#include "videoout.h"

void uart_initialize()
{
    // set baud rate - http://ruemohr.org/~ircjunk/avr/baudcalc/avrbaudcalc-1.0.8.php?postbitrate=38400&postclock=24
    int ubrr = 4;       // 38400 at 3 Mhz
    UBRRH = (ubrr>>8);
    UBRRL = (ubrr);

    // set config
    UCSRC = (1<<UCSZ1) | (1<<UCSZ0);   // Async-mode 
    UCSRB = (1<<RXEN) | (1<<TXEN);     // Enable Receiver and Transmitter
}


void uart_putchar(uint8_t c) 
{
    while (!( UCSRA & (1<<UDRE)));     // Wait for empty transmit buffer
    UDR = c;
}

uint8_t uart_getchar()
{
    while (!( UCSRA & (1<<RXC)));  // wait for empty receive buffer
    return UDR;
}

void uart_putstr(const char* s)
{
    int i = 0;
    while (s[i])
        uart_putchar(s[i++]);
}

static void uart_puthex_v(uint8_t v)
{
    if (v <= 9)
        uart_putchar(v + '0');
    else
        uart_putchar(v + 'A' - 10);
}

void uart_puthex(uint8_t v)
{
    uart_puthex_v(v >> 4);
    uart_puthex_v(v & 0xf);
    uart_putchar(' ');
}

void uart_tick()
{
    if (UCSRA & (1<<RXC)) {
        video_out(UDR);
    }
}
