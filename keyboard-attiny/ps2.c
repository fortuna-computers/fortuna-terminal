#include "ps2.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdbool.h>
#include <stdint.h>

// AVR PD2 (INT0) = PS/2 CLK
// AVR PD3 (INT1) = PS/2 DATA

static volatile uint16_t ps2_data = 0;
static volatile uint8_t  ps2_size = 0;
static volatile int      ps2_last_data = NO_DATA;

void ps2_initialize()
{
    // setup INT0 (CLK) interrupt
    cli();
    GIMSK = (1 << INT0);   // Enable INT0
    MCUCR = (1 << ISC01);  // The falling edge of INT0 generates an interrupt request

    // setup timer to every 1 ms
    OCR0A = 92;               // 1 ms
    TCCR0A |= (1 << WGM01);   // set CTC
    TCCR0B |= (1 << CS02);    // prescaler 1/256
    TIMSK = (1 << OCIE0A);    // fire interrupt on TIMER0 match

    sei();
}

int ps2_new_data()
{
    if (ps2_last_data != NO_DATA) {
        int tmp = (ps2_last_data >> 1) & 0xff;
        ps2_last_data = NO_DATA;
        return tmp;
    }

    return NO_DATA;
}

ISR(INT0_vect)   // interrupt when clock line is pulled low
{
    if (ps2_size < 10) {
        uint8_t data = (PIND & (1 << PIND3)) ? 1 : 0;
        if (data) {
            ps2_data |= (1 << ps2_size);
        }
        ++ps2_size;
    } else {
        ps2_last_data = (int) ps2_data;
        ps2_size = 0;
        ps2_data = 0;
    }

    TCNT0 = 0;  // reset timer
}

ISR(TIMER0_COMPA_vect)   // interrupt when timer reaches 1 ms
{
    // 1 ms without communcation - resets everything
    ps2_size = 0;
    ps2_data = 0;
    ps2_last_data = NO_DATA;
    TCNT0 = 0;  // reset timer
}
