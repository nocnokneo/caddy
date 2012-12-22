// testCode.h
#ifndef TESTCODE_H
#define TESTCODE_H

#include "caddy.h"


// --- CONSTANTS --- //
#define DEFAULT_TEST_MODE       UPDATE_PATH_TEST_MODE

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
void toggleTestMode( s08 i );
void runFixedPath( void );
void baseSpeedTest( void );
void lineStatsTest( void );
void seeBallTest( void );
void seekBallTest( void );
void encoderTest( void );
inline void refreshColorStats( void );
inline void clearColorStats( void );
inline void labelColorStats( void );
void updatePathTest( void );


#endif  // #ifndef
