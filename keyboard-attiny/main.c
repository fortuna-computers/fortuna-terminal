#include "uart.h"

int main()
{
    uart_initialize();
    // print_hex(0x42);

    for (;;) {
        uart_getchar();
        uart_puthex(0xAF);
    }
    return 0;
}
