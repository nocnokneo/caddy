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

#define BALL_DIST       0
#define BALL_NODE_NUM   1

extern BOOL checkedList[];
extern u08 goalList[];

u08 goalListSize;
u08 numKnownGoals;

void junctionCode(void);
BOOL standardBallSearch( void );
inline BOOL nodeCode0( void );
inline BOOL nodeCode22( void );
inline BOOL diagNodeCode(void);
inline BOOL nodeCode37( void );


#endif
