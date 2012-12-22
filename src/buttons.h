// buttons.h
#ifndef BUTTONS_H
#define BUTTONS_H

#include "caddy.h"

#define DEBOUNCE_COUNT   3   // should be equal to 2 or greater

#define RED_BUTTON       0
#define L_UP_BUTTON      1
#define L_DOWN_BUTTON    2
#define R_UP_BUTTON      3
#define R_DOWN_BUTTON    4
#define NEST_BUTTON      5
#define NUM_BUTTONS      6    // change isPressed(u08 button) when adding a button

#define RED_BUTTON_DOWN       bit_is_clear(PIND,6)
#define L_UP_BUTTON_DOWN      bit_is_clear(PINA,0)
#define L_DOWN_BUTTON_DOWN    bit_is_clear(PINA,1)
#define R_UP_BUTTON_DOWN      bit_is_clear(PINA,2)
#define R_DOWN_BUTTON_DOWN    bit_is_clear(PINA,3)
#define NEST_BUTTON_DOWN      bit_is_clear(PINB,0)

#define BREAK_BEAM_TRIGGERED  bit_is_clear(PINB,1)

#define BOTH_RIGHT_BUTTONS_PRESSED   ( (justPressed(R_UP_BUTTON) && justPressed(R_DOWN_BUTTON)) || (justPressed(R_UP_BUTTON) && isDown[R_DOWN_BUTTON]) || (justPressed(R_DOWN_BUTTON) && isDown[R_UP_BUTTON]) )
#define BOTH_LEFT_BUTTONS_PRESSED    ( (justPressed(L_UP_BUTTON) && justPressed(L_DOWN_BUTTON)) || (justPressed(L_UP_BUTTON) && isDown[L_DOWN_BUTTON]) || (justPressed(L_DOWN_BUTTON) && isDown[L_UP_BUTTON]) )


BOOL isDown[NUM_BUTTONS];
BOOL wasEvent[NUM_BUTTONS];
u08 upCount[NUM_BUTTONS];
u08 downCount[NUM_BUTTONS];


void initButtons(void);
void waitFor(u08 button);
BOOL justPressed(u08 button);
BOOL justReleased(u08 button);
void debounceButtons(void);
BOOL isPressed(u08 button);



#endif  // #ifndef
