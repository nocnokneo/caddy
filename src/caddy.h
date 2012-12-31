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
#include "perms.h"

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
#endif



// Prototypes -------------------------------------------------------

inline void initAtmel( void );

#endif  // #ifndef
