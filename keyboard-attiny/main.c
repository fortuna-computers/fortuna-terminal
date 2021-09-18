#include "uart.h"
#include "ps2.h"

#include <util/delay.h>

int main()
{
    uart_initialize();
    ps2_initialize();

    _delay_ms(500);

    uart_putchar('|');
    uart_putchar('|');

    for (;;) {
        int d = ps2_new_data();
        if (d != NO_DATA)
            uart_puthex((uint8_t) d);
    }
    return 0;
}
