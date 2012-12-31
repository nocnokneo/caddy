//*****************************************************************************
// pickuptest.c
//
//   Writes to LCD, moves forward with PWM, picks-up ball, and drops ball.
//   Based on fixed delays.
// 
// Revision History:
// When			   Who			   Description of change
// -----------	   -----------	   -----------------------
// 3-12-2005      Logan Kinde    Created
//
//*****************************************************************************

#include <avr/io.h>		   // include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>	   // include "signal" names (interrupt names)
#include <avr/interrupt.h>	// include interrupt support

#include "global.h"		// include our global settings
#include "uart.h"		   // include uart function library
#include "rprintf.h"	   // include printf function library
#include "timer.h"		// include timer function library (timing, PWM, etc)
#include "vt100.h"		// include VT100 terminal support

#include "cmuDefines.h"
#include "motorCntrl.h"
#include "ourlcd.h"

volatile uint8_t linePosition;
uint8_t gotAck;
uint8_t gotNck;

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


void setServo(uint8_t servoNum, uint8_t servoPos)
{
   rprintf("sv %d %d\r", servoNum, servoPos);
}


void disableServo(uint8_t servoNum)
{
   rprintf("so %d 0\r", servoNum);
}


void setPose(uint8_t pose)
{
   switch (pose)
   {
   case DRIVE_OPEN:
      // set servos to initial positions
      setServo(PAN, PAN_CENTER);
      setServo(BOOM, MAX_BOOM_UP);
      setServo(TILT, TILT_VERT);
      setServo(DOOR, DOOR_CLOSED);
      myDelay(30);
      setServo(LIFT, LIFT_OPEN);
      myDelay(20);
      disableServo(PAN);
      disableServo(BOOM);
      disableServo(TILT);
      disableServo(DOOR);
      disableServo(LIFT);
      lcdWriteStr("Drive Open", 0, 0);
      break;
   case DRIVE_UP:
      // set servos to initial positions
      setServo(PAN, PAN_CENTER);
      setServo(BOOM, BOOM_UP);
      setServo(TILT, TILT_VERT);
      setServo(DOOR, DOOR_CLOSED);
      myDelay(30);
      setServo(LIFT, LIFT_UP);
      myDelay(50);
      disableServo(PAN);
      disableServo(BOOM);
      disableServo(TILT);
      disableServo(DOOR);
      disableServo(LIFT);
      lcdWriteStr("Drive UP", 0, 0);
      break;
   default:
      lcdWriteStr("ERROR", 0, 0);
      break;
   }
}


void grabBonusBall(void)
{
   // Get in position
   //setPose(BB_READY);
   setServo(TILT, TILT_BACK);
   setServo(LIFT, LIFT_BB_READY);
   myDelay(40);
   
   // Drive up to the corner
   forward(BOTH, 255);
   myDelay(20);
   brake(BOTH);

   // Execute the pickup sequence
   setServo(BOOM, BOOM_BB_GRAB);
   myDelay(10);
   setServo(TILT, TILT_BB_GRAB);
   myDelay(10);
   setServo(BOOM, BOOM_UP);
   myDelay(15);
   setServo(LIFT, LIFT_UP);
   myDelay(0);
   
   // Back away from the corner
   reverse(BOTH, 200);
   myDelay(15);
   brake(BOTH);
}



void init(void)
{
   // Timer Initialization
   timerInit();
   
   // LCD Initialization
   lcdInit();
   ourLcdControlWrite(1<<LCD_ON_CTRL | 1<<LCD_ON_DISPLAY);
   
   // UART Initialization
	uartInit();
	uartSetBaudRate(CMU_BAUD);
	//uartSetRxHandler(serialRcv);
   rprintfInit(uartSendByte);

   // PWM Initialization
   outb(DDRD, 0xFF);	// set all port D pins to output
   timer1PWMInit(8);
	timer1PWMAOn();
   timer1PWMBOn();
   outb(DDRA, 0xFF);	// set all port D pins to output
}



int main(void)
{
   neutral();
   init();
   lcdWriteStr("Ready           ", 0, 0);

   // Bonus ball pickup sequence:
   setPose(DRIVE_UP);
   myDelay(30);
   
   grabBonusBall();
   
/* 
   // Grounb ball pickup sequence:
   setPose(DRIVE_OPEN);
   
   // move, pickup, and brake
   forward();
   myDelay(60);
   setServo(LIFT, MAX_LIFT_UP);
   //disableServo(LIFT);
   myDelay(60);
   brake();
   myDelay(10);
   
   // drop balls and return to initial position
   setServo(DOOR, DOOR_OPEN);
   myDelay(60);
   setServo(DOOR, DOOR_CLOSED);
   myDelay(30);
   setServo(LIFT, MAX_LIFT_OPEN);
   //myDelay(5);
   //disableServo(DOOR);
   //disableServo(LIFT);
*/

   lcdWriteStr("End", 1, 0);
   brake(BOTH);

	return 0;
}
