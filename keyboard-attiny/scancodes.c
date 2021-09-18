typedef struct {
    bool        special;
    uint8_t     data;
    char        chr;
    char        shifted;
} PS2_Scancode;

static const PS2_Scancode ps2_scancodes[] PROGMEM = {
    { false, 0x1c, 'a', 'A' },
    { false, 0x32, 'b', 'B' },
    { false, 0x21, 'c', 'C' },
    { false, 0x00,  0 ,  0  }
};
