#include <Adafruit_CCS811.h>
#include <FastLED.h>
#include <TroykaMeteoSensor.h>
#include "fonts.h"


#define BRIGHTNESS 40
#define CURRENT_LIMIT 2000


// LED matrix geometry {{{

#define WIDTH 16
#define HEIGHT 16
#define MATRIX_TYPE 0         // 0 - zigzag, 1 - parallel
#define CONNECTION_ANGLE 3    // connection point: 0 - left bottom, 1 - left top, 2 - right top, 3 - right bottom
#define STRIP_DIRECTION 1     // direction: 0 - right, 1 - up, 2 - left, 3 - down

#define NUM_LEDS WIDTH * HEIGHT
#define SEGMENTS 1            // num of diods in one pixel

#define COLOR_ORDER BGR  // good flame, red matrix
//#define COLOR_ORDER BRG  // blue flame, blue matrix
//#define COLOR_ORDER RGB  // pinky flame, blue-green ocean, red matrix
//#define COLOR_ORDER RBG  // blue flame and matrix, red-green ocean
//#define COLOR_ORDER GRB  // green flame and matrix, pinky ocean
//#define COLOR_ORDER GBR  // green matrix and flame, red-blue ocean

// }}}


// PINS {{{

#define LED_PIN 5
#define BUTTON_MODE_PIN 3
#define BUTTON_NEXT_PIN 4
#define BUTTON_PREV_PIN 2
#define MODE_AMOUNT 8

// }}}


// TUNES FOR FASTLED {{{

// probably can be deleted
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ALLOW_INTERRUPTS 0

// }}}


Adafruit_CCS811 ccs;
CRGB leds[NUM_LEDS];
TroykaMeteoSensor meteoSensor;


// VARS {{{

// struct defines effect params
struct {
  byte brightness = 10;
  byte speed = 30;  // 30 is good for flame
  byte scale = 40;  // 40 is ok 100 makes flame blue, 10 makes pinky
} modes[MODE_AMOUNT];

// struct defines climate info with corresponding color
struct Text {
    CRGB color;
    String text;
};

boolean loadingFlag = true;  // flag of initial state, used by effects to set some init params

int8_t global_mode = 0;          // 0 - effects, 1 - climate info
int8_t currentMode = 0;          // initial effect
int8_t brightness = BRIGHTNESS;  // initial brightness

unsigned char matrixValue[8][16];

// }}}


void setup() {

    FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
  
    if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    FastLED.show();
  
    memset(matrixValue, 0, sizeof(matrixValue));
  
    randomSeed(micros());
  
    // init buttons
    pinMode(BUTTON_MODE_PIN, INPUT_PULLUP);
    pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_PREV_PIN, INPUT_PULLUP);
  
    ccs.begin();
    meteoSensor.begin();

}


void loop() {

    // check buttons and change states accordingly
    buttonsTick();
 
    // run something according to mode state
    if (global_mode == 0) {
        effectsTick();
    } else {
        climateTick();
    }

}
