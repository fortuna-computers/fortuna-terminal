PROJECT=fortuna-terminal-keyboard
OBJECTS=main.o uart.o ps2.o
AVRDUDE_FLAGS=-p attiny2313 -C ./avrdude_gpio.conf -c pi_1 -B 0.5 -V
FUSES=-U efuse:w:0xff:m -U hfuse:w:0xdf:m -U lfuse:w:0xe0:m   # external clock from VGA uc
MCU=attiny2313a
F_CPU=24000000UL

CC=avr-gcc
CPPFLAGS=-std=c11 -Wall -Wextra -Os -DF_CPU=${F_CPU} -mmcu=${MCU} -ffunction-sections -fdata-sections -I../common
# CPPFLAGS+=-DRUN_TESTS  # execute tests on initialization
# CPPFLAGS+=-DDEBUG      # print debugging information during execution
# CPPFLAGS+=-DSTEP       # wait for a keypress before each step

all: ${PROJECT}.hex

${PROJECT}.hex: ${PROJECT}.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
	arm-linux-gnueabihf-size ${PROJECT}.hex

${PROJECT}.elf: ${OBJECTS}
	$(CC) -mmcu=${MCU} -o $@ $^ -Wl,--gc-sections
	avr-size -C --mcu=${MCU} ${PROJECT}.elf	

test-connection:
	sudo avrdude ${AVRDUDE_FLAGS}

clean:
	rm -f boot.c *.elf *.o *.hex z80/*.rom

upload: ${PROJECT}.hex
	sudo avrdude ${AVRDUDE_FLAGS} -U flash:w:$<:i

fuse:
	sudo avrdude ${AVRDUDE_FLAGS} ${FUSES}

# vim: set ts=8 sts=8 sw=8 noexpandtab:
