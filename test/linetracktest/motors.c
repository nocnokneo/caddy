/*
 * Contains: 
 *    - Linetracking ?
 *    - Subroutines for setting motor directions.
 *
 */


#include "motors.h"





// Motor Direction Subroutines ---------------------------
// Pins 2,3 are left wheel
// Pins 6,7 are right wheel

void forward(void)
{
	// both motors forward
	sbi(PORTD, 3);
 	sbi(PORTD, 6);
	cbi(PORTD, 2);
	cbi(PORTD, 7);
}

void reverse(void)
{
	// both motors reverse
	sbi(PORTD, 2);
 	sbi(PORTD, 7);
	cbi(PORTD, 3);
	cbi(PORTD, 6);
}

void neutral(void)
{
	// both motors coast
	sbi(PORTD, 2);
 	sbi(PORTD, 6);
	sbi(PORTD, 3);
	sbi(PORTD, 7);
}

void brake(void)
{
	// both motors brake
	cbi(PORTD, 2);
 	cbi(PORTD, 6);
	cbi(PORTD, 3);
	cbi(PORTD, 7);
}

void tractor_right(void)
{
	// brake right, forward left
	sbi(PORTD, 3);
	cbi(PORTD, 2);
 	cbi(PORTD, 6);
	cbi(PORTD, 7);
}

void tractor_left(void)
{
	// brake left, forward right
	sbi(PORTD, 6);
	cbi(PORTD, 2);
 	cbi(PORTD, 7);
	cbi(PORTD, 3);
}

void tank_right(void)
{
	// forward left, reverse right
	sbi(PORTD, 3);
	sbi(PORTD, 7);
 	cbi(PORTD, 2);
	cbi(PORTD, 6);
}

void tank_left(void)
{
	// forward right, reverse left
	sbi(PORTD, 2);
	sbi(PORTD, 6);
 	cbi(PORTD, 3);
	cbi(PORTD, 7);
}
