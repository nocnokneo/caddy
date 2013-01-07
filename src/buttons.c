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
/** @file */
#include "buttons.h"

// AVRLIB
#include "avrlibdefs.h"

// avr-libc
#include <stdint.h>
#include <stdbool.h>

#define DEBOUNCE_COUNT   3   // should be equal to 2 or greater

static bool isDown[NUM_BUTTONS]   = { false, false, false,
                                      false, false, false };
static bool wasEvent[NUM_BUTTONS] = { false, false, false,
                                      false, false, false };
static uint8_t upCount[NUM_BUTTONS] = { DEBOUNCE_COUNT, DEBOUNCE_COUNT,
                                        DEBOUNCE_COUNT, DEBOUNCE_COUNT,
                                        DEBOUNCE_COUNT, DEBOUNCE_COUNT };
static uint8_t downCount[NUM_BUTTONS] = { 0, 0, 0, 0, 0, 0 };

void waitFor(uint8_t button)
{
    debounceButtons();
    while (!justReleased(button))
    {
        debounceButtons();
    }
}

/**
 * @return true when confirmed rising edge at last debouncing.
 */
inline bool justPressed(uint8_t button)
{
    return wasEvent[button] && isDown[button];
}

/**
 * @return true when confirmed falling edge at last debouncing.
 */
inline bool justReleased(uint8_t button)
{
    return wasEvent[button] && !isDown[button];
}

/**
 * @brief Maintains wasEvent[] and toggles isDown[].
 */
void debounceButtons(void)
{
    uint8_t button;
    for (button = 0; button < NUM_BUTTONS; button++)
    {
        // count times buttons have been consecutively up/down (upto DEBOUNCE_COUNT).
        if (isPressed(button))
        {
            downCount[button] = MIN(downCount[button]+1, DEBOUNCE_COUNT);
            upCount[button] = 0;
        }
        else
        {
            upCount[button] = MIN(upCount[button]+1, DEBOUNCE_COUNT);
            downCount[button] = 0;
        }

        // check for confirmed up/down event
        if (isDown[button])
        {
            if (upCount[button] >= DEBOUNCE_COUNT)
            {
                isDown[button] = false;
                wasEvent[button] = true;
            }
            else
            {
                wasEvent[button] = false;
            }
        }
        else
        {
            if (downCount[button] >= DEBOUNCE_COUNT)
            {
                isDown[button] = true;
                wasEvent[button] = true;
            }
            else
            {
                wasEvent[button] = false;
            }
        }
    }
}

/**
 * @return true when button is currently down (does no debouncing!)
 */
inline bool isPressed(uint8_t button)
{
    switch (button)
    {
    case RED_BUTTON:      return RED_BUTTON_DOWN;
    case L_UP_BUTTON:     return L_UP_BUTTON_DOWN;
    case L_DOWN_BUTTON:   return L_DOWN_BUTTON_DOWN;
    case R_UP_BUTTON:     return R_UP_BUTTON_DOWN;
    case R_DOWN_BUTTON:   return R_DOWN_BUTTON_DOWN;
    case NEST_BUTTON:     return NEST_BUTTON_DOWN;
    default:              break;
    }

    return false;
}

inline bool bothRightButtonsPressed(void)
{
    return (justPressed(R_UP_BUTTON) && justPressed(R_DOWN_BUTTON)) ||
           (justPressed(R_UP_BUTTON) && isDown[R_DOWN_BUTTON])      ||
           (justPressed(R_DOWN_BUTTON) && isDown[R_UP_BUTTON]);

}

inline bool bothLeftButtonsPressed(void)
{
    return (justPressed(L_UP_BUTTON) && justPressed(L_DOWN_BUTTON)) ||
           (justPressed(L_UP_BUTTON) && isDown[L_DOWN_BUTTON])      ||
           (justPressed(L_DOWN_BUTTON) && isDown[L_UP_BUTTON]);

}
