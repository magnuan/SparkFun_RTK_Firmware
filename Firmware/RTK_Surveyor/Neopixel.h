#pragma once

typedef enum
{
    led_black = 0,
    led_red,
    led_green,
    led_blue,
    led_yellow,
    led_magenta,
    led_cyan,
    led_white
} NeopixelColor;

void beginNeopixel();
void neopixelSetColor(NeopixelColor new_color);

