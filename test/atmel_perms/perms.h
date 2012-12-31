// perms.h
#ifndef PERMS_H
#define PERMS_H

//#include "caddy.h"


#include "global.h"
#include <avr/io.h>				// include I/O definitions (port names, pin names, etc)
#include <avr/signal.h>			// include "signal" names (interrupt names)
#include <avr/interrupt.h>		// include interrupt support
#include <inttypes.h>


BOOL next_permutation(uint8_t *first, uint8_t *last);
void iter_swap(uint8_t *a, uint8_t *b);
void reverse(uint8_t *a, uint8_t *b);


#endif // #ifndef
