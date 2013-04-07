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
/**
 * @file
 * @brief Interface to PWM motor controller
 * @author Mike Shelley
 *
 * Pinout:
 *   2,3 Left motor control
 *   6,7 Right motor control
 *   5,4 motor enable, PWM outputs
 *    5 - A, Right
 *    4 - B, Left
 *
 * @note: Assumes motor enable is connected to PWM A,B defined in timer.h
 */
#ifndef MOTORCNTRL_H_
#define MOTORCNTRL_H_

// AVRLIB
#include "timer.h"

// avr-libc
#include <avr/io.h>
#include <stdint.h>

//Motor selection constants
#define LEFT_MOTOR  0
#define RIGHT_MOTOR 1
#define BOTH_MOTORS 2
#define LEFT_ENC    1
#define RIGHT_ENC   0

//Speed definitions
#define MAX_BRAKE 255

//Pin defines
//defined by the active high pin
#define MC_PORT PORTA
#define FORWARD_LEFT  7
#define FORWARD_RIGHT 5
#define REVERSE_LEFT  6
#define REVERSE_RIGHT 4
#define PWM_LEFT  timer1PWMASet
#define PWM_RIGHT timer1PWMBSet

void moveStraight(int16_t ticks, uint8_t speed);
void tractorTurn(uint8_t speed, int8_t brads);
void tankTurn(uint8_t speed, int8_t brads);
void enableMotors( void );
void disableMotors( void );

//select left, right, or both motors
//sets selected motor(s) to forward at speed
void forward(uint8_t motorSelect, uint8_t speed);
//select left, right, or both motors
//sets selected motor(s) to reverse at speed
void reverse(uint8_t motorSelect, uint8_t speed);
//disables motor controller
void neutral(void);
//brake selected motor
//full brake assumed
void brake(uint8_t motorSelect);
void tickWheels(int16_t leftTicks, int16_t rightTicks, uint8_t speed);

#endif // #ifndef MOTORCNTRL_H_
