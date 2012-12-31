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
// helperFunctions.h
#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "caddy.h"
#include <stdint.h>
#include <stdbool.h>

void myDelay(uint16_t outerDelay);
void msDelay(uint16_t ms);
int8_t  getIndex(uint8_t value, const uint8_t array[], const uint8_t arraySize);

inline void initGoalList( void );
inline bool isInGoalList( uint8_t nodeNum );
inline void addToGoalList( uint8_t nodeNum );
bool removeFromGoalList( uint8_t nodeNum );
inline void printGoalList( void );
inline void copyList(uint8_t srcList[], uint8_t destList[], uint8_t numElements);
uint8_t getUpcomingBallNum( void );


#endif  // #ifndef
