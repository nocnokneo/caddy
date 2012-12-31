#include <avr/io.h>				// include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>			// include "signal" names (interrupt names)
#include <avr/interrupt.h>		// include interrupt support
#include <inttypes.h>

#include "global.h"
#include "timer.h"				// include timer function library (timing, PWM, etc)

// port and pins you will use for control lines
#define LCD_PORT	PORTC
#define LCD_DDR		DDRC
#define LCD_RS		2
#define LCD_RW		0	// not used on the Atmega32 board
#define LCD_E		3
#define LCD_POUT	PORTC
#define LCD_PIN		PINC
#define LCD_DELAY	asm volatile ("nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n");	

// Prototypes
void lcdInit(void);
void lcdWriteInit(uint8_t data);
void lcdControlWrite(uint8_t data);
void lcdDataWrite(uint8_t data);
void lcdSetCursor(uint8_t data);
void lcdPrintHex(uint8_t data);
void lcdWrite(uint8_t data);
