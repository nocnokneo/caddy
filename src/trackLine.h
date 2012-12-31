// trackLine.h
#ifndef TRACKLINE_H
#define TRACKLINE_H

#include "caddy.h"



// Track the BLACK line on white background
#define LINE_RMIN    16
#define LINE_GMIN    16
#define LINE_BMIN    16
#define LINE_RMAX    50
#define LINE_GMAX    50
#define LINE_BMAX    40


#define DS_X_LINE             1
#define DS_Y_LINE             4
#define VW_X1_LINE            10
#define VW_Y1_LINE            1
#define VW_X2_LINE            77
#define VW_Y2_LINE            35
#define VW_X_SIZE_LINE        VW_X2_LINE-VW_X1_LINE+1
#define VW_Y_SIZE_LINE        VW_Y2_LINE-VW_Y1_LINE+1

#define LINE_STATS_ROWS       VW_Y_SIZE_LINE
#define LINE_STATS_COLS       4    // must correspond to bits in LINE_STAT_MASK
#define LINE_STAT_MASK        0Xf  // Sends the mean, min, max, and pixel count
#define X_MEAN                0
#define X_MIN                 1
#define X_MAX                 2
#define LINE_COUNT            3
#define SCAN_WIDTH            4


#define LINE_Y_MAX_NDX        (LINE_STATS_ROWS - SCAN_WIDTH - 1)
#define JUNC_Y_MAX_NDX        (LINE_STATS_ROWS - JUNC_SCAN_WIDTH - 1)
#define BALL_Y_MAX_NDX        (LINE_STATS_ROWS - BALL_SCAN_WIDTH - 1)

#define LINE_Y3               49

#define JUNC_SCAN_WIDTH       1
#define BALL_SCAN_WIDTH       7



void adjustPWM( void );

void trackLineInit(void);
void restartLineMode(void);

void analyzeLineStats(void);
BOOL isGoodScan(u08 y);
BOOL isJunctionScan(u08 y);
BOOL mayBeBallScan(u08 y);

void printPacket(void);

s16 correction;
s08 junctionY;
s08 possibleBallY;

volatile u08 lineStats[LINE_STATS_ROWS][LINE_STATS_COLS];
volatile BOOL lineStatsProcessed;



#endif  // #ifndef
