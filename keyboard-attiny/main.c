#include "uart.h"
#include "ps2.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
    _delay_ms(200);
    uart_initialize();
    _delay_ms(200);

    /*
    if(MCUSR & (1<<WDRF )) uart_putchar('%');
    if(MCUSR & (1<<BORF )) uart_putchar('$');
    if(MCUSR & (1<<PORF )) uart_putchar('@');
    if(MCUSR & (1<<EXTRF)) uart_putchar('#');
    MCUSR = 0;

    DDRD |= (1 << PD6);
    PORTD |= (1 << PD6);

    _delay_ms(200);
    
    uart_putchar('|');
    */

    ps2_initialize();

    // uart_putchar('|');

    for (;;) {
        ps2_tick();
    }

    return 0;
}

ISR(BADISR_vect)
{
    UDR = '!'; for(;;);
}
