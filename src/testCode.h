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
// testCode.h
#ifndef TESTCODE_H
#define TESTCODE_H

#include "caddy.h"
#include <stdint.h>


// --- CONSTANTS --- //
#define DEFAULT_TEST_MODE       SEEK_BALL_TEST_MODE

#define RUN_BOT_TEST_MODE       0
#define BB_TEST_MODE            1
#define GB_TEST_MODE            2
#define LINE_STATS_TEST_MODE    3
#define SEE_BALL_TEST_MODE      4
#define SEEK_BALL_TEST_MODE     5
#define NEST_TEST_MODE          6
#define FIXED_PATH_TEST_MODE    7
#define ZIG_ZAG_TEST_MODE       8
#define UPDATE_PATH_TEST_MODE   9
#define DIAG_TEST_MODE          10
#define NODE_31_TEST_MODE       11

#define NUM_TEST_MODES          12

// --- PROTOTYPES --- //
void runTest( void );
void toggleTestMode( int8_t i );
void runFixedPath( void );
void seekBallTest( void );
inline void refreshColorStats( void );
inline void clearColorStats( void );
inline void labelColorStats( void );
void updatePathTest( void );

void printPathList( void );


#endif  // #ifndef
