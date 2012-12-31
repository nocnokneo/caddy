/* buttons.c
 *
 *    Button debouncing, start bot logic
 *
 */

#include "global.h"
#include "buttons.h"

/*
 * Sets isDown[] and wasEvent[] to all false.  Assumes timer is already initialized.
 */
void initButtons(void)
{
   uint8_t i;
   for( i = 0; i < NUM_BUTTONS; i++ )
   {
      isDown[i] = FALSE;
      wasEvent[i] = FALSE;
      upCount[i] = DEBOUNCE_COUNT;
      downCount[i] = 0;
   }
}

void waitFor(uint8_t button)
{
   debounceButtons();
   while( !justReleased(button) )
   {
      debounceButtons();
   }
}

/*
 * Returns true when confirmed rising edge at last debouncing.
 */
BOOL justPressed(uint8_t button)
{
   return wasEvent[button] && isDown[button];
}


/*
 * Returns true when confirmed falling edge at last debouncing.
 */
BOOL justReleased(uint8_t button)
{
   return wasEvent[button] && !isDown[button];
}

/*
 * Maintains wasEvent[] and toggles isDown[].
 */
void debounceButtons(void)
{
   uint8_t button;
   for( button = 0; button < NUM_BUTTONS; button++)
   {
      // count times buttons have been consecutively up/down (upto DEBOUNCE_COUNT).
      if( isPressed(button) )
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
      if( isDown[button] )
      {
         if( upCount[button] >= DEBOUNCE_COUNT )
         {
            isDown[button] = FALSE;
            wasEvent[button] = TRUE;
         }
         else
         {
            wasEvent[button] = FALSE;
         }
      }
      else
      {
         if( downCount[button] >= DEBOUNCE_COUNT )
         {
            isDown[button] = TRUE;
            wasEvent[button] = TRUE;
         }
         else
         {
            wasEvent[button] = FALSE;
         }
      }
   }
}


/*
 * Returns true when button is currently down (may be bouncing).
 */
BOOL isPressed(uint8_t button)
{
   BOOL pressed;
   
   switch( button )
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
         pressed = FALSE;
         break;
   }
   
   return pressed;
}


