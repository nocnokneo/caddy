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

volatile int8_t lineOffset;
volatile int16_t lineSlope;
volatile BOOL topLost;
volatile BOOL bottomLost;
volatile uint8_t statsBuf[STAT_BUF_ROWS][STAT_BUF_COLS];
volatile BOOL statsBufProcessed;
uint8_t gotAck;
uint8_t gotNck;

void myDelay(uint16_t outerDelay);
void setServo(uint8_t servoNum, uint8_t servoPos);

void disableServo(uint8_t servoNum);
void setPose(uint8_t pose);
void grabBonusBall(void);
void packetRcv(uint8_t c);
void lineMode2Rcv(uint8_t c);
//void sendCommand(char *command);
void cmuInit(void);
void trackLineInit(void);
void servoInit(void);
void init(void);
void setLeftPWM(uint8_t pwm);
void setRightPWM(uint8_t pwm);
void trackLine(void);
//void analyzeTopStrip(uint8_t stipStats[], uint8_t numRows);
//void analyzeBottomStrip(uint8_t stipStats[], uint8_t numRows); 
uint8_t getMean(uint8_t stripStats[], uint8_t numRows);
void analyzeStatsBuf(void);
BOOL isGoodScan(uint8_t y);