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
// eeProm.h
#ifndef EEPROM_H
#define EEPROM_H

#include "caddy.h"

//Locations in EEPROM
#define EE_ADDR_LEFT_BASE           0x50
#define EE_ADDR_RIGHT_BASE          0x51
#define EE_ADDR_SLOPE_COEF          0x52 //u16
#define EE_ADDR_OFF_COEF            0x54 //u16
#define EE_ADDR_DAMP_COEF           0x56
#define EE_ADDR_LINE_X_CENTER       0x57
#define EE_ADDR_TURN_POINT          0x58
#define EE_ADDR_TURN_SUBTRACT       0x59
#define EE_ADDR_PAN_OFFSET          0x5A
#define EE_ADDR_TILT_OFFSET         0x5B
#define EE_ADDR_TRACTOR_OVERSHOOT_DELAY 0x5C //u16
#define EE_ADDR_TEST_MODE           0x5E
#define EE_ADDR_TEMP_TWEAK1         0x5F
#define EE_ADDR_TEMP_TWEAK2         0x60
#define EE_ADDR_TEMP_TWEAK3         0x61 //u16
#define EE_ADDR_TEMP_TWEAK4         0x63 //u16
//next address 0x65

/*
// Current values - Bigger motors at 6 Volts
#define INIT_LEFT_BASE_SPEED        0xF7
#define INIT_RIGHT_BASE_SPEED       0xF0
#define INIT_SLOPE_COEF             0x0110   // <--- 0x110 could be tweaked
#define INIT_OFF_COEF               0x0001
#define INIT_DAMP_COEF              0x01     // <--- 0x01 could be tweaked
#define INIT_LINE_X_CENTER          0x25
#define INIT_TURN_POINT             0x15     // Turn values
#define INIT_TURN_SUBTRACT          0x0A
pan offset 0x05
tilt offset 0xE7

#define TRACTOR_OVERSHOOT_DELAY     5000
*/

#define BASE_MIN                    0x60     // <--- also worked at 0xB0
#define BASE_MAX                    0xFF

// Pickup values
#define BALL_CHECK_RATIO            16
#define PICK_UP_POINT               0x16


/*
// Old values - 6V Solarbotics before damping fix
#define LEFT_BASE_SPEED           0x8C
#define RIGHT_BASE_SPEED          0xC2
#define BASE_MIN                  100
#define BASE_MAX                  255
#define OFF_COEF                  0x2
#define SLOPE_COEF                0x100
#define DAMP_COEF                 0x14
*/

u08 l_base;
u08 r_base;
u16 slopeCoef;
u16 offCoef;
u08 dampCoef;
u08 lineCenter;
u08 turnPoint;
u08 turnSubtract;
s08 panOffset;
s08 tiltOffset;
u16 tractorOvershootDelay;
u08 tempTweak1;
s08 tempTweak2;
u16 tempTweak3;
u16 tempTweak4;



u08 lcdMode;  // <- need debugger menu for this, remove old init/toggling, and save in eeProm
u08 testMode; // <- need to save this in eeProm

inline void loadTweakValues( void );
inline void storeTweakValues( void );
u08 EEPROM_read(unsigned int uiAddress);
void EEPROM_write(unsigned int uiAddress, u08 ucData);
#endif  // #ifndef
