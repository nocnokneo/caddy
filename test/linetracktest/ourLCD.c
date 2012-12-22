#include "ourLCD.h"


void lcdInit(void)
{
   outb(DDRC, 0x0F);
	// Turn on LCD
	cbi(LCD_PORT, LCD_E);
	delay(20000);	//delay 15ms

	lcdWriteInit(0x30);
	delay(4500);
	lcdWriteInit(0x30);
	timerPause(150);
	lcdWriteInit(0x30);
	timerPause(40);
	lcdWriteInit(0x20);
	timerPause(40);
	lcdWriteInit(0x20);
	timerPause(40);
	//lcdWriteInit(0xc0);
   lcdWriteInit(0xa0);
	timerPause(40);
	lcdWriteInit(0x00);
	timerPause(40);
	lcdWriteInit(0xF0);
	timerPause(40);
	lcdWriteInit(0x00);
	timerPause(40);
	lcdWriteInit(0x10);
	timerPause(40);
	lcdWriteInit(0x00);
	timerPause(40);
	lcdWriteInit(0x60);
	timerPause(40);
	lcdWriteInit(0x00);
	timerPause(40);		
	lcdWriteInit(0xF0);
	timerPause(40);
}


void lcdWriteInit(u08 data)
{
	cbi(LCD_PORT, LCD_RS);
	lcdControlWrite(data);
}


void lcdControlWrite(u08 data)
{
   // write the control byte to the display controller
	//lcdBusyWait();							// wait until LCD not busy
	cbi(LCD_PORT, LCD_RS);			// set RS to "control"

	// 4 bit write
	outb(LCD_DDR, inb(LCD_DDR)|0xF0);	// set data I/O lines to output (4bit)
	outb(LCD_POUT, (inb(LCD_POUT)&0x0F) | (data&0xF0) );	// output data, high 4 bits
	sbi(LCD_PORT, LCD_E);	// set "E" line
	delay(40);
	cbi(LCD_PORT, LCD_E);	// clear "E" line
	delay(40);
}


void ourLcdControlWrite(u08 data) 
{
// write the control byte to the display controller
	//lcdBusyWait();							// wait until LCD not busy
   delay(4500);
	cbi(LCD_PORT, LCD_RS);			// set RS to "control"
		// 4 bit write
		sbi(LCD_PORT, LCD_E);	// set "E" line
		outb(LCD_DDR, inb(LCD_DDR)|0xF0);	// set data I/O lines to output (4bit)
		outb(LCD_POUT, (inb(LCD_POUT)&0x0F) | (data&0xF0) );	// output data, high 4 bits
		LCD_DELAY;								// wait
		LCD_DELAY;								// wait
		cbi(LCD_PORT, LCD_E);	// clear "E" line
		LCD_DELAY;								// wait
		LCD_DELAY;								// wait
		sbi(LCD_PORT, LCD_E);	// set "E" line
		outb(LCD_POUT, (inb(LCD_POUT)&0x0F) | (data<<4) );	// output data, low 4 bits
		LCD_DELAY;								// wait
		LCD_DELAY;								// wait
		cbi(LCD_PORT, LCD_E);	// clear "E" line
	//	leave data lines in input mode so they can be most easily used for other purposes
		//outb(LCD_DATA_DDR, inb(LCD_DATA_DDR)&0x0F);		// set data I/O lines to input (4bit)
		//outb(LCD_DATA_POUT, inb(LCD_DATA_POUT)|0xF0);	// set pull-ups to on (4bit)
}


void lcdSetCursor(u08 data)
{
	cbi(LCD_PORT, LCD_RS);
	lcdWrite(data | 0x80);
}


void lcdDataWrite(u08 data)
{
	sbi(LCD_PORT, LCD_RS);		// set RS to "data"
	lcdWrite(data);
}


void lcdWrite(u08 data)
{
	// 4 bit write
	outb(LCD_DDR, inb(LCD_DDR)|0xF0);	// set data I/O lines to output (4bit)
	outb(LCD_POUT, (inb(LCD_POUT)&0x0F) | (data&0xF0) );	// output data, high 4 bits
	sbi(LCD_PORT, LCD_E);	// set "E" line
	delay(40);
	cbi(LCD_PORT, LCD_E);	// clear "E" line
	delay(40);
	
	outb(LCD_POUT, (inb(LCD_POUT)&0x0F) | (data<<4) );	// output data, low 4 bits
	sbi(LCD_PORT, LCD_E);	// set "E" line
	delay(40);
	cbi(LCD_PORT, LCD_E);	// clear "E" line
	delay(40);
}


void lcdPrintHex(u08 data, u08 row, u08 col)
{
	u08 temp;
   
   switch (row) 
   {
   case 1: 
      lcdSetCursor(LCD_LINE1_DDRAMADDR + col);
      break;
   case 0:
   default:
      lcdSetCursor(LCD_LINE0_DDRAMADDR + col);
      break;
   }
   
	temp = ((data & 0xF0) >> 4) + 0x30;
	if(temp >= 0x3A)
	{
		temp += 7;
	}
	lcdDataWrite(temp);
	temp = (data & 0x0F) + 0x30;
	if(temp >= 0x3A)
	{
		temp += 7;
	}
	lcdDataWrite(temp);
}


/* prints a string to the lcd. Stops when a null (\0) is reached or 
   16 chars have been printed.
 */
void lcdWriteStr(u08 str[], u08 row, u08 col) 
{
   u08 i;

   // make sure we don't have a null pointer
   if (!str) {
      return;
   }
   
   switch (row) 
   {
   case 1: 
      lcdSetCursor(LCD_LINE1_DDRAMADDR + col);
      break;
   case 0:
   default:
      lcdSetCursor(LCD_LINE0_DDRAMADDR + col);
      break;
   }
   
   // Print each char one at a time
   for (i = 0; (i < LCD_LINE_LENGTH-col) && (str[i] != '\0'); i++)
   {
      lcdDataWrite(str[i]);
   }
}

/*
void lcdClear(void)
{
	// clear LCD
	ourLcdControlWrite(1<<LCD_CLR);
}
*/
