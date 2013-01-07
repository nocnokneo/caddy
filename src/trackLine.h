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
 * @file
 * @brief Line detection and PID tracking using CMUcam2
 */
#ifndef TRACKLINE_H_
#define TRACKLINE_H_

#include <stdint.h>
#include <stdbool.h>

#define DS_X_LINE             1
#define DS_Y_LINE             4
#define VW_X1_LINE            10
#define VW_Y1_LINE            1
#define VW_X2_LINE            77
#define VW_Y2_LINE            35
#define VW_X_SIZE_LINE        (VW_X2_LINE - VW_X1_LINE + 1)
#define VW_Y_SIZE_LINE        (VW_Y2_LINE - VW_Y1_LINE + 1)

#define LINE_STATS_ROWS       VW_Y_SIZE_LINE
#define LINE_STATS_COLS       4    // must correspond to bits in LINE_STAT_MASK

void adjustPWM( void );

void trackLineInit(void);
void restartLineMode(void);

void analyzeLineStats(void);
bool isGoodScan(uint8_t y);
bool isJunctionScan(uint8_t y);
bool mayBeBallScan(uint8_t y);

void printPacket(void);

extern int8_t junctionY;

volatile uint8_t lineStats[LINE_STATS_ROWS][LINE_STATS_COLS];
volatile bool lineStatsProcessed;

#endif // #ifndef TRACKLINE_H_
