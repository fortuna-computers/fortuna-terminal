typedef struct __attribute__((__packed__)) {
    uint8_t     data;
    char        chr;
    char        shifted;
} PS2_Scancode;

static const PS2_Scancode ps2_scancodes[] PROGMEM = {
    { 0x76, '\e', 0   },

    { 0x0e, '\'', '"' },
    { 0x16, '1',  '!' },
    { 0x1e, '2',  '@' },
    { 0x26, '3',  '#' },
    { 0x25, '4',  '$' },
    { 0x2e, '5',  '%' },
    { 0x36, '6',  '"' },
    { 0x3d, '7',  '&' },
    { 0x3e, '8',  '*' },
    { 0x46, '9',  '(' },
    { 0x45, '0',  ')' },
    { 0x4e, '-',  '_' },
    { 0x55, '_',  '+' },
    { 0x66, 127,  0   },

    { 0x0d, '\t', 0   },
    { 0x15, 'q',  'Q' },
    { 0x1d, 'w',  'W' },
    { 0x24, 'e',  'E' },
    { 0x2d, 'r',  'R' },
    { 0x2c, 't',  'T' },
    { 0x35, 'y',  'Y' },
    { 0x3c, 'u',  'U' },
    { 0x43, 'i',  'I' },
    { 0x44, 'o',  'O' },
    { 0x4d, 'p',  'P' },
    { 0x54, '\'',  '`' },
    { 0x5b, '[',  '{' },
    { 0x5a, '\n', 0   },

    { 0x1c, 'a',  'A' },
    { 0x1b, 's',  'S' },
    { 0x23, 'd',  'D' },
    { 0x2b, 'f',  'F' },
    { 0x34, 'g',  'G' },
    { 0x33, 'h',  'H' },
    { 0x3b, 'j',  'J' },
    { 0x42, 'k',  'K' },
    { 0x4b, 'l',  'L' },
    { 0x52, '~',  '^' },
    { 0x5d, ']',  '}' },

    { 0x61, '\\', '|' },
    { 0x1a, 'z',  'Z' },
    { 0x22, 'x',  'X' },
    { 0x21, 'c',  'C' },
    { 0x2a, 'v',  'V' },
    { 0x32, 'b',  'B' },
    { 0x31, 'n',  'N' },
    { 0x3a, 'm',  'M' },
    { 0x41, ',',  '<' },
    { 0x49, '.',  '>' },
    { 0x4a, ';',  ':' },

    { 0x29, ' ', 0    },

    { 0x00,  0 ,   0  }
};

typedef struct __attribute__((__packed__)) {
    uint8_t data;
    PGM_P   sequence;
} PS2_ScancodeSpecial;

static const char SEQ_F1[]     PROGMEM = "\eOP";
static const char SEQ_F2[]     PROGMEM = "\eOQ";
static const char SEQ_F3[]     PROGMEM = "\eOR";
static const char SEQ_F4[]     PROGMEM = "\eOS";
static const char SEQ_F5[]     PROGMEM = "\eO[15~";
static const char SEQ_F6[]     PROGMEM = "\eO[17~";
static const char SEQ_F7[]     PROGMEM = "\eO[18~";
static const char SEQ_F8[]     PROGMEM = "\eO[19~";
static const char SEQ_F9[]     PROGMEM = "\eO[20~";
static const char SEQ_F10[]    PROGMEM = "\eO[21~";
static const char SEQ_F11[]    PROGMEM = "\eO[23~";
static const char SEQ_F12[]    PROGMEM = "\eO[24~";
static const char SEQ_UP[]     PROGMEM = "\e[A";
static const char SEQ_DOWN[]   PROGMEM = "\e[B";
static const char SEQ_RIGHT[]  PROGMEM = "\e[C";
static const char SEQ_LEFT[]   PROGMEM = "\e[D";
static const char SEQ_HOME[]   PROGMEM = "\e[H";
static const char SEQ_END[]    PROGMEM = "\e[F";
static const char SEQ_INSERT[] PROGMEM = "\e[2~";
static const char SEQ_DELETE[] PROGMEM = "\e[3~";
static const char SEQ_PGUP[]   PROGMEM = "\e[5~";
static const char SEQ_PGDOWN[] PROGMEM = "\e[6~";

static const PS2_ScancodeSpecial ps2_scancodes_special[] PROGMEM = {
    { 0x05, SEQ_F1 },
    { 0x06, SEQ_F2 },
    { 0x04, SEQ_F3 },
    { 0x0c, SEQ_F4 },
    { 0x03, SEQ_F5 },
    { 0x0b, SEQ_F6 },
    { 0x83, SEQ_F7 },
    { 0x0a, SEQ_F8 },
    { 0x01, SEQ_F9 },
    { 0x09, SEQ_F10 },
    { 0x78, SEQ_F11 },
    { 0x07, SEQ_F12 },

    { 0x75, SEQ_UP },
    { 0x72, SEQ_DOWN },
    { 0x6b, SEQ_LEFT },
    { 0x74, SEQ_RIGHT },

    { 0x70, SEQ_INSERT },
    { 0x6c, SEQ_HOME },
    { 0x7d, SEQ_PGUP },
    { 0x71, SEQ_DELETE },
    { 0x69, SEQ_END },
    { 0x7a, SEQ_PGDOWN },

    { 0x00, 0 }
};
