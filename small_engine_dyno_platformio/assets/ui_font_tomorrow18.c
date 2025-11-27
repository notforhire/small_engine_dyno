/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: --bpp 1 --size 18 --font /home/peg_leg/platformIO/dyno/assets/Tomorrow-Italic.ttf -o /home/peg_leg/platformIO/dyno/assets/ui_font_tomorrow18.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_TOMORROW18
#define UI_FONT_TOMORROW18 1
#endif

#if UI_FONT_TOMORROW18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x11, 0x33, 0x32, 0x22, 0x26, 0x0, 0x44,

    /* U+0022 "\"" */
    0xd9, 0x99,

    /* U+0023 "#" */
    0xc, 0xc0, 0xc8, 0x7f, 0xf1, 0x98, 0x19, 0x1,
    0x10, 0xff, 0xc3, 0x30, 0x22, 0x2, 0x60,

    /* U+0024 "$" */
    0x1, 0x0, 0x20, 0x7f, 0x99, 0x82, 0x30, 0x44,
    0x8, 0x81, 0x90, 0x1f, 0x80, 0xd8, 0x19, 0x2,
    0x20, 0x44, 0x9, 0x83, 0x33, 0xf8, 0xc, 0x1,
    0x0,

    /* U+0025 "%" */
    0x0, 0x4, 0x70, 0x32, 0x61, 0x98, 0x8c, 0x42,
    0x61, 0x9b, 0x3, 0xd8, 0x0, 0x40, 0x2, 0x0,
    0x13, 0xc0, 0x99, 0x84, 0x46, 0x21, 0x19, 0x6,
    0x48, 0x1e, 0x0, 0x0,

    /* U+0026 "&" */
    0xf, 0x1, 0x98, 0x30, 0x83, 0x8, 0x31, 0x81,
    0xf0, 0xe, 0x3, 0xe0, 0x66, 0xc, 0x33, 0xc1,
    0xec, 0xc, 0xc1, 0xc7, 0xf6,

    /* U+0027 "'" */
    0xea,

    /* U+0028 "(" */
    0x6, 0x18, 0x61, 0x83, 0x6, 0xc, 0x10, 0x20,
    0xc1, 0x83, 0x6, 0x8, 0x10, 0x20, 0x60, 0xc0,
    0xc0,

    /* U+0029 ")" */
    0x18, 0x18, 0x18, 0x30, 0x60, 0x81, 0x2, 0xc,
    0x18, 0x30, 0x40, 0x81, 0x6, 0xc, 0x18, 0x43,
    0x0,

    /* U+002A "*" */
    0x31, 0x3e, 0xcd, 0x48,

    /* U+002B "+" */
    0x4, 0x2, 0x1, 0x1, 0x80, 0xc7, 0xfc, 0x20,
    0x10, 0x8, 0xc, 0x0,

    /* U+002C "," */
    0x6d, 0x28,

    /* U+002D "-" */
    0xfc,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x0, 0xc0, 0x60, 0x18, 0xc, 0x2, 0x1, 0x80,
    0x40, 0x30, 0x8, 0x6, 0x1, 0x0, 0xc0, 0x20,
    0x18, 0x4, 0x3, 0x0,

    /* U+0030 "0" */
    0x1f, 0xc4, 0xd, 0x81, 0xb0, 0x24, 0x4, 0x80,
    0x90, 0x36, 0x6, 0xc0, 0xd8, 0x13, 0x2, 0x40,
    0x4c, 0x18, 0xfe, 0x0,

    /* U+0031 "1" */
    0x3c, 0x30, 0xc2, 0x8, 0x61, 0x86, 0x18, 0x61,
    0x4, 0x33, 0xf0,

    /* U+0032 "2" */
    0x1f, 0xc6, 0xc, 0x1, 0x80, 0x30, 0xe, 0x3,
    0x80, 0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0, 0x38,
    0xe, 0x1, 0xff, 0x0,

    /* U+0033 "3" */
    0x1f, 0xc6, 0xc, 0x0, 0x80, 0x30, 0x6, 0x1,
    0xc3, 0xe0, 0x6, 0x0, 0x40, 0x18, 0x3, 0x20,
    0x6c, 0x18, 0xfe, 0x0,

    /* U+0034 "4" */
    0x0, 0xc0, 0x70, 0x3c, 0x1a, 0xe, 0x87, 0x63,
    0x98, 0xc6, 0x61, 0xb0, 0x4f, 0xfc, 0xc, 0x3,
    0x0, 0xc0,

    /* U+0035 "5" */
    0x1f, 0xe2, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x7f,
    0x0, 0x30, 0x2, 0x0, 0xc0, 0x18, 0x3, 0x20,
    0x6c, 0x18, 0xfe, 0x0,

    /* U+0036 "6" */
    0x1f, 0xc4, 0xd, 0x81, 0x30, 0x4, 0x0, 0x80,
    0x17, 0xe7, 0x6, 0xc0, 0xd8, 0x1b, 0x2, 0x40,
    0x4c, 0x18, 0xfe, 0x0,

    /* U+0037 "7" */
    0x3f, 0xc0, 0x30, 0x1c, 0x6, 0x3, 0x0, 0xc0,
    0x60, 0x38, 0xc, 0x6, 0x3, 0x80, 0xc0, 0x60,
    0x18, 0x0,

    /* U+0038 "8" */
    0x1f, 0x86, 0x18, 0x81, 0x30, 0x26, 0xc, 0xc1,
    0x8f, 0xe3, 0x6, 0xc0, 0xd8, 0x1a, 0x3, 0x40,
    0x4c, 0x18, 0xfe, 0x0,

    /* U+0039 "9" */
    0x1f, 0xc6, 0xd, 0x81, 0xb0, 0x36, 0x4, 0x80,
    0x98, 0x31, 0xfe, 0x0, 0xc0, 0x18, 0x2, 0x40,
    0x4c, 0x18, 0xfe, 0x0,

    /* U+003A ":" */
    0x24, 0x0, 0x0, 0xd8,

    /* U+003B ";" */
    0x11, 0x0, 0x0, 0x0, 0x64, 0x48,

    /* U+003C "<" */
    0x4, 0x31, 0x8c, 0x61, 0x6, 0xc, 0x18, 0x20,

    /* U+003D "=" */
    0x7f, 0xc0, 0x0, 0x0, 0x0, 0xff, 0xc0,

    /* U+003E ">" */
    0x41, 0x83, 0x6, 0xc, 0x63, 0x18, 0xc2, 0x0,

    /* U+003F "?" */
    0x7e, 0xc3, 0x3, 0x3, 0x3, 0x6, 0x1c, 0x38,
    0x20, 0x20, 0x0, 0x0, 0x60, 0x40,

    /* U+0040 "@" */
    0xf, 0xff, 0x6, 0x0, 0x63, 0x0, 0xc, 0x80,
    0x3, 0x21, 0xe8, 0xc8, 0xce, 0x36, 0x61, 0x89,
    0x98, 0x62, 0x66, 0x19, 0x91, 0x84, 0x64, 0x63,
    0x91, 0xf, 0x38, 0xc0, 0x0, 0x30, 0x0, 0x46,
    0x0, 0x30, 0xff, 0xf8,

    /* U+0041 "A" */
    0x1, 0xc0, 0x3c, 0x2, 0xc0, 0x64, 0x4, 0x40,
    0xc4, 0xc, 0x61, 0x86, 0x18, 0x63, 0xfe, 0x30,
    0x26, 0x2, 0x60, 0x3c, 0x3,

    /* U+0042 "B" */
    0x3f, 0x84, 0x19, 0x81, 0x30, 0x26, 0xc, 0xc1,
    0x9f, 0xe2, 0x6, 0xc0, 0xd8, 0x1b, 0x3, 0x60,
    0x6c, 0x19, 0xfe, 0x0,

    /* U+0043 "C" */
    0x1f, 0xc4, 0xd, 0x80, 0x30, 0x4, 0x0, 0x80,
    0x10, 0x6, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x40,
    0x4c, 0x18, 0xfe, 0x0,

    /* U+0044 "D" */
    0x3f, 0x84, 0x19, 0x81, 0xb0, 0x16, 0x6, 0xc0,
    0xd0, 0x1a, 0x3, 0xc0, 0x58, 0xb, 0x1, 0x60,
    0x6c, 0x19, 0xfe, 0x0,

    /* U+0045 "E" */
    0x3f, 0xe4, 0x1, 0x80, 0x30, 0x6, 0x0, 0xc0,
    0x1f, 0xe2, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x60,
    0xc, 0x1, 0xfe, 0x0,

    /* U+0046 "F" */
    0x3f, 0xc8, 0x6, 0x1, 0x80, 0x60, 0x18, 0x7,
    0xf1, 0x0, 0xc0, 0x30, 0xc, 0x3, 0x0, 0x80,
    0x20, 0x0,

    /* U+0047 "G" */
    0x1f, 0xc4, 0xd, 0x80, 0x30, 0x4, 0x0, 0x80,
    0x10, 0x6, 0x1e, 0xc0, 0x58, 0xb, 0x3, 0x40,
    0xec, 0x3c, 0xfd, 0x0,

    /* U+0048 "H" */
    0x20, 0x32, 0x3, 0x60, 0x26, 0x2, 0x60, 0x66,
    0x6, 0x7f, 0xe4, 0x6, 0xc0, 0x4c, 0xc, 0xc0,
    0xcc, 0xc, 0x80, 0xc8, 0xc,

    /* U+0049 "I" */
    0x3e, 0x10, 0x20, 0xc1, 0x83, 0x6, 0x8, 0x10,
    0x20, 0xc1, 0x83, 0x1f, 0x0,

    /* U+004A "J" */
    0x0, 0xc0, 0x30, 0xc, 0x2, 0x0, 0x80, 0x60,
    0x18, 0x6, 0x1, 0x90, 0x4c, 0x13, 0x4, 0xc3,
    0x1f, 0x80,

    /* U+004B "K" */
    0x20, 0x62, 0xc, 0x61, 0x86, 0x30, 0x66, 0x6,
    0xc0, 0x5c, 0x7, 0xc0, 0xe6, 0xe, 0x60, 0xc3,
    0xc, 0x30, 0x81, 0x88, 0x18,

    /* U+004C "L" */
    0x20, 0x20, 0x60, 0x60, 0x60, 0x60, 0x60, 0x40,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff,

    /* U+004D "M" */
    0x30, 0xe, 0x60, 0x1d, 0xe0, 0x73, 0xc0, 0xa7,
    0x83, 0xcd, 0xd, 0x92, 0x1b, 0x26, 0x66, 0xcc,
    0x89, 0x8b, 0x33, 0x14, 0x66, 0x38, 0xc8, 0x61,
    0x90, 0xc3, 0x0,

    /* U+004E "N" */
    0x30, 0x33, 0x82, 0x78, 0x26, 0x86, 0x6c, 0x66,
    0xc6, 0x44, 0x64, 0x64, 0xc6, 0x4c, 0x2c, 0xc3,
    0xcc, 0x3c, 0x81, 0xc8, 0x18,

    /* U+004F "O" */
    0x1f, 0xc4, 0xd, 0x81, 0xb0, 0x34, 0x6, 0x80,
    0xd0, 0x16, 0x2, 0xc0, 0x58, 0x1b, 0x3, 0x40,
    0x6c, 0x18, 0xfe, 0x0,

    /* U+0050 "P" */
    0x3f, 0x88, 0x36, 0x5, 0x83, 0x60, 0xd8, 0x34,
    0x19, 0xfc, 0xc0, 0x30, 0xc, 0x3, 0x0, 0x80,
    0x20, 0x0,

    /* U+0051 "Q" */
    0x1f, 0xc4, 0xd, 0x81, 0xb0, 0x34, 0x6, 0x80,
    0xd0, 0x16, 0x2, 0xc0, 0x58, 0x1b, 0x3, 0x44,
    0x6c, 0x98, 0xfe, 0x6, 0x0, 0xc0,

    /* U+0052 "R" */
    0x3f, 0xc4, 0xd, 0x81, 0xb0, 0x26, 0x4, 0xc1,
    0x90, 0x23, 0xf8, 0xc3, 0x18, 0x63, 0x4, 0x60,
    0xc8, 0x19, 0x3, 0x0,

    /* U+0053 "S" */
    0x1f, 0xe6, 0x0, 0x80, 0x10, 0x2, 0x0, 0x60,
    0x7, 0xe0, 0x6, 0x0, 0x40, 0x8, 0x1, 0x0,
    0x60, 0x8, 0xfe, 0x0,

    /* U+0054 "T" */
    0xff, 0xc3, 0x0, 0xc0, 0x30, 0x8, 0x2, 0x1,
    0x80, 0x60, 0x18, 0x6, 0x1, 0x0, 0x40, 0x30,
    0xc, 0x0,

    /* U+0055 "U" */
    0x30, 0x13, 0x1, 0x30, 0x33, 0x3, 0x20, 0x32,
    0x3, 0x60, 0x26, 0x2, 0x60, 0x66, 0x6, 0x40,
    0x64, 0x6, 0x60, 0xc3, 0xf8,

    /* U+0056 "V" */
    0x80, 0x70, 0xb, 0x3, 0x60, 0x4c, 0x19, 0x82,
    0x10, 0xc2, 0x10, 0x46, 0xc, 0x81, 0x90, 0x36,
    0x6, 0x80, 0x70, 0x0,

    /* U+0057 "W" */
    0x41, 0x83, 0x41, 0x83, 0x41, 0x82, 0x43, 0x86,
    0x43, 0x86, 0x42, 0x84, 0x46, 0x8c, 0x46, 0x88,
    0x64, 0x88, 0x6c, 0x98, 0x68, 0x90, 0x68, 0xb0,
    0x78, 0xe0, 0x70, 0xe0,

    /* U+0058 "X" */
    0x10, 0x18, 0xc1, 0x86, 0x8, 0x18, 0xc0, 0xcc,
    0x2, 0xc0, 0x1e, 0x0, 0xe0, 0xd, 0x80, 0xcc,
    0x6, 0x30, 0x61, 0x86, 0x4, 0x60, 0x30,

    /* U+0059 "Y" */
    0x80, 0xf0, 0x64, 0x19, 0x8c, 0x66, 0x9, 0x83,
    0xc0, 0xe0, 0x10, 0x4, 0x3, 0x0, 0xc0, 0x30,
    0xc, 0x0,

    /* U+005A "Z" */
    0x1f, 0xf0, 0x7, 0x0, 0xe0, 0xc, 0x1, 0x80,
    0x38, 0x7, 0x0, 0xe0, 0x1c, 0x1, 0x80, 0x30,
    0x7, 0x0, 0x60, 0xf, 0xfc,

    /* U+005B "[" */
    0x1e, 0x20, 0x41, 0x83, 0x6, 0xc, 0x10, 0x20,
    0xc1, 0x83, 0x6, 0x8, 0x10, 0x60, 0xc1, 0x83,
    0xc0,

    /* U+005C "\\" */
    0x8c, 0xcc, 0xc4, 0x46, 0x66, 0x62, 0x23, 0x33,

    /* U+005D "]" */
    0x1e, 0xc, 0x18, 0x30, 0x60, 0x81, 0x6, 0xc,
    0x18, 0x30, 0x40, 0x81, 0x6, 0xc, 0x18, 0x23,
    0xc0,

    /* U+005E "^" */
    0x1c, 0x3c, 0x66, 0x42,

    /* U+005F "_" */
    0xff, 0x80,

    /* U+0060 "`" */
    0xcc, 0x80,

    /* U+0061 "a" */
    0x3f, 0x0, 0xc0, 0x20, 0x33, 0xfb, 0xf, 0x5,
    0x86, 0xc7, 0x3f, 0x80,

    /* U+0062 "b" */
    0x10, 0x4, 0x3, 0x0, 0xc0, 0x3f, 0x8e, 0x33,
    0xc, 0x83, 0x60, 0xd8, 0x36, 0x9, 0x82, 0x71,
    0x97, 0xc0,

    /* U+0063 "c" */
    0x3e, 0x63, 0x41, 0xc0, 0xc0, 0xc0, 0x80, 0x80,
    0xc0, 0x7e,

    /* U+0064 "d" */
    0x0, 0xc0, 0x30, 0xc, 0x2, 0x3e, 0x98, 0xec,
    0x1b, 0x6, 0xc1, 0xb0, 0x48, 0x12, 0xc, 0xc7,
    0x1e, 0xc0,

    /* U+0065 "e" */
    0x3e, 0x31, 0xb0, 0x58, 0x2f, 0xf6, 0x2, 0x1,
    0x0, 0xc0, 0x3f, 0x0,

    /* U+0066 "f" */
    0x1c, 0xc6, 0x18, 0xf9, 0x84, 0x10, 0xc3, 0xc,
    0x30, 0x82, 0x0,

    /* U+0067 "g" */
    0x1f, 0x4c, 0x72, 0xd, 0x83, 0x60, 0xd8, 0x24,
    0x9, 0x6, 0x63, 0x8f, 0x60, 0x18, 0x4, 0x3,
    0x1f, 0x80,

    /* U+0068 "h" */
    0x10, 0x4, 0x3, 0x0, 0xc0, 0x3f, 0x8e, 0x33,
    0xc, 0x83, 0x60, 0xd8, 0x36, 0x9, 0x2, 0x41,
    0x90, 0x60,

    /* U+0069 "i" */
    0x13, 0x3, 0x22, 0x26, 0x66, 0x44, 0x40,

    /* U+006A "j" */
    0x4, 0x10, 0x3, 0xc, 0x30, 0x82, 0x18, 0x61,
    0x86, 0x10, 0x41, 0xc, 0xe0,

    /* U+006B "k" */
    0x10, 0x4, 0x3, 0x0, 0xc0, 0x31, 0xc8, 0xc2,
    0x60, 0xb0, 0x7c, 0x1f, 0x6, 0x61, 0x18, 0x43,
    0x10, 0x40,

    /* U+006C "l" */
    0x11, 0x33, 0x33, 0x22, 0x66, 0x66, 0x44,

    /* U+006D "m" */
    0x37, 0x9f, 0x1c, 0x78, 0xcc, 0x18, 0x64, 0x18,
    0x36, 0xc, 0x1b, 0x6, 0xd, 0x83, 0x4, 0x81,
    0x2, 0x40, 0x83, 0x20, 0x41, 0x80,

    /* U+006E "n" */
    0x37, 0x8e, 0x33, 0x4, 0x83, 0x60, 0xd8, 0x36,
    0xd, 0x2, 0x40, 0x90, 0x20,

    /* U+006F "o" */
    0x3f, 0x30, 0xb0, 0x78, 0x3c, 0x16, 0xa, 0x5,
    0x6, 0xc2, 0x3e, 0x0,

    /* U+0070 "p" */
    0x3f, 0x8e, 0x33, 0xc, 0x83, 0x60, 0xd8, 0x36,
    0x9, 0x82, 0x71, 0x97, 0xcc, 0x3, 0x0, 0xc0,
    0x30, 0x0,

    /* U+0071 "q" */
    0x3e, 0xb1, 0xf0, 0x78, 0x3c, 0x1e, 0xa, 0x5,
    0x6, 0xc7, 0x3d, 0x80, 0xc0, 0x40, 0x20, 0x10,

    /* U+0072 "r" */
    0x3f, 0x38, 0x30, 0x20, 0x60, 0x60, 0x60, 0x40,
    0x40, 0x40,

    /* U+0073 "s" */
    0x1f, 0x90, 0x18, 0xc, 0x3, 0xe0, 0x18, 0x4,
    0x2, 0x3, 0x3f, 0x0,

    /* U+0074 "t" */
    0x21, 0x19, 0xf6, 0x21, 0x18, 0xc6, 0x31, 0x87,
    0x0,

    /* U+0075 "u" */
    0x40, 0xa0, 0x50, 0x78, 0x3c, 0x1e, 0xb, 0x5,
    0x6, 0xc7, 0x3d, 0x80,

    /* U+0076 "v" */
    0xc0, 0xf0, 0x6c, 0x11, 0xc, 0x42, 0x19, 0x86,
    0x40, 0xb0, 0x28, 0xc, 0x0,

    /* U+0077 "w" */
    0xc3, 0x5, 0x86, 0x1b, 0x1c, 0x26, 0x28, 0xcc,
    0xd1, 0x9, 0xa2, 0x12, 0x68, 0x2c, 0xd0, 0x51,
    0xe0, 0xe1, 0x80,

    /* U+0078 "x" */
    0x30, 0x62, 0x18, 0x66, 0x6, 0x80, 0xe0, 0x16,
    0x6, 0x41, 0x8c, 0x61, 0x8c, 0x18,

    /* U+0079 "y" */
    0xc0, 0xb0, 0x6c, 0x31, 0xc, 0x66, 0x19, 0x86,
    0xc0, 0xb0, 0x38, 0xe, 0x3, 0x0, 0x80, 0x60,
    0x10, 0x0,

    /* U+007A "z" */
    0x3f, 0x80, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0,
    0xe0, 0xe0, 0x7f, 0x80,

    /* U+007B "{" */
    0xf, 0x18, 0x18, 0x18, 0x10, 0x10, 0x10, 0x30,
    0x30, 0xe0, 0x20, 0x20, 0x20, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x38,

    /* U+007C "|" */
    0x18, 0x84, 0x23, 0x18, 0xc4, 0x21, 0x18, 0xc6,
    0x21, 0x8, 0xc6, 0x0,

    /* U+007D "}" */
    0x1c, 0xc, 0x18, 0x30, 0x60, 0x81, 0x2, 0xc,
    0xc, 0x30, 0x40, 0x81, 0x6, 0xc, 0x18, 0x23,
    0xc0,

    /* U+007E "~" */
    0x39, 0x24, 0xb3, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 64, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 72, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 98, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 10, .adv_w = 221, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 190, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 50, .adv_w = 249, .box_w = 14, .box_h = 16, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 78, .adv_w = 224, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 55, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 100, .adv_w = 101, .box_w = 7, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 117, .adv_w = 101, .box_w = 7, .box_h = 19, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 134, .adv_w = 120, .box_w = 5, .box_h = 6, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 138, .adv_w = 180, .box_w = 9, .box_h = 10, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 150, .adv_w = 65, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 152, .adv_w = 132, .box_w = 6, .box_h = 1, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 153, .adv_w = 65, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 123, .box_w = 10, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 174, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 122, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 183, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 185, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 174, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 183, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 194, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 150, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 195, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 193, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 65, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 65, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 371, .adv_w = 124, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 379, .adv_w = 192, .box_w = 10, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 386, .adv_w = 124, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 394, .adv_w = 158, .box_w = 8, .box_h = 14, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 299, .box_w = 18, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 444, .adv_w = 192, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 199, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 186, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 203, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 180, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 166, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 205, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 207, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 114, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 166, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 189, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 161, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 255, .box_w = 15, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 207, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 200, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 738, .adv_w = 176, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 756, .adv_w = 200, .box_w = 11, .box_h = 16, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 778, .adv_w = 195, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 798, .adv_w = 190, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 818, .adv_w = 160, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 202, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 857, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 262, .box_w = 16, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 905, .adv_w = 182, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 182, .box_w = 10, .box_h = 14, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 946, .adv_w = 191, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 967, .adv_w = 100, .box_w = 7, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 984, .adv_w = 123, .box_w = 4, .box_h = 16, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 992, .adv_w = 100, .box_w = 7, .box_h = 19, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1009, .adv_w = 169, .box_w = 8, .box_h = 4, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 1013, .adv_w = 156, .box_w = 9, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1015, .adv_w = 73, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 15},
    {.bitmap_index = 1017, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1029, .adv_w = 178, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1047, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1057, .adv_w = 178, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1075, .adv_w = 168, .box_w = 9, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1087, .adv_w = 88, .box_w = 6, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1098, .adv_w = 178, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1116, .adv_w = 180, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1134, .adv_w = 72, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1141, .adv_w = 76, .box_w = 6, .box_h = 17, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 1154, .adv_w = 156, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1172, .adv_w = 72, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1179, .adv_w = 291, .box_w = 17, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1201, .adv_w = 183, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1214, .adv_w = 172, .box_w = 9, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1226, .adv_w = 178, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1244, .adv_w = 178, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 1260, .adv_w = 117, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1270, .adv_w = 159, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1282, .adv_w = 96, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1291, .adv_w = 179, .box_w = 9, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1303, .adv_w = 167, .box_w = 10, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1316, .adv_w = 241, .box_w = 15, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1335, .adv_w = 161, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1349, .adv_w = 163, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 1367, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1379, .adv_w = 125, .box_w = 8, .box_h = 19, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 1398, .adv_w = 75, .box_w = 5, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1410, .adv_w = 125, .box_w = 7, .box_h = 19, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1427, .adv_w = 169, .box_w = 9, .box_h = 3, .ofs_x = 2, .ofs_y = 6}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 2, 0, 3, 0, 0,
    4, 5, 0, 0, 0, 0, 0, 0,
    0, 0, 6, 7, 8, 9, 10, 11,
    12, 13, 13, 0, 14, 15, 0, 13,
    16, 17, 16, 18, 19, 20, 0, 21,
    22, 23, 24, 25, 0, 0, 0, 0,
    0, 0, 26, 27, 28, 0, 29, 30,
    31, 26, 32, 33, 34, 0, 26, 26,
    27, 27, 35, 36, 27, 37, 38, 39,
    40, 41, 42, 43, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 2, 3, 4, 0, 0,
    5, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 6, 7, 8, 7, 0, 0,
    8, 7, 7, 9, 7, 7, 0, 7,
    8, 7, 8, 7, 10, 11, 0, 12,
    13, 14, 15, 16, 0, 0, 0, 0,
    0, 0, 17, 0, 18, 18, 18, 19,
    18, 20, 0, 21, 0, 20, 22, 22,
    18, 22, 18, 22, 18, 23, 24, 25,
    26, 27, 28, 29, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 10, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -19, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -22,
    -6, -7, -19, 4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, -6, -22, -19, -9, 8, -20,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, -11, -3, 0, -11, 0, 0, 0,
    0, 0, 0, -2, 0, -2, 0, -6,
    -5, -7, -10, -8, -12, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, -6, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, -3, -3, -4, -4, -10, -10, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, -4, -2, 0,
    0, 0, 0, 0, -1, -6, -3, 0,
    -6, 0, 0, 0, 0, 0, 0, -18,
    0, 0, -30, 0, 0, 0, 0, 0,
    0, -10, -25, -16, 0, 0, 0, -6,
    0, -13, -3, 0, 0, -3, -13, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -10,
    -6, 0, -10, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, -6, 0, -8,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, -6, 0, 0, 0, 0, 0,
    0, -8, -5, 0, 0, 0, 0, 0,
    0, -27, -22, 0, -27, 0, 0, 0,
    0, 0, 0, 6, 0, 0, 0, 0,
    -33, -32, -19, 3, -37, 0, 0, -5,
    0, 0, 0, 0, 0, -3, -19, -10,
    0, -19, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, -4, -3, 0, -1, -2,
    -2, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -18, 0, 0,
    -19, 0, 0, 0, 0, 0, 0, -13,
    -16, -3, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, -11, -3, -6,
    -3, 0, 0, -3, -6, -6, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, -6, -6, -3, -3,
    -6, -10, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, 0, -6, 0, 0,
    0, 0, 0, 0, -22, 0, 0, -32,
    -6, 3, 5, 3, 5, 5, -22, -32,
    -29, 0, 0, 0, -22, 0, -25, -19,
    -19, -16, -19, -19, 0, 0, 0, 0,
    0, -14, 0, -1, -19, -6, 5, 0,
    0, 3, 3, -13, -19, -16, 0, 0,
    0, -11, 0, -16, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, -6, -3,
    -2, -19, -3, 3, 0, 0, 0, 0,
    -10, -10, -10, 0, 0, 0, -2, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 8, 0, -2, -3, -3,
    5, 3, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -16, 0, -6, -38, -6, 5, 3, 0,
    0, 0, -13, -25, -19, 0, 0, 0,
    -16, 0, -19, -10, -6, -3, -10, -6,
    0, 0, 0, 0, 0, -6, 0, 0,
    -3, -13, -16, -10, -10, -6, -13, 0,
    -16, -19, -16, 0, 0, -13, 0, -19,
    -16, -14, -3, -16, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -22,
    -13, -5, 0, -18, -10, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -29, -16, -10, 0,
    -19, -13, 0, -1, 0, 0, 0, 0,
    0, 0, -7, -5, -3, -7, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -29, -16, -10, 0, -16, -13, -7,
    0, 0, 0, 0, 0, 0, 0, -5,
    -3, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, -29, -16,
    -10, 0, -16, -13, -7, 0, 0, 0,
    0, 0, 0, 0, -4, -3, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 0, 10, 6, 10, 0, 6,
    0, -6, 0, 0, 6, 0, 0, 0,
    0, 6, 0, 0, 6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -19, -11, -2, 0, -19, -10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -13,
    0, 0, 0, -11, 0, -6, -3, 0,
    0, 0, 0, 0, 0, -2, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -11, -2, 0,
    -16, 0, 0, 0, 0, 0, 8, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -10, 0, 0, -13,
    0, -13, 0, 0, 0, 0, -25, -6,
    -3, 6, 0, 0, 0, 6, 0, 6,
    6, 0, 6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -22, -11, -2, 0, -16,
    -10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -11, -8, 0, -6, -3,
    -19, 0, 0, 0, -10, -19, -5, -7,
    3, 0, 0, 0, 3, -2, 0, 2,
    0, 0, -2, 0, 0, 0, 0, 0,
    -3, -6, 0, -3, 0, -16, 0, 0,
    0, -6, -11, -10, -3, 0, 0, 0,
    0, 0, -2, 2, 2, 0, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -16, 0, 0, 0, -3, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, -11, -8, 0, -6, -3, -19,
    0, 0, 0, -10, -19, -10, -7, 3,
    0, 0, 0, 3, 0, 0, 2, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -19, -3, 0, 0,
    -6, 0, -6, -3, 0, 0, 0, 0,
    0, 0, -6, 0, 0, -6, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 43,
    .right_class_cnt     = 29,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_tomorrow18 = {
#else
lv_font_t ui_font_tomorrow18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 22,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_TOMORROW18*/

