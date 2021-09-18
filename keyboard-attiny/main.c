#include "uart.h"
#include "ps2.h"

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    _delay_ms(200);

    DDRD |= (1 << PD6);
    PORTD |= (1 << PD6);

    uart_initialize();
    ps2_initialize();

    _delay_ms(200);

    uart_putchar('|');
    uart_putchar('|');

    for (;;) {
        ps2_tick();
    }

    return 0;
}
