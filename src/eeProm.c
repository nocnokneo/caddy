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
/* eeProm.c
 *
 *    For loading and storing tweak values into eeProm.
 *
 */

#include "eeProm.h"

// Global variables - Runtime configurable parameters
uint8_t l_base;
uint8_t r_base;
uint16_t slopeCoef;
uint16_t offCoef;
uint8_t dampCoef;
uint8_t lineCenter;
uint8_t turnPoint;
uint8_t turnSubtract;
int8_t panOffset;
int8_t tiltOffset;
uint16_t tractorOvershootDelay;
uint8_t tempTweak1;
int8_t tempTweak2;
uint16_t tempTweak3;
uint16_t tempTweak4;

uint8_t lcdMode;  // <- need debugger menu for this, remove old init/toggling, and save in eeProm
uint8_t testMode; // <- need to save this in eeProm

// Initializes constants that can be tweaked by debugger
inline void loadTweakValues(void)
{
    cli(); // disable all interrupts

    // EEPROM Reads
    l_base                = EEPROM_read(EE_ADDR_LEFT_BASE);
    r_base                = EEPROM_read(EE_ADDR_RIGHT_BASE);
    slopeCoef             = (EEPROM_read(EE_ADDR_SLOPE_COEF) << 8) +
                             EEPROM_read(EE_ADDR_SLOPE_COEF + 1);
    offCoef               = (EEPROM_read(EE_ADDR_OFF_COEF) << 8) +
                             EEPROM_read(EE_ADDR_OFF_COEF + 1);
    dampCoef              = EEPROM_read(EE_ADDR_DAMP_COEF);
    lineCenter            = EEPROM_read(EE_ADDR_LINE_X_CENTER);
    turnPoint             = EEPROM_read(EE_ADDR_TURN_POINT);
    turnSubtract          = EEPROM_read(EE_ADDR_TURN_SUBTRACT);
    panOffset             = EEPROM_read(EE_ADDR_PAN_OFFSET);
    tiltOffset            = EEPROM_read(EE_ADDR_TILT_OFFSET);
    tractorOvershootDelay = (EEPROM_read(EE_ADDR_TRACTOR_OVERSHOOT_DELAY) << 8) +
                             EEPROM_read(EE_ADDR_TRACTOR_OVERSHOOT_DELAY + 1);
    testMode              = EEPROM_read(EE_ADDR_TEST_MODE);
    tempTweak1            = EEPROM_read(EE_ADDR_TEMP_TWEAK1);
    tempTweak2            = EEPROM_read(EE_ADDR_TEMP_TWEAK2);
    tempTweak3            = (EEPROM_read(EE_ADDR_TEMP_TWEAK3) << 8) +
                             EEPROM_read(EE_ADDR_TEMP_TWEAK3 + 1);
    tempTweak4            = (EEPROM_read(EE_ADDR_TEMP_TWEAK4) << 8) +
                             EEPROM_read(EE_ADDR_TEMP_TWEAK4 + 1);

    sei(); // enable all interrupts
}

// Saves constants after they have been changed by the debugger
inline void storeTweakValues(void)
{
    cli(); // disable all interrupts

    // EEPROM writes
    EEPROM_write(EE_ADDR_LEFT_BASE, l_base);
    EEPROM_write(EE_ADDR_RIGHT_BASE, r_base);
    EEPROM_write(EE_ADDR_SLOPE_COEF, slopeCoef >> 8);
    EEPROM_write(EE_ADDR_SLOPE_COEF + 1, slopeCoef);
    EEPROM_write(EE_ADDR_OFF_COEF, offCoef >> 8);
    EEPROM_write(EE_ADDR_OFF_COEF + 1, offCoef);
    EEPROM_write(EE_ADDR_DAMP_COEF, dampCoef);
    EEPROM_write(EE_ADDR_LINE_X_CENTER, lineCenter);
    EEPROM_write(EE_ADDR_TURN_POINT, turnPoint);
    EEPROM_write(EE_ADDR_TURN_SUBTRACT, turnSubtract);
    EEPROM_write(EE_ADDR_PAN_OFFSET, panOffset);
    EEPROM_write(EE_ADDR_TILT_OFFSET, tiltOffset);
    EEPROM_write(EE_ADDR_TRACTOR_OVERSHOOT_DELAY, tractorOvershootDelay >> 8);
    EEPROM_write(EE_ADDR_TRACTOR_OVERSHOOT_DELAY + 1, tractorOvershootDelay);
    EEPROM_write(EE_ADDR_TEST_MODE, testMode);
    EEPROM_write(EE_ADDR_TEMP_TWEAK1, tempTweak1);
    EEPROM_write(EE_ADDR_TEMP_TWEAK2, tempTweak2);
    EEPROM_write(EE_ADDR_TEMP_TWEAK3, tempTweak3 >> 8);
    EEPROM_write(EE_ADDR_TEMP_TWEAK3 + 1, tempTweak3);
    EEPROM_write(EE_ADDR_TEMP_TWEAK4, tempTweak4 >> 8);
    EEPROM_write(EE_ADDR_TEMP_TWEAK4 + 1, tempTweak4);

    sei(); // enable all interrupts
}

uint8_t EEPROM_read(unsigned int uiAddress)
{
    // Wait for completion of previous write
    while (EECR & (1 << EEWE)) ;
    // Set up address register
    EEAR = uiAddress;
    // Start eeprom read by writing EERE
    EECR |= (1 << EERE);
    // Return data from data register
    return EEDR;
}

void EEPROM_write(unsigned int uiAddress, uint8_t ucData)
{
    // Wait for completion of previous write
    while (EECR & (1 << EEWE)) ;
    // Set up address and data registers
    EEAR = uiAddress;
    EEDR = ucData;
    // Write logical one to EEMWE
    EECR |= (1 << EEMWE);
    // Start eeprom write by setting EEWE
    EECR |= (1 << EEWE);
    // EEMWE and EEWE are automatically cleared back to 0 by hardware
}
