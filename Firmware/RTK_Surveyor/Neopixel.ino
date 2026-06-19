#ifdef USE_NEOPIXEL
#define NEOPIXEL_PIN 0 

#include "Neopixel.h" 
#include <Adafruit_NeoPixel.h>

//----------------------------------------
// Locals
//----------------------------------------
Adafruit_NeoPixel onePixel; 


//----------------------------------------
// Routines
//----------------------------------------

void beginNeopixel()
{
    onePixel = Adafruit_NeoPixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
    onePixel.begin();             // Start the NeoPixel object
    onePixel.clear();             // Set NeoPixel color to black (0,0,0)
    onePixel.setBrightness(10);   // Affects all subsequent settings
                                  //onePixel.setPixelColor(0, 255, 255, 255);   //  Set pixel 0 to (r,g,b) color value
    onePixel.show();              // Update the pixel state
    neopixelSetColor(led_green);
}

void updateNeopixel()
{
    uint8_t ntripClientState = ntripClientStateGet();
    /*
    switch (ntripClientState)
    {
        default:
            break;
        case NTRIP_CLIENT_OFF:
            break;
        case NTRIP_CLIENT_ON:
        case NTRIP_CLIENT_NETWORK_STARTED:
        case NTRIP_CLIENT_NETWORK_CONNECTED:
        case NTRIP_CLIENT_CONNECTING:
        case NTRIP_CLIENT_WAIT_RESPONSE:
            break;
        case NTRIP_CLIENT_CONNECTED:
            break;
    }*/
    if (online.gnss == true)
    {
        switch(carrSoln){
            case 0: //No RTK
                if (ntripClientState==0)
                    neopixelSetColor(led_red);
                else if (ntripClientState==6)
                    neopixelSetColor(led_green);
                else
                    neopixelSetColor(led_yellow);
                break;
            case 1: //RTK Float
                neopixelSetColor(led_cyan);
                break;
            case 2: //RTK Fixed
                neopixelSetColor(led_blue);
                break;
            default:
                neopixelSetColor(led_black);
                break;
        }
    }
    else{
        neopixelSetColor(led_black);
    }
}

void neopixelSetColor(NeopixelColor new_color){
    static NeopixelColor current_color = led_black;
    if (current_color != new_color){
        switch(new_color){
            case led_black:
                onePixel.setPixelColor(0,  0, 0, 0);   //  Set pixel 0 to (r,g,b) color value
                break;
            case led_red:
                onePixel.setPixelColor(0, 255, 0, 0);   //  Set pixel 0 to (r,g,b) color value
                break;
            case led_green:
                onePixel.setPixelColor(0,   0, 255, 0);   //  Set pixel 0 to (r,g,b) color value
                break;
            case led_blue:
                onePixel.setPixelColor(0,   0, 0, 255);   //  Set pixel 0 to (r,g,b) color value
                break;
            case led_yellow:
                onePixel.setPixelColor(0, 128, 64, 0);   //  Set pixel 0 to (r,g,b) color value
                break;
            case led_magenta:
                onePixel.setPixelColor(0,   128, 0, 128);   //  Set pixel 0 to (r,g,b) color value
                break;
            case led_cyan:
                onePixel.setPixelColor(0,   0, 128, 128);   //  Set pixel 0 to (r,g,b) color value
                break;
            case led_white:
                onePixel.setPixelColor(0,   128, 128, 128);   //  Set pixel 0 to (r,g,b) color value
                break;
        }
        onePixel.show();              // Update the pixel state
        current_color = new_color;
    }
}
#endif
