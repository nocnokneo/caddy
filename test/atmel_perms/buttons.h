// buttons.h
#ifndef BUTTONS_H
#define BUTTONS_H

#include <avr/io.h>				// include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>			// include "signal" names (interrupt names)
#include <avr/interrupt.h>		// include interrupt support
#include <inttypes.h>
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

#define BOTH_RIGHT_BUTTONS_PRESSED   ( (justPressed(R_UP_BUTTON) && justPressed(R_DOWN_BUTTON)) || (justPressed(R_UP_BUTTON) && isDown[R_DOWN_BUTTON]) || (justPressed(R_DOWN_BUTTON) && isDown[R_UP_BUTTON]) )
#define BOTH_LEFT_BUTTONS_PRESSED    ( (justPressed(L_UP_BUTTON) && justPressed(L_DOWN_BUTTON)) || (justPressed(L_UP_BUTTON) && isDown[L_DOWN_BUTTON]) || (justPressed(L_DOWN_BUTTON) && isDown[L_UP_BUTTON]) )


BOOL isDown[NUM_BUTTONS];
BOOL wasEvent[NUM_BUTTONS];
uint8_t upCount[NUM_BUTTONS];
uint8_t downCount[NUM_BUTTONS];


void initButtons(void);
void waitFor(uint8_t button);
BOOL justPressed(uint8_t button);
BOOL justReleased(uint8_t button);
void debounceButtons(void);
BOOL isPressed(uint8_t button);



#endif  // #ifndef
