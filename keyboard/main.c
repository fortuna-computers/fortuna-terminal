#include "uart.h"
#include "ps2.h"
#include "videoout.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define HALT_CHAR 1

int main()
{
    _delay_ms(50);
    uart_initialize();
    _delay_ms(50);

    if(MCUSR & (1<<WDRF )) uart_putchar('%');
    if(MCUSR & (1<<BORF )) uart_putchar('$');
    if(MCUSR & (1<<PORF )) uart_putchar('@');
    if(MCUSR & (1<<EXTRF)) uart_putchar('#');
    MCUSR = 0;

    DDRD &= ~(1 << DDD4);
    PORTD |= (1 << PORTD4);

    _delay_ms(200);
    
    uart_putchar('|');

    ps2_initialize();
    video_out_init();
    _delay_ms(50);

    uart_putchar('|');

    for (;;) {
        ps2_tick();
        uart_tick();
        if (!bit_is_set(PIND, PIND4)) {  // halt condition for vga
            uart_putstr("HALT!");  // TODO - pgmspace
            video_out(HALT_CHAR);
            for (;;);
        }
    }

    return 0;
}

ISR(BADISR_vect)
{
    UDR = '!'; for(;;);
}
