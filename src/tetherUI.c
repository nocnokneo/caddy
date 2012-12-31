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
#include "tetherUI.h"
#include "buttons.h"
#include <avr/io.h>
#include <stdint.h>

#define WELCOME                       0 // Must be 0
#define BASE_SPEED_TWEAK              1
#define LINE_TRACK_TWEAK              2
#define DAMP_TWEAK                    3
#define TURN_TWEAK                    4
#define PAN_TILT_TWEAK                5
#define TRACTOR_OVERSHOOT_DELAY_TWEAK 6
#define u08_TEMP_TWEAK                7
#define u16_TEMP_TWEAK                8
#define TEST_MODE_TWEAK               9

#define NUM_TWEAK_MODES     10

#define DELTA_SLOPE_COEF    8
#define DELTA_TEMP_2        2

static uint8_t tweakMode;

#define turnOnRemoteLight()   sbi(PORTD, 7)
#define turnOffRemoteLight()  cbi(PORTD, 7)

static inline void updateTweaks(void);
static inline void printValues(void);
static inline void toggleTweakMode(uint8_t modeIncrement);

inline void runTetherUI(void)
{
    turnOnRemoteLight();

    tweakMode = WELCOME;
#if DEBUGGING
    lcdWriteStr("Welcome, T-mode:", 0, 0);
    toggleTestMode(0);
#endif

    lcdMode = NAV_LCD_MODE;

    while (!justReleased(RED_BUTTON))
    {
        debounceButtons();
        updateTweaks();
        printValues();

        if (BOTH_RIGHT_BUTTONS_PRESSED)
        {
            toggleTweakMode(1);
        }
        if (BOTH_LEFT_BUTTONS_PRESSED)
        {
            toggleTweakMode(-1);
        }
    }

    turnOffRemoteLight();

    // save new tweak values, entered a tweak mode
    if (tweakMode != WELCOME)
    {
        storeTweakValues();
    }
}

/**
 * @brief Modify global variable parameters based on last button pressed
 */
inline void updateTweaks(void)
{
    switch (tweakMode)
    {
    case BASE_SPEED_TWEAK:
        if (justReleased(L_UP_BUTTON))
            l_base++;
        if (justReleased(L_DOWN_BUTTON))
            l_base--;
        if (justReleased(R_UP_BUTTON))
            r_base++;
        if (justReleased(R_DOWN_BUTTON))
            r_base--;
        break;

    case LINE_TRACK_TWEAK:
        if (justReleased(L_UP_BUTTON))
            slopeCoef += DELTA_SLOPE_COEF;
        if (justReleased(L_DOWN_BUTTON))
            slopeCoef -= DELTA_SLOPE_COEF;
        if (justReleased(R_UP_BUTTON))
            offCoef++;
        if (justReleased(R_DOWN_BUTTON))
            offCoef--;
        break;

    case DAMP_TWEAK:
        if (justReleased(L_UP_BUTTON))
            dampCoef++;
        if (justReleased(L_DOWN_BUTTON))
            dampCoef--;
        if (justReleased(R_UP_BUTTON))
            lineCenter++;
        if (justReleased(R_DOWN_BUTTON))
            lineCenter--;
        break;

    case TURN_TWEAK:
        if (justReleased(L_UP_BUTTON))
            turnPoint++;
        if (justReleased(L_DOWN_BUTTON))
            turnPoint--;
        if (justReleased(R_UP_BUTTON))
            turnSubtract++;
        if (justReleased(R_DOWN_BUTTON))
            turnSubtract--;
        break;

    case PAN_TILT_TWEAK:
        if (justReleased(L_UP_BUTTON))
            panOffset++;
        if (justReleased(L_DOWN_BUTTON))
            panOffset--;
        if (justReleased(R_UP_BUTTON))
            tiltOffset++;
        if (justReleased(R_DOWN_BUTTON))
            tiltOffset--;
        break;

    case TRACTOR_OVERSHOOT_DELAY_TWEAK:
        if (justReleased(L_UP_BUTTON))
            tractorOvershootDelay += 50;
        if (justReleased(L_DOWN_BUTTON))
            tractorOvershootDelay -= 50;
        break;

    case u08_TEMP_TWEAK:
        if (justReleased(L_UP_BUTTON))
            tempTweak1++;
        if (justReleased(L_DOWN_BUTTON))
            tempTweak1--;
        if (justReleased(R_UP_BUTTON))
            tempTweak2 += DELTA_TEMP_2;
        if (justReleased(R_DOWN_BUTTON))
            tempTweak2 -= DELTA_TEMP_2;
        break;

    case u16_TEMP_TWEAK:
        if (justReleased(L_UP_BUTTON))
            tempTweak3++;
        if (justReleased(L_DOWN_BUTTON))
            tempTweak3--;
        if (justReleased(R_UP_BUTTON))
            tempTweak4++;
        if (justReleased(R_DOWN_BUTTON))
            tempTweak4--;
        break;

    case TEST_MODE_TWEAK:
        if (justReleased(L_UP_BUTTON) || justReleased(R_UP_BUTTON))
            toggleTestMode(1);
        if (justReleased(L_DOWN_BUTTON) || justReleased(R_DOWN_BUTTON))
            toggleTestMode(-1);
        break;
    }
}

