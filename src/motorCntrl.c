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
//*****************************************************************************
// motorCntrl.c
//
// Motor control functions.
//
// Revision History:
//   3/21/05 created by Mike, based on motorTest.c
//       added #define's
//       added support for speed, motor selection
//       all speeds declared as 8 bit, uint8_t
//   3/23/05 modified by Mike for use with the caddy
//       not sure which pwm controls which though..
//       so could be wrong
//
//  assumes motor enable is connected to PWM A,B
//    defined in timer.h
//*****************************************************************************
#include "motorCntrl.h"
#include "encoder.h"
#include "eeProm.h"
#include "ourLCD.h"

// avr-libc
#include <stdint.h>

void forward(uint8_t motorSelect, uint8_t speed)
{
    switch (motorSelect)
    {
    case LEFT_MOTOR:
        sbi(MC_PORT, FORWARD_LEFT);
        cbi(MC_PORT, REVERSE_LEFT);
        PWM_LEFT(speed);
        break;
    case RIGHT_MOTOR:
        sbi(MC_PORT, FORWARD_RIGHT);
        cbi(MC_PORT, REVERSE_RIGHT);
        PWM_RIGHT(speed);
        break;
    case BOTH:
        // both motors forward
        sbi(MC_PORT, FORWARD_LEFT);
        sbi(MC_PORT, FORWARD_RIGHT);
        cbi(MC_PORT, REVERSE_LEFT);
        cbi(MC_PORT, REVERSE_RIGHT);
        PWM_RIGHT(speed);
        PWM_LEFT(speed);
        break;
    }
}

void tickWheels(int16_t leftTicks, int16_t rightTicks, uint8_t speed)
{
    if (leftTicks >= 0)
    {
        forward(LEFT_MOTOR, speed);
    }
    else
    {
        reverse(LEFT_MOTOR, speed);
        leftTicks *= -1;
    }

    if (rightTicks >= 0)
    {
        forward(RIGHT_MOTOR, speed);
    }
    else
    {
        reverse(RIGHT_MOTOR, speed);
        rightTicks *= -1;
    }

    encoderSetPosition(LEFT_ENC, 0);
    encoderSetPosition(RIGHT_ENC, 0);

    while (encoderGetPosition(LEFT_ENC) < leftTicks
           || encoderGetPosition(RIGHT_ENC) < rightTicks)
    {
        if (encoderGetPosition(LEFT_ENC) >= leftTicks)
        {
            brake(LEFT_MOTOR);
        }

        if (encoderGetPosition(RIGHT_ENC) >= rightTicks)
        {
            brake(RIGHT_MOTOR);
        }
#if DEBUGGING
        lcdPrintHex(encoderGetPosition(1) >> 8, 1, 8);
        lcdPrintHex(encoderGetPosition(1), 1, 10);
        lcdPrintHex(encoderGetPosition(0) >> 8, 1, 12);
        lcdPrintHex(encoderGetPosition(0), 1, 14);
#endif
    }
    neutral();
}

/*
 * Move staight forward (positive) or straight back (negative)
 */
void moveStraight(int16_t ticks, uint8_t speed)
{
    tickWheels(ticks, ticks, speed);
}

/*
 * Brake one wheel, turn the other
 */
void tractorTurn(uint8_t speed, int8_t brads)
{
    if (brads > 0)
    {
        tickWheels(brads, 0, speed);
        delay(tractorOvershootDelay);
        tickWheels(brads - encoderGetPosition(LEFT_ENC), 0, speed);
        delay(tractorOvershootDelay); //***temporary?
    }
    else
    {
        brads *= -1;
        tickWheels(0, brads, speed);
        delay(tractorOvershootDelay);
        tickWheels(0, brads - encoderGetPosition(RIGHT_ENC), speed);
        delay(tractorOvershootDelay); //***temporary?
    }
}

/*
 * Turn on a dime (like a tank!)
 */
void tankTurn(uint8_t speed, int8_t brads)
{
    int8_t halfBrads = brads / 2;
    tickWheels(halfBrads, (-1 * halfBrads), speed);
    // Now we correct/prevent overshoot
    delay(TANK_OVERSHOOT_DELAY);
    if (brads < 0)
    {
        tickWheels(encoderGetPosition(LEFT_ENC) + halfBrads,
                   -1 * halfBrads - encoderGetPosition(RIGHT_ENC),
                   speed);
    }
    else
    {
        tickWheels(halfBrads - encoderGetPosition(LEFT_ENC),
                   encoderGetPosition(RIGHT_ENC) - halfBrads,
                   speed);
    }
}

void reverse(uint8_t motorSelect, uint8_t speed)
{
    switch (motorSelect)
    {
    case LEFT_MOTOR:
        sbi(MC_PORT, REVERSE_LEFT);
        cbi(MC_PORT, FORWARD_LEFT);
        PWM_LEFT(speed);
        break;
    case RIGHT_MOTOR:
        sbi(MC_PORT, REVERSE_RIGHT);
        cbi(MC_PORT, FORWARD_RIGHT);
        PWM_RIGHT(speed);
        break;
    case BOTH:
        // both motors reverse
        sbi(MC_PORT, REVERSE_LEFT);
        sbi(MC_PORT, REVERSE_RIGHT);
        cbi(MC_PORT, FORWARD_LEFT);
        cbi(MC_PORT, FORWARD_RIGHT);
        PWM_RIGHT(speed);
        PWM_LEFT(speed);
        break;
    }
}

void neutral(void)
{
    // both motors coast, disable
    PWM_RIGHT(0);
    PWM_LEFT(0);
}

//brake selected motor
//full brake assumed
void brake(uint8_t motorSelect)
{
    switch (motorSelect)
    {
    case LEFT_MOTOR:
        cbi(MC_PORT, REVERSE_LEFT);
        cbi(MC_PORT, FORWARD_LEFT);
        break;
    case RIGHT_MOTOR:
        cbi(MC_PORT, REVERSE_RIGHT);
        cbi(MC_PORT, FORWARD_RIGHT);
        break;
    case BOTH:
        // both motors reverse
        cbi(MC_PORT, REVERSE_LEFT);
        cbi(MC_PORT, REVERSE_RIGHT);
        cbi(MC_PORT, FORWARD_LEFT);
        cbi(MC_PORT, FORWARD_RIGHT);
        break;
    }
    PWM_RIGHT(MAX_BRAKE);
    PWM_LEFT(MAX_BRAKE);
}

void enableMotors(void)
{
    timer1PWMAOn();
    timer1PWMBOn();
}

void disableMotors(void)
{
    timer1PWMAOff();
    timer1PWMBOff();
}
