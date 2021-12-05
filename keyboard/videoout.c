#include "videoout.h"

#include <avr/io.h>
#include <util/delay.h>

#include <stdbool.h>

static bool current = false;

void video_out_init()
{
    DDRB = 0xff;           // transmission line
    DDRD |= (1 << DDD5);    // data_new
}

void video_out(char c)
{
    PORTB = c;
    current = !current;
    if (current)
        PORTD |= (1 << PORTD5);
    else
        PORTD &= ~(1 << PORTD5);
    _delay_us(30);
}
