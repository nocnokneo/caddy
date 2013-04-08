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
#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

// avr-libc
#include <stdint.h>

// Number of elements in a 1-dimensional array
#define ELEMENTSOF(x)  (sizeof(x)/sizeof((x)[0]))

void myDelay(uint16_t outerDelay);
void msDelay(uint16_t ms);

/**
 * @brief Finds the first occurrence of a value in a given array
 *
 * @param[in] array      Array to search
 * @param[in] arraySize  Number of elements in array
 * @param[in] value      Value to find
 *
 * @return Array index of the first occurrence of value, if found, otherwise -1
 */
int8_t findValue(const uint8_t *array, const uint8_t arraySize, uint8_t value);

/**
 * @brief Print an error message and halt the robot
 *
 * @note: Does not return
 */
void fatalError(const char *errorStr1, const char *errorStr2);

#endif // #ifndef HELPERFUNCTIONS_H_
