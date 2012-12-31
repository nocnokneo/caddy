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
// botCntrl.h
#ifndef BOTCNTRL_H
#define BOTCNTRL_H

#include "caddy.h"


#define BEAM_IGNORE_COUNT      6
#define CORRAL_COUNT           3
#define LIFT_DONE_COUNT        8


// --- GLOBALS --- //
extern u08 botNode;
extern s08 botHeading;
extern u08 numUnreachedGoals;
BOOL liftDown;
u08 upComingBallNum;

// --- Prototypes --- //
inline void runBot( void );
inline void initBotGlobals(void);
inline BOOL positionBot(void);
inline s08 getNextHeading(u08 nextBotNode);
inline void moveToJunction( u08 numJunctions, BOOL justTurned );
void bbSequence( void );
void nestSequence( void );
inline void bbPositioning( s08 bbHeading, s08 nextHeading );


#endif  // #ifndef
