#include "ps2.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>

// AVR PD2 (INT0) = PS/2 CLK
// AVR PD3 (INT1) = PS/2 DATA

static volatile uint16_t ps2_data = 0;
static volatile uint8_t  ps2_size = 0;
static volatile int16_t  ps2_last_data = -1;

void ps2_initialize()
{
    cli();
    GIMSK = (1 << INT0);   // Enable INT0
    MCUCR = (1 << ISC01);  // The falling edge of INT0 generates an interrupt request
    sei();
}

int ps2_new_data()
{
    if (ps2_last_data != -1) {
        if (ps2_last_data & 1 != 0) {  // start bit
            uart_putchar('!'); for(;;);
        }

        if (ps2_last_data & (1 << 11) != 1) {  // stop bit
            uart_putchar('@'); for(;;);
        }

        int16_t tmp = (ps2_last_data >> 1) & 0xff;

        if (tmp % 2 == ps2_last_data & (1 << 10)) {
            uart_putchar('#'); for(;;);
        }

        ps2_last_data = -1;
        return tmp;
    }

    return -1;
}

ISR (INT0_vect)   // interrupt when clock line is pulled low
{
    if (ps2_size < 10) {
        uint8_t data = (PIND & (1 << PIND3)) ? 1 : 0;
        if (data)
            ps2_data |= (1 << ps2_size);
        ++ps2_size;
    } else {
        ps2_last_data = (int16_t) ps2_data;
        ps2_size = 0;
        ps2_data = 0;
    }
}
