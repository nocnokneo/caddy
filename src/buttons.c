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
/* buttons.c
 *
 *    Button debouncing, start bot logic
 *
 */

#include "buttons.h"

/*
 * Sets isDown[] and wasEvent[] to all false.  Assumes timer is already initialized.
 */
void initButtons(void)
{
    uint8_t i;
    for (i = 0; i < NUM_BUTTONS; i++)
    {
        isDown[i] = false;
        wasEvent[i] = false;
        upCount[i] = DEBOUNCE_COUNT;
        downCount[i] = 0;
    }
}

void waitFor(uint8_t button)
{
    debounceButtons();
    while (!justReleased(button))
    {
        debounceButtons();
    }
}

/*
 * Returns true when confirmed rising edge at last debouncing.
 */
inline bool justPressed(uint8_t button)
{
    return wasEvent[button] && isDown[button];
}

/*
 * Returns true when confirmed falling edge at last debouncing.
 */
inline bool justReleased(uint8_t button)
{
    return wasEvent[button] && !isDown[button];
}

/*
 * Maintains wasEvent[] and toggles isDown[].
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
        } else
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

/*
 * Returns true when button is currently down (may be bouncing).
 */
inline bool isPressed(uint8_t button)
{
    bool pressed;

    switch (button)
    {
    case RED_BUTTON:
        pressed = RED_BUTTON_DOWN;
        break;
    case L_UP_BUTTON:
        pressed = L_UP_BUTTON_DOWN;
        break;
    case L_DOWN_BUTTON:
        pressed = L_DOWN_BUTTON_DOWN;
        break;
    case R_UP_BUTTON:
        pressed = R_UP_BUTTON_DOWN;
        break;
    case R_DOWN_BUTTON:
        pressed = R_DOWN_BUTTON_DOWN;
        break;
    case NEST_BUTTON:
        pressed = NEST_BUTTON_DOWN;
        break;
    default:
        pressed = false;
        break;
    }

    return pressed;
}

