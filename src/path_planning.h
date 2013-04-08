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
 * @brief AI navigation algorithm
 */
#ifndef UPDATEPATH_H_
#define UPDATEPATH_H_

#include <stdint.h>
#include <stdbool.h>

/** Worst case number of nodes to complete the course */
#define MAX_PATH_LIST_SIZE 70

/** List of nodes to be visited. Updated as new goals are discovered. */
extern uint8_t pathList[];
/** Index into @ref pathList corresponding to the robot's current position */
extern uint8_t pathListIndex;

uint8_t updatePath( void );
inline bool isInGoalList( uint8_t nodeNum );
inline void addToGoalList( uint8_t nodeNum );
bool removeFromGoalList( uint8_t nodeNum );
inline void adjustNumKnownGoals( int8_t adjustment );
inline bool allGoalsFound(void);
inline void printGoalList( void );
uint8_t getNextBallNodeNum( void );
inline int8_t getNextHeading(void);

#endif  // #ifndef UPDATEPATH_H_
