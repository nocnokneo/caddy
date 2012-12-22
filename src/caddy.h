// caddy.h
#ifndef CADDY_H
#define CADDY_H


// Defines ---------------------------------------------------------- 

#define DEBUGGING TRUE

#define START_DELAY 5


// Includes ---------------------------------------------------------

#include <stdlib.h>
#include <avr/io.h>		      // include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>	      // include "signal" names (interrupt names)
#include <avr/interrupt.h>	   // include interrupt support
#include "uart.h"		         // include uart function library
#include "rprintf.h"	         // include printf function library
#include "timer.h"		      // include timer function library (timing, PWM, etc)
#include "encoder.h"
#include "linkedList.h"

#include "global.h"
#include "botCntrl.h"
#include "updatePath.h"
#include "junctionCode.h"
#include "helperFunctions.h"

#include "eeProm.h"
#include "buttons.h"
#include "motorCntrl.h"
#include "camera.h"
#include "servos.h"
#include "trackLine.h"
#include "trackColor.h"

#include "nodeList.h"


#if DEBUGGING
#include "ourLCD.h"
#include "debugger.h"
#include "testCode.h"
#include "exercises.h"
#endif



// Prototypes -------------------------------------------------------

void initAtmel( void );

void runFixedPath( void );
void baseSpeedTest( void );
void bbPickupTest( void );
void lineStatsTest( void );
void seeBallTest( void );
void gbPickupTest( void );

#endif  // #ifndef
