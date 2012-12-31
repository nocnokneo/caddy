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
	lcdWriteInit(0xc0);
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
void lcdPrintHex(uint8_t data)
{
	uint8_t temp;
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
