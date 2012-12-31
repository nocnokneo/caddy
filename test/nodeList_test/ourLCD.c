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


void lcdWriteInit(uint8_t data)
{
	cbi(LCD_PORT, LCD_RS);
	lcdControlWrite(data);
}


void lcdControlWrite(uint8_t data)
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


void ourLcdControlWrite(uint8_t data) 
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


void lcdSetCursor(uint8_t data)
{
	cbi(LCD_PORT, LCD_RS);
	lcdWrite(data | 0x80);
}


void lcdDataWrite(uint8_t data)
{
	sbi(LCD_PORT, LCD_RS);		// set RS to "data"
	lcdWrite(data);
}


void lcdWrite(uint8_t data)
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


void lcdPrintHex(uint8_t data, uint8_t row, uint8_t col)
{
	uint8_t temp;
   
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


void lcdPrintDecU08(uint8_t data, uint8_t row, uint8_t col)
{
	uint8_t ones = 0;
   uint8_t tens = 0;
   uint8_t hundreds = 0;
   
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
   
	ones = data%10;
   tens = (data%100) / 10;
   hundreds = (data%1000) / 100;
   if (hundreds > 0)
   {
      lcdDataWrite(hundreds+0x30);
   }
   lcdDataWrite(tens+0x30);
   lcdDataWrite(ones+0x30);
}


void lcdPrintDecS08(int8_t data, uint8_t row, uint8_t col)
{
	uint8_t ones = 0;
   uint8_t tens = 0;
   uint8_t hundreds = 0;
   
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
   
   if (data < 0)
   {
      lcdDataWrite('-');
      data *= -1;
   }
	ones = data%10;
   tens = (data%100) / 10;
   hundreds = (data%1000) / 100;
   lcdDataWrite(hundreds+0x30);
   lcdDataWrite(tens+0x30);
   lcdDataWrite(ones+0x30);
}


/* prints a string to the lcd. Stops when a null (\0) is reached or 
   16 chars have been printed.
 */
void lcdWriteStr(uint8_t str[], uint8_t row, uint8_t col) 
{
   uint8_t i;

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
