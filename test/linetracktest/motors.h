#include <avr/io.h>		    // include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>	    // include "signal" names (interrupt names)
#include <avr/interrupt.h>	 // include interrupt support

#include "global.h"

uint8_t rightPWM;
uint8_t leftPWM;


#define LINE_CENTER         0x4d
#define LEFT_BASE_SPEED     140
#define RIGHT_BASE_SPEED    145
#define SPEED_RANGE         85
#define MIN_SPEED           BASE_SPEED-SPEED_RANGE
#define MAX_SPEED           BASE_SPEED+SPEED_RANGE




// linetracking prototypes ?


// Motor direction prototypes
void forward(void);
void reverse(void);
void neutral(void);
void brake(void);
void tractor_right(void);
void tractor_left(void);
void tank_right(void);
void tank_left(void);
