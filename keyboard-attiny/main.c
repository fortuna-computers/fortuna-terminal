#include "uart.h"
#include "ps2.h"

int main()
{
    uart_initialize();
    ps2_initialize();

    for (;;) {
        int d = ps2_new_data();
        if (d != -1)
            uart_puthex((uint8_t) d);
    }
    return 0;
}
