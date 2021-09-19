#include "videoout.h"

#include <avr/io.h>

void video_out_init()
{
    DDRB = 0b1111111;
}

void video_out(char c)
{
}
