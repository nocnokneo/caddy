#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>

#include "global.h"
#include "ourLcd.h"

#define SIMULATING FALSE



#define DEBOUNCE_COUNT   3   // should be equal to 2 or greater
#define START_DELAY      3

#define RED_BUTTON       0
#define MODE_BUTTON      1
#define L_UP_BUTTON      2
#define L_DOWN_BUTTON    3
#define R_UP_BUTTON      4
#define R_DOWN_BUTTON    5

#define NUM_BUTTONS      6

#define RED_BUTTON_DOWN       FALSE
//#define RED_BUTTON_DOWN       (R_UP_BUTTON_DOWN && R_DOWN_BUTTON_DOWN)
#define MODE_BUTTON_DOWN      bit_is_clear(PIND,2)
#define L_UP_BUTTON_DOWN      bit_is_clear(PINA,0)
#define L_DOWN_BUTTON_DOWN    bit_is_clear(PINA,1)
#define R_UP_BUTTON_DOWN      bit_is_clear(PINA,2)
#define R_DOWN_BUTTON_DOWN    bit_is_clear(PINA,3)

#define BOTH_RIGHT_BUTTONS_PRESSED   ( (justPressed(R_UP_BUTTON) && justPressed(R_DOWN_BUTTON)) || (justPressed(R_UP_BUTTON) && isDown[R_DOWN_BUTTON]) || (justPressed(R_DOWN_BUTTON) && isDown[R_UP_BUTTON]) )

#define ENABLE_INT0    outb( GICR, BV(INT0) )
#define DISABLE_INT0   outb( GICR, 0 )

#define WELCOME             0
#define BASE_SPEED_TWEAK    1
#define LINE_TRACK_TWEAK    2
#define PAN_TILT_TWEAK      3

#define NUM_TWEAK_MODES     4

#define L_BASE_START        140
#define R_BASE_START        140
#define BASE_TWEAK          1

BOOL resetFlag;

BOOL isDown[NUM_BUTTONS];
BOOL wasEvent[NUM_BUTTONS];
u08 upCount[NUM_BUTTONS];
u08 downCount[NUM_BUTTONS];

u08 tweakMode;

u08 l_base;
u08 r_base;

volatile BOOL userWantsToStop;

void loadTweakValues(void);   // eventually use EEPROM
void storeTweakValues(void);


void initButtons(void);
void tweakValues(void);
void debounceButtons(void);
void updateTweaks(void);
void printValues(void);
BOOL justPressed(u08 button);
BOOL justReleased(u08 button);
BOOL isPressed(u08 button);
void toggleTweakMode(void);

void turnOnRemoteLight(void);
void turnOffRemoteLight(void);

void myDelay(u16 outerDelay);
void init(void);
void printPortA(void);

void enableINT0(void);

BOOL timeToStartBot(void);
