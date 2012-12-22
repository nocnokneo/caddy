// debugger.h
#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "caddy.h"

//#define ENABLE_INT0    outb( GICR, BV(INT0) )
//#define DISABLE_INT0   outb( GICR, 0 )


#define WELCOME             0     // Must have WELCOME mode and must be 0
#define BASE_SPEED_TWEAK    1
#define LINE_TRACK_TWEAK    2
#define DAMP_TWEAK          3
#define TURN_TWEAK          4
#define PAN_TILT_TWEAK      5
#define TRACTOR_OVERSHOOT_DELAY_TWEAK 6
#define u08_TEMP_TWEAK      7
#define u16_TEMP_TWEAK      8
#define TEST_MODE_TWEAK     9

#define NUM_TWEAK_MODES     10


#define NAV_LCD_MODE        0
#define LINE_LCD_MODE       1


#define DELTA_SLOPE_COEF    8


#define turnOnRemoteLight()   sbi(PORTD, 7)
#define turnOffRemoteLight()  cbi(PORTD, 7)


//#define ENABLE_INT0    outb( GICR, BV(INT0) )
//#define DISABLE_INT0   outb( GICR, 0 )
//volatile BOOL userWantsToStop;


u08 tweakMode;

void runDebugger(void);
void updateTweaks(void);
void printValues(void);
void toggleTweakMode( s08 i );


#endif  // #ifndef
