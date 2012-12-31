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

void myDelay(u16 outerDelay);
void msDelay(u16 ms);
s08  getIndex(u08 value, const u08 array[], const u08 arraySize);

inline void initGoalList( void );
inline BOOL isInGoalList( u08 nodeNum );
inline void addToGoalList( u08 nodeNum );
BOOL removeFromGoalList( u08 nodeNum );
inline void printGoalList( void );
inline void copyList(u08 srcList[], u08 destList[], u08 numElements);
u08 getUpcomingBallNum( void );


#endif  // #ifndef