/**
 * @brief Print the tweak parameters for the current tweak mode
 */
inline void printValues(void)
{
    switch (tweakMode)
    {
    case BASE_SPEED_TWEAK:
        lcdPrintHex(l_base, 1, 5);
        lcdPrintHex(r_base, 1, 14);
        break;
    case LINE_TRACK_TWEAK:
        lcdPrintHex(slopeCoef >> 8, 1, 3);
        lcdPrintHex(slopeCoef, 1, 5);
        lcdPrintHex(offCoef >> 8, 1, 11);
        lcdPrintHex(offCoef, 1, 13);
        break;
    case DAMP_TWEAK:
        lcdPrintHex(dampCoef, 1, 5);
        lcdPrintHex(lineCenter, 1, 13);
        break;
    case TURN_TWEAK:
        lcdPrintHex(turnPoint, 1, 3);
        lcdPrintHex(turnSubtract, 1, 12);
        break;
    case PAN_TILT_TWEAK:
        lcdPrintHex(panOffset, 1, 5);
        lcdPrintHex(tiltOffset, 1, 13);
        break;
    case TRACTOR_OVERSHOOT_DELAY_TWEAK:
        lcdPrintHex(tractorOvershootDelay >> 8, 1, 4);
        lcdPrintHex(tractorOvershootDelay, 1, 6);
        break;
    case u08_TEMP_TWEAK:
        lcdPrintHex(tempTweak1, 1, 3);
        lcdPrintHex(tempTweak2, 1, 12);
        break;
    case u16_TEMP_TWEAK:
        lcdPrintHex(tempTweak3 >> 8, 1, 3);
        lcdPrintHex(tempTweak3, 1, 5);
        lcdPrintHex(tempTweak4 >> 8, 1, 11);
        lcdPrintHex(tempTweak4, 1, 13);
        break;
    }
}

/**
 * @brief Cycle through tweak modes (except 'Welcome' mode)
 */
inline void toggleTweakMode(uint8_t modeIncrement)
{
    // advance tweak mode (skipping welcome mode)
    tweakMode += modeIncrement;
    if (tweakMode == NUM_TWEAK_MODES)
    {
        tweakMode = 1;
    }
    else if (tweakMode == 0 || tweakMode == 255)
    {
        tweakMode = NUM_TWEAK_MODES - 1;
    }

    // clear LCD and print labels for new tweak mode
    switch (tweakMode)
    {
    case BASE_SPEED_TWEAK:
        lcdWriteStr("Base speed tweak", 0, 0);
        lcdWriteStr("Left:   Right:  ", 1, 0);
        break;
    case LINE_TRACK_TWEAK:
        lcdWriteStr("Slp & Offst Cnst", 0, 0);
        lcdWriteStr("sc:     oc:     ", 1, 0);
        break;
    case DAMP_TWEAK:
        lcdWriteStr("Damping & Center", 0, 0);
        lcdWriteStr("damp:   cntr:   ", 1, 0);
        break;
    case TURN_TWEAK:
        lcdWriteStr("Turn tweak      ", 0, 0);
        lcdWriteStr("pt:    subt:    ", 1, 0);
        break;
    case PAN_TILT_TWEAK:
        lcdWriteStr("Pan,Tilt Offsets", 0, 0);
        lcdWriteStr("Pan:    tilt:   ", 1, 0);
        break;
    case TRACTOR_OVERSHOOT_DELAY_TWEAK:
        lcdWriteStr("Tractor Os Delay", 0, 0);
        lcdWriteStr("dly:            ", 1, 0);
        break;
    case u08_TEMP_TWEAK:
        lcdWriteStr("uint8_t Temp Tweaks ", 0, 0);
        lcdWriteStr("T1:     T2:     ", 1, 0);
        break;
    case u16_TEMP_TWEAK:
        lcdWriteStr("u16 Temp Tweaks ", 0, 0);
        lcdWriteStr("T3:     T4:     ", 1, 0);
        break;
    case TEST_MODE_TWEAK:
        lcdWriteStr("Test mode tweak ", 0, 0);
        toggleTestMode(0);
        break;
    }
}
