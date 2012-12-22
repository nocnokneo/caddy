// perms.h
#ifndef PERMS_H
#define PERMS_H

//#include "caddy.h"


#include "global.h"
#include <avr/io.h>				// include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>			// include "signal" names (interrupt names)
#include <avr/interrupt.h>		// include interrupt support
#include <inttypes.h>


BOOL next_permutation(u08 *first, u08 *last);
void iter_swap(u08 *a, u08 *b);
void reverse(u08 *a, u08 *b);


#endif // #ifndef
