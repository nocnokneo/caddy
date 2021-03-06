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
#include "servos.h"

// AVRLIB
#include "rprintf.h"

// avr-libc
#include <stdint.h>

void setServo(uint8_t servoNum, uint8_t servoPos)
{
    rprintf("sv %d %d\r", servoNum, servoPos);
}

void disableServo(uint8_t servoNum)
{
    rprintf("so %d 0\r", servoNum);
}
