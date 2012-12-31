//*****************************************************************************
// buttontest.c
//
//   software debouncing an array of buttons,
//   debounced external interrupts,
//   debugger development
//
//*****************************************************************************

#include "buttontest.h"


int main(void)
{
   init();
   resetFlag = TRUE;
   outb(DDRA, 0x00);      // set all port A pins to input
   outb(DDRD, 0x01);      
   
   while(1)
   {
      // Let user tweak values., until red button is released
      tweakValues();
      
      lcdWriteStr("Running         ",0,0);
      lcdWriteStr("                ",1,0);
      
      userWantsToStop = FALSE;
      ENABLE_INT0;
      
      while( //botNode != STOP_NODE &&
             !userWantsToStop )
      {
         ;
      }
   }
   
   /*
   lcdWriteStr("Rdy",0,0);
   while( !timeToStartBot() )
   {
      ;
   }
   lcdWriteStr("Go",1,0);
   */
   
   /*
   while(1) 
   {
      printPortA();
   }
   */
   
   /************ INT0 test ************** 
   lcdWriteStr("Running",0,0);
   turnRemoteLightOn();
   userWantsToStop = FALSE;
   ENABLE_INT0;                // enable external interrupts
   sei();                      // enable all interrupts
   while(!userWantsToStop) 
   {
      printPortA();
   }
   turnRemoteLightOff();
   lcdWriteStr("Done   ",0,0);
   */
   
	return 0;
}

void turnOnRemoteLight(void)
{
   sbi(PORTD, 7);
}

void turnOffRemoteLight(void)
{
   cbi(PORTD, 7);
}

/*
 * External interupt 0 handler for Atmega32 - Masks future interrupts.
 * If writing this, I discovered that AVRlibC has library functions for
 * external interrupts that is easier to configure.
 */
SIGNAL(SIG_INTERRUPT0)
{
   DISABLE_INT0;           // Mask external interrupt 0
   
   // debounce button
   uint8_t count = 0;
   while( MODE_BUTTON_DOWN && count < MAX_U08 )
      count++;
   
   if(count == MAX_U08 )
   {
      userWantsToStop = TRUE;
   }
   else
   {
      ENABLE_INT0;         // Re-allow external interrupt 0, due to bounce
   }
}

void printPortA(void)
{
   int8_t i;
   for( i = 7; i >= 0; i--)
   {
      if( bit_is_set(PINA,i) )
         lcdWriteStr("1",1,i);
      else
         lcdWriteStr("0",1,i);
   }
}

void init(void)
{
   // Initialize Timer
   timerInit();
   // Initialize LCD
   lcdInit();
   ourLcdControlWrite(1<<LCD_ON_CTRL | 1<<LCD_ON_DISPLAY);
   // Initialize PWM
   outb(DDRD, 0xCF);
   timer1PWMInit(8);
	timer1PWMAOn();
   timer1PWMBOn();
}




void myDelay(uint16_t outerDelay)
{
   uint16_t i, j;
   for(i=0; i<outerDelay; i++)
   {
      for(j=0; j<MAX_U16; j++)
      {
	     ;
      }
   }
}

/*
 * Debounces red button.
 * Delays and returns true once red button has been released.
 */
BOOL timeToStartBot(void)
{
   BOOL timeToStart = FALSE;
   
   #if SIMULATING
      timeToStart = TRUE;
   #else
      timeToStart = justReleased(RED_BUTTON) || BOTH_RIGHT_BUTTONS_PRESSED;
      if( timeToStart )
         myDelay(START_DELAY);
   #endif
   
   return timeToStart;
}

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
      
      // TEST CODE
      //if( button == 1 || button == 2 )
      //{
      //   uint8_t line = button-1;
      //      
      //   lcdPrintHex(upCount[button],line,0);
      //   lcdPrintHex(downCount[button],line,3);
      //   lcdPrintHex(isDown[button],line,6);
      //   lcdPrintHex(wasEvent[button],line,9);
      //   
      //   static uint8_t eventCount[2] = {0, 0};
      //   if( wasEvent[button] )
      //     eventCount[line]++;
      //   lcdPrintHex(eventCount[line],line,12);
      //}
      
      // TEST CODE
      //if( button == 1 || button == 2 )
      //{
      //   uint8_t line = button-1;
      //   lcdPrintHex(isDown[button],line,0);
      //   
      //   static uint8_t eventCount[2] = {0, 0};
      //   if( wasEvent[button] )
      //      eventCount[line]++;
      //   lcdPrintHex(eventCount[line],line,3);
      //   
      //   static uint8_t pressCount[2] = {0, 0};
      //   if( justPressed(button) )
      //      pressCount[line]++;
      //   lcdPrintHex(pressCount[line],line,6);
      //   
      //   static uint8_t releaseCount[2] = {0, 0};
      //   if( justReleased(button) )
      //      releaseCount[line]++;
      //   lcdPrintHex(releaseCount[line],line,9);
      //}
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
      case MODE_BUTTON:
         pressed = MODE_BUTTON_DOWN;
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
      default:
         pressed = FALSE;
         break;
   }
   
   return pressed;
}

/*
 * Polls and debounces push buttons for tweaking values.  Prints debugging values.
 * Loads and stores values in EEPROM.  Remote light is on while tweaking.
 */
void tweakValues(void)
{
   turnOnRemoteLight();
   loadTweakValues();
   initButtons();
   
   tweakMode = WELCOME;
   lcdWriteStr("Welcome to the  ",0,0);
   lcdWriteStr("ALF debugger.   ",1,0);
   
   while( !timeToStartBot() )
   {
      debounceButtons();
      updateTweaks();
      printValues();
      
      if( justReleased(MODE_BUTTON) )
      {
         toggleTweakMode();
      }
   }
   
   turnOffRemoteLight();
   storeTweakValues();
}

/*
 * Sets values that can be tweaked to predefined constants.
 */
void loadTweakValues(void)
{
   if( resetFlag )  // will use EE_PROM eventually
   {
      l_base = L_BASE_START;
      r_base = R_BASE_START;
      resetFlag = FALSE;
   }
}

void storeTweakValues(void)
{
}

void updateTweaks(void)
{
   switch( tweakMode )
   {
      case BASE_SPEED_TWEAK:
         if( justReleased(L_UP_BUTTON) )
            l_base++;
         if( justReleased(L_DOWN_BUTTON) )
            l_base--;
         if( justReleased(R_UP_BUTTON) )
            r_base++;
         if( justReleased(R_DOWN_BUTTON) )
            r_base--;
         break;
   }
}

void printValues(void)
{
   switch( tweakMode )
   {
      case BASE_SPEED_TWEAK:
         lcdPrintHex(l_base,1,5);
         lcdPrintHex(r_base,1,14);
         break;
   }
}

void toggleTweakMode(void)
{
   // advance tweak mode (skipping welcome mode)
   tweakMode++;
   if( tweakMode == NUM_TWEAK_MODES )
      tweakMode = 1;
   
   // clear lcd and print lables for new tweak mode
   switch( tweakMode )
   {
      case BASE_SPEED_TWEAK:
         lcdWriteStr("Base speed tweak",0,0);
         lcdWriteStr("Left:   Right:  ",1,0);
         break;
      case LINE_TRACK_TWEAK:
         lcdWriteStr("Line track tweak",0,0);
         lcdWriteStr("     (TBD)      ",1,0);
         break;
      case PAN_TILT_TWEAK:
         lcdWriteStr("Pan & tilt tweak",0,0);
         lcdWriteStr("     (TBD)      ",1,0);
         break;
   }
}

