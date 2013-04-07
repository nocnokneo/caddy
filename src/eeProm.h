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
/**
 * @file
 * @brief Interface to the "tweak values" stored in EEPROM
 *
 * Tweak values are runtime configurable parameters that can be adjusted e.g.
 * with the tether UI and saved persistently in EEPROM.
 */
#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>

//Locations in EEPROM
#define EE_ADDR_LEFT_BASE           0x50
#define EE_ADDR_RIGHT_BASE          0x51
#define EE_ADDR_SLOPE_COEF          0x52 //uint16_t
#define EE_ADDR_OFF_COEF            0x54 //uint16_t
#define EE_ADDR_DAMP_COEF           0x56
#define EE_ADDR_LINE_X_CENTER       0x57
#define EE_ADDR_TURN_POINT          0x58
#define EE_ADDR_TURN_SUBTRACT       0x59
#define EE_ADDR_PAN_OFFSET          0x5A
#define EE_ADDR_TILT_OFFSET         0x5B
#define EE_ADDR_TRACTOR_OVERSHOOT_DELAY 0x5C //uint16_t
#define EE_ADDR_TEST_MODE           0x5E
#define EE_ADDR_TEMP_TWEAK1         0x5F
#define EE_ADDR_TEMP_TWEAK2         0x60
#define EE_ADDR_TEMP_TWEAK3         0x61 //uint16_t
#define EE_ADDR_TEMP_TWEAK4         0x63 //uint16_t
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

// Global variables - Runtime configurable parameters
extern uint8_t l_base;
extern uint8_t r_base;
extern uint16_t slopeCoef;
extern uint16_t offCoef;
extern uint8_t dampCoef;
extern uint8_t lineCenter;
extern uint8_t turnPoint;
extern uint8_t turnSubtract;
extern int8_t panOffset;
extern int8_t tiltOffset;
extern uint16_t tractorOvershootDelay;
extern uint8_t tempTweak1;
extern int8_t tempTweak2;
extern uint16_t tempTweak3;
extern uint16_t tempTweak4;

extern uint8_t lcdMode;
extern uint8_t testMode;

inline void loadTweakValues( void );
inline void storeTweakValues( void );
uint8_t EEPROM_read(unsigned int uiAddress);
void EEPROM_write(unsigned int uiAddress, uint8_t ucData);

#endif // #ifndef EEPROM_H_
