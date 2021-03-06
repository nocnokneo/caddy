// ourLcd.h
#ifndef OURLCD_H
#define OURLCD_H

#include <avr/io.h>				// include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>			// include "signal" names (interrupt names)
#include <avr/interrupt.h>		// include interrupt support
#include <inttypes.h>

#include "global.h"
#include "timer.h"				// include timer function library (timing, PWM, etc)

// port and pins you will use for control lines
#define LCD_PORT	PORTC
#define LCD_DDR	DDRC
#define LCD_RS		2
#define LCD_RW		0	// not used on the Atmega32 board
#define LCD_E		3
#define LCD_POUT	PORTC
#define LCD_PIN	PINC
#define LCD_DELAY	asm volatile ("nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n");	

// LCD display geometry
// change these definitions to adapt settings
#define LCD_LINES				2	// visible lines
#define LCD_LINE_LENGTH			16	// line length (in characters)
// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
//#define LCD_LINE2_DDRAMADDR		0x14
//#define LCD_LINE3_DDRAMADDR		0x54

// control commands
#define LCD_CLR             0      // DB0: clear display
#define LCD_HOME            1      // DB1: return to home position
#define LCD_ENTRY_MODE      2      // DB2: set entry mode
#define LCD_ENTRY_INC        1     //   DB1: increment
#define LCD_ENTRY_SHIFT      0     //   DB2: shift
#define LCD_ON_CTRL         3      // DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY       2     //   DB2: turn display on
#define LCD_ON_CURSOR        1     //   DB1: turn cursor on
#define LCD_ON_BLINK         0     //   DB0: blinking cursor
#define LCD_MOVE            4      // DB4: move cursor/display
#define LCD_MOVE_DISP        3     //   DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT       2     //   DB2: move right (0-> left)
#define LCD_FUNCTION        5      // DB5: function set
#define LCD_FUNCTION_8BIT    4     //   DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES  3     //   DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS  2     //   DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM           6      // DB6: set CG RAM address
#define LCD_DDRAM           7      // DB7: set DD RAM address


// Prototypes
void lcdInit(void);
void lcdWriteInit(uint8_t data);
void lcdControlWrite(uint8_t data);
void lcdDataWrite(uint8_t data);
void lcdSetCursor(uint8_t data);
void lcdPrintHex(uint8_t data, uint8_t row, uint8_t col);
void lcdPrintDec(int8_t data, uint8_t row, uint8_t col);
void lcdWrite(uint8_t data);
void lcdWriteStr(uint8_t str[], uint8_t row, uint8_t col);
//void lcdClear(void);
void ourLcdControlWrite(uint8_t data);
void lcdPrintDecU08(uint8_t data, uint8_t row, uint8_t col);
void lcdPrintDecS08(int8_t data, uint8_t row, uint8_t col);

#endif  // #ifndef
