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
// ourLcd.h
#ifndef OURLCD_H
#define OURLCD_H

#include "caddy.h"
//#include <avr/io.h>				// include I/O definitions (port names, pin names, etc)
//#include <avr/signal.h>			// include "signal" names (interrupt names)
//#include <avr/interrupt.h>		// include interrupt support
//#include <inttypes.h>

//#include "global.h"
//#include "timer.h"				// include timer function library (timing, PWM, etc)

// port and pins you will use for control lines
#define LCD_PORT	PORTC
#define LCD_DDR	    DDRC
#define LCD_RS		2
#define LCD_RW		0	// not used on the Atmega32 board
#define LCD_E		3
#define LCD_POUT	PORTC
#define LCD_PIN	PINC
#define LCD_DELAY	\
    asm volatile ("nop; nop; nop; nop; nop; nop; nop; nop;" \
    "nop; nop; nop; nop; nop; nop; nop; nop;" \
    "nop; nop; nop; nop;")

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
void lcdWriteInit(u08 data);
void lcdControlWrite(u08 data);
void lcdDataWrite(u08 data);
void lcdSetCursor(u08 data);
void lcdPrintHex(u08 data, u08 row, u08 col);
void lcdPrintDec(s08 data, u08 row, u08 col);
void lcdWrite(u08 data);
void lcdWriteStr(u08 str[], u08 row, u08 col);
void ourLcdControlWrite(u08 data);
void lcdPrintDecU08(u08 data, u08 row, u08 col);
void lcdPrintDecS08(s08 data, u08 row, u08 col);

#endif  // #ifndef
