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
#include "helperFunctions.h"

// AVRLIB
#include "timer.h"

void myDelay(uint16_t outerDelay)
{
    uint16_t i, j;
    for (i = 0; i < outerDelay; i++)
        for (j = 0; j < UINT16_MAX; j++) ;
}

void msDelay(uint16_t ms)
{
    uint16_t i;
    for (i = 0; i < ms; i++)
    {
        delay(1000); // 1000 microseconds
    }
}

int8_t findValue(const uint8_t *array, const uint8_t arraySize, uint8_t value)
{
    uint8_t i = 0;
    while (i < arraySize)
    {
        if (array[i] == value)
            return i;
        i++;
    }
    return -1;
}
