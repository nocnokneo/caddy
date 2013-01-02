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
#include <stdbool.h>

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

inline void initGoalList( void );
inline bool isInGoalList( uint8_t nodeNum );
inline void addToGoalList( uint8_t nodeNum );
bool removeFromGoalList( uint8_t nodeNum );
inline void printGoalList( void );
inline void copyList(uint8_t srcList[], uint8_t destList[], uint8_t numElements);
uint8_t getUpcomingBallNum( void );

#endif // #ifndef HELPERFUNCTIONS_H_
