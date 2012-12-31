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
// buttons.h
#ifndef BUTTONS_H
#define BUTTONS_H

#include "caddy.h"
#include <stdint.h>
#include <stdbool.h>

#define DEBOUNCE_COUNT   3   // should be equal to 2 or greater

#define RED_BUTTON       0
#define L_UP_BUTTON      1
#define L_DOWN_BUTTON    2
#define R_UP_BUTTON      3
#define R_DOWN_BUTTON    4
#define NEST_BUTTON      5
#define NUM_BUTTONS      6    // change isPressed(uint8_t button) when adding a button

#define RED_BUTTON_DOWN       bit_is_clear(PIND,6)
#define L_UP_BUTTON_DOWN      bit_is_clear(PINA,0)
#define L_DOWN_BUTTON_DOWN    bit_is_clear(PINA,1)
#define R_UP_BUTTON_DOWN      bit_is_clear(PINA,2)
#define R_DOWN_BUTTON_DOWN    bit_is_clear(PINA,3)
#define NEST_BUTTON_DOWN      bit_is_clear(PINB,0)

#define BREAK_BEAM_TRIGGERED  bit_is_set(PINB,1)

#define BOTH_RIGHT_BUTTONS_PRESSED   ( (justPressed(R_UP_BUTTON) && justPressed(R_DOWN_BUTTON)) || (justPressed(R_UP_BUTTON) && isDown[R_DOWN_BUTTON]) || (justPressed(R_DOWN_BUTTON) && isDown[R_UP_BUTTON]) )
#define BOTH_LEFT_BUTTONS_PRESSED    ( (justPressed(L_UP_BUTTON) && justPressed(L_DOWN_BUTTON)) || (justPressed(L_UP_BUTTON) && isDown[L_DOWN_BUTTON]) || (justPressed(L_DOWN_BUTTON) && isDown[L_UP_BUTTON]) )


bool isDown[NUM_BUTTONS];
bool wasEvent[NUM_BUTTONS];
uint8_t upCount[NUM_BUTTONS];
uint8_t downCount[NUM_BUTTONS];


void initButtons(void);
void waitFor(uint8_t button);
inline bool justPressed(uint8_t button);
inline bool justReleased(uint8_t button);
void debounceButtons(void);
inline bool isPressed(uint8_t button);



#endif  // #ifndef
