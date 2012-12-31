/*
 * This file is part of Caddy.
 *
 *  Caddy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Caddy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Caddy.  If not, see <http://www.gnu.org/licenses/>.
 */
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
#define DELTA_TEMP_2        2


#define turnOnRemoteLight()   sbi(PORTD, 7)
#define turnOffRemoteLight()  cbi(PORTD, 7)


//#define ENABLE_INT0    outb( GICR, BV(INT0) )
//#define DISABLE_INT0   outb( GICR, 0 )
//volatile BOOL userWantsToStop;


u08 tweakMode;

inline void runDebugger(void);
inline void updateTweaks(void);
inline void printValues(void);
inline void toggleTweakMode( u08 i );


#endif  // #ifndef
