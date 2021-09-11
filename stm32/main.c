#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void gpio_setup()
{
    rcc_periph_clock_enable(RCC_GPIOC);          // enable GPIO clock
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ,
            GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);   // set GPIO12 as output push-pull
}

int main()
{
    int i;

    gpio_setup();

    while (1) {
        gpio_toggle(GPIOC, GPIO12);   // LED on/off
        for (i = 0; i < 800000; i++)  // busy wait
            __asm__("nop");
    }

    return 0;
}
