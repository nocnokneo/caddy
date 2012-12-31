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
// junctionCode.h
#ifndef JUNCTIONCODE_H
#define JUNCTIONCODE_H

#include "caddy.h"
#include <stdint.h>
#include <stdbool.h>

#define BALL_DIST       0
#define BALL_NODE_NUM   1

extern bool checkedList[];
extern uint8_t goalList[];

uint8_t goalListSize;
uint8_t numKnownGoals;

void junctionCode(void);
bool standardBallSearch( void );
inline bool nodeCode0( void );
inline bool nodeCode22( void );
inline bool diagNodeCode(void);
inline bool nodeCode37( void );


#endif
