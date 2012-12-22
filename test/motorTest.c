//*****************************************************************************
// motorTest.c
// 
// Motor control test stub.  Ties enable pins high for 100% duty.
// 
// Revision History:
//    2/27/05 created by Patrick, Logan, and Scott
//
//*****************************************************************************

 
//----- Include Files ---------------------------------------------------------
#include <avr/io.h>		    // include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>	    // include "signal" names (interrupt names)
#include <avr/interrupt.h>  // include interrupt support
#include "timer.h"          // include timer (PWM) support

#include "global.h"		    // include global settings
#include "ourLCD.h"

void myDelay(u16 outerDelay)
{
   u16 i, j;
   for(i=0; i<outerDelay; i++)
   {
      for(j=0; j<MAX_U16; j++)
      {
	     ;
      }
   }
}

void myShortDelay(u16 outerDelay)
{
   u16 j;
   for(j=0; j<outerDelay; j++)
   {
     ;
   }
}

void forward(u16 outerDelay)
{
	// both motors forward
	sbi(PORTD, 3);
 	sbi(PORTD, 7);
	cbi(PORTD, 2);
	cbi(PORTD, 6);
	myDelay(outerDelay);
}

void reverse(u16 outerDelay)
{
	// both motors reverse
	sbi(PORTD, 2);
 	sbi(PORTD, 4);
	cbi(PORTD, 3);
	cbi(PORTD, 5);
	myDelay(outerDelay);
}

void neutral(u16 outerDelay)
{
	// both motors coast
	sbi(PORTD, 2);
 	sbi(PORTD, 4);
	sbi(PORTD, 3);
	sbi(PORTD, 5);
	myDelay(outerDelay);
}

void brake(u16 outerDelay)
{
	// both motors brake
	cbi(PORTD, 2);
 	cbi(PORTD, 6);
	cbi(PORTD, 3);
	cbi(PORTD, 7);
	myDelay(outerDelay);
}

void tractor_right(u16 outerDelay)
{
	// brake right, forward left
	sbi(PORTD, 3);
	cbi(PORTD, 2);
 	cbi(PORTD, 4);
	cbi(PORTD, 5);
	myDelay(outerDelay);
}

void tractor_left(u16 outerDelay)
{
	// brake left, forward right
	sbi(PORTD, 5);
	cbi(PORTD, 2);
 	cbi(PORTD, 4);
	cbi(PORTD, 3);
	myDelay(outerDelay);
}

void tank_right(u16 outerDelay)
{
	// forward left, reverse right
	sbi(PORTD, 3);
	sbi(PORTD, 4);
 	cbi(PORTD, 2);
	cbi(PORTD, 5);
	myDelay(outerDelay);
}

void tank_left(u16 outerDelay)
{
	// forward right, reverse left
	sbi(PORTD, 2);
	sbi(PORTD, 5);
 	cbi(PORTD, 3);
	cbi(PORTD, 4);
	myDelay(outerDelay);
}

//----- Begin Code ------------------------------------------------------------
int main(void)
{
   timerInit(); //Patrick added
   outb(DDRD, 0xFF);	// set all port D pins to output
   timer1PWMInit(8);
	timer1PWMAOn();
   timer1PWMBOn();

   myDelay(50);
   forward(0);
   
   lcdInit();
	lcdSetCursor(0);
   lcdDataWrite('S');

   u08 i,n=0;
   while(n<5)
   {
      for(i=0; i<255; i++)
      {
         timer1PWMASet(i);
         timer1PWMBSet(i);
         myShortDelay(0xFFF);
      }
      for(i=255; i>0; i--)
      {
         timer1PWMASet(i);
         timer1PWMBSet(i);
         myShortDelay(0xFFF);
      }
      n++;
      lcdSetCursor(0);
      lcdPrintHex(n);
   }
   lcdSetCursor(0);
   lcdDataWrite('F');
   
   //tank_left(30);
   //forward(80);
   //tractor_left(30);
   //forward(80);
   //neutral(0);
   //neutral(20);
   //brake(10);
   //reverse(80);
   //neutral(20);
   myDelay(3);
   brake(10);
   
   return 0;
}

