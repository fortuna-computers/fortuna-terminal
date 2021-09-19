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

    if(MCUSR & (1<<WDRF )) uart_putchar('%');
    if(MCUSR & (1<<BORF )) uart_putchar('$');
    if(MCUSR & (1<<PORF )) uart_putchar('@');
    if(MCUSR & (1<<EXTRF)) uart_putchar('#');
    MCUSR = 0;

    DDRD |= (1 << PD6);
    PORTD |= (1 << PD6);

    _delay_ms(200);

    uart_putchar('|');
    ps2_initialize();
    uart_putchar('|');

    for (;;) {
        ps2_tick();
    }

    return 0;
}

ISR(ANA_COMP_vect)
{
    UDR = 'q'; for(;;);
}

ISR(INT1_vect)
{
    UDR = 'e'; for(;;);
}

ISR(TIMER0_COMPB_vect)
{
    UDR = 'y'; for(;;);
}

ISR(TIMER0_OVF_vect)
{
    UDR = 'u'; for(;;);
}

ISR(TIMER1_CAPT_vect)
{
    UDR = 'i'; for(;;);
}

ISR(TIMER1_COMPA_vect)
{
    UDR = 'o'; for(;;);
}

ISR(TIMER1_COMPB_vect)
{
    UDR = 'p'; for(;;);

}

ISR(TIMER1_OVF_vect)
{
    UDR = 'a'; for(;;);
}

ISR(USART_RX_vect)
{
    UDR = 's'; for(;;);
}

ISR(USART_TX_vect)
{
    UDR = 'd'; for(;;);
}

ISR(USART_UDRE_vect)
{
    UDR = 'f'; for(;;);
}

ISR(USI_OVERFLOW_vect)
{
    UDR = 'g'; for(;;);
}

ISR(USI_START_vect)
{
    UDR = 'h'; for(;;);
}

ISR(WDT_OVERFLOW_vect)
{
    UDR = 'j'; for(;;);
}

ISR(BADISR_vect)
{
    UDR = '!'; for(;;);
}
