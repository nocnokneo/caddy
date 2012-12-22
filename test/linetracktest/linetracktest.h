#include <avr/io.h>		   // include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>	   // include "signal" names (interrupt names)
#include <avr/interrupt.h>	// include interrupt support

#include "global.h"		// include our global settings
#include "uart.h"		   // include uart function library
#include "rprintf.h"	   // include printf function library
#include "timer.h"		// include timer function library (timing, PWM, etc)
#include "vt100.h"		// include VT100 terminal support

#include "cmuDefines.h"
#include "motors.h"
#include "ourlcd.h"

volatile s08 lineOffset;
volatile s16 lineSlope;
volatile BOOL topLost;
volatile BOOL bottomLost;
volatile u08 statsBuf[STAT_BUF_ROWS][STAT_BUF_COLS];
volatile BOOL statsBufProcessed;
u08 gotAck;
u08 gotNck;

void myDelay(u16 outerDelay);
void setServo(u08 servoNum, u08 servoPos);

void disableServo(u08 servoNum);
void setPose(u08 pose);
void grabBonusBall(void);
void packetRcv(u08 c);
void lineMode2Rcv(u08 c);
//void sendCommand(char *command);
void cmuInit(void);
void trackLineInit(void);
void servoInit(void);
void init(void);
void setLeftPWM(u08 pwm);
void setRightPWM(u08 pwm);
void trackLine(void);
//void analyzeTopStrip(u08 stipStats[], u08 numRows);
//void analyzeBottomStrip(u08 stipStats[], u08 numRows); 
u08 getMean(u08 stripStats[], u08 numRows);
void analyzeStatsBuf(void);
BOOL isGoodScan(u08 y);