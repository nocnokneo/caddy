//*****************************************************************************
// motorCntrl.h
//
// Motor control function definitions and constants.
//
// Revision History:
//   3/21/05 created by Mike, based on motorTest.c
//       added #define's
//       added support for speed, motor selection
//       all speeds declared as 8 bit, u08
//   3/23/05 modified by Mike for use with the caddy
//      not sure which pwm controls which though..
//      so could be wrong
//
// Pinout:   =>  for Mike's bot!
//   0,1 Left motor cntrl
//   6,7 Right motor cntrl
//   5,4 motor enable, pwm outputs
//    5 - A, Right
//    4 - B, Left
//
// Pinout:   =>  for CADDY bot!
//   2,3 Left motor cntrl
//   6,7 Right motor cntrl
//   5,4 motor enable, pwm outputs
//    5 - A, Right
//    4 - B, Left
//
//  assumes motor enable is connected to PWM A,B
//    defined in timer.h
//*****************************************************************************

#ifndef MOTORCNTRL_H
#define MOTORCNTRL_H

#include "caddy.h"


//Motor selection constants
#define LEFT_MOTOR  0
#define RIGHT_MOTOR 1
#define LEFT_ENC    1
#define RIGHT_ENC   0

#define BOTH  2
//Speed definitions
#define MAX_BRAKE 255
//#define MAX_SPEED 255
//#define MIN_SPEED 0

//Pin defines
//defined by the active high pin
#define MC_PORT PORTA
#define FORWARD_LEFT  7
#define FORWARD_RIGHT 5
#define REVERSE_LEFT  6
#define REVERSE_RIGHT 4
#define PWM_LEFT  timer1PWMASet
#define PWM_RIGHT timer1PWMBSet
//#define TRACTOR_OVERSHOOT_DELAY     5000
#define TANK_OVERSHOOT_DELAY        16000

void moveStraight(s16 ticks, u08 speed);
void tractorTurn(u08 speed, s08 brads);
void tankTurn(u08 speed, s08 brads);
void enableMotors( void );
void disableMotors( void );

//select left, right, or both motors
//sets selected motor(s) to forward at speed
void forward(u08 motorSelect, u08 speed);
//select left, right, or both motors
//sets selected motor(s) to reverse at speed
void reverse(u08 motorSelect, u08 speed);
//disables motor controller
void neutral(void);
//brake selected motor
//full brake assumed
void brake(u08 motorSelect);
void tickWheels(s16 leftTicks, s16 rightTicks, u08 speed);
void motor_pin_test(void);


#endif
