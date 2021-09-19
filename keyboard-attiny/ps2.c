/* TODO:
 *   - caps lock
 *   - num lock
 */

#include "ps2.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <stdbool.h>
#include <stdint.h>

#include "uart.h"

// AVR PD2 (INT0) = PS/2 CLK
// AVR PD3 (INT1) = PS/2 DATA

static volatile uint16_t ps2_data = 0;
static volatile uint8_t  ps2_size = 0;
static volatile int      ps2_last_data = NO_DATA;
static volatile int      ps2_ignore_next = 0;
static volatile bool     ps2_reset = false;

static volatile struct {
    bool    last_was_special : 1;
    bool    last_was_break   : 1;
    bool    shifted          : 1;
    uint8_t pause_counter    : 4;
} ps2_state = { false, false, false, 0 };

#include "scancodes.c"

#define PS2_BREAK   0xf0
#define PS2_SPECIAL 0xe0
#define PS2_PAUSE   0xe1
#define PS2_LSHIFT  0x12
#define PS2_RSHIFT  0x59

static bool ps2_parse_special_chars(uint8_t data)
{
    switch (data) {
        case PS2_BREAK:
            ps2_state.last_was_break = true;
            return true;
        case PS2_SPECIAL:
            ps2_state.last_was_special = true;
            return true;
        case PS2_PAUSE:
            ps2_state.pause_counter = 8;
            return true;
    }

    return false;
}

static char ps2_translate(uint8_t data)
{
    uint8_t ret = NO_DATA;

    // manage SHIFT
    if (data == PS2_LSHIFT || data == PS2_RSHIFT) {
        ps2_state.shifted = !ps2_state.last_was_break;
        goto done;
    }

    // manage BREAK (key release)
    if (ps2_state.last_was_break)
        goto done;

    // manage regular keys (1 byte output)
    size_t i = 0;
    for (;;) {
        PS2_Scancode sc;
        memcpy_P(&sc, &ps2_scancodes[i], sizeof(PS2_Scancode));
        if (sc.data == 0x0)
            break;

        if (data == sc.data) {
            if (ps2_state.shifted && sc.shifted) {
                uart_putchar(sc.shifted);
            } else {
                uart_putchar(sc.chr);
            }
        }
        ++i;
    }

    // manage special keys (1 byte input / n byte output)
    i = 0;
    for (;;) {
        PS2_ScancodeSpecial sc;
        memcpy_P(&sc, &ps2_scancodes_special[i], sizeof(PS2_ScancodeSpecial));
        if (sc.data == 0x0)
            break;

        if (data == sc.data && ps2_state.last_was_special) {
            char buf[10] = { 0 };
            strncpy_P(buf, sc.sequence, 9);
            for (char* p = buf; *p; ++p)
                uart_putchar(*p);
        }
        ++i;
    }

done:
    ps2_state.last_was_special = false;
    ps2_state.last_was_break = false;
    ps2_state.pause_counter = 0;
    return ret;
}

void ps2_initialize()
{
    // setup INT0 (CLK) interrupt
    cli();
    GIMSK = (1 << INT0);   // Enable INT0
    MCUCR = (1 << ISC01);  // The falling edge of INT0 generates an interrupt request

    // setup timer to every 1 ms
    OCR0A = 45;               // 1 ms
    TCCR0A |= (1 << WGM01);   // set CTC
    TCCR0B |= (1 << CS01) | (1 << CS00);    // prescaler 1/64
    TIMSK = (1 << OCIE0A);    // fire interrupt on TIMER0 match

    sei();
}

void ps2_tick()
{
    if (ps2_last_data != NO_DATA) {
        uint8_t data = (uint8_t)((ps2_last_data >> 1) & 0xff);  // remove PS/2 envelope
        // uart_puthex(data);
        ps2_last_data = NO_DATA;                                // reset data
        if (ps2_parse_special_chars(data))
            return;
        ps2_translate(data);
    }

    if (ps2_reset) {
        ps2_size = 0;
        ps2_data = 0;
        ps2_last_data = NO_DATA;
        ps2_reset = false;
        TCNT0 = 0;  // reset timer
    }
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
    ps2_reset = true;
}
