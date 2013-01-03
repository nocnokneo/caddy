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
 * @brief Simple tracking Roborodentia objects of interest by color
 *
 * Uses the CMUcam2 color blob tracking to:
 *   - Identify ball and estimate distance from robot
 *   - Identify nest
 */
#ifndef TRACKCOLOR_H_
#define TRACKCOLOR_H_

#include <stdint.h>
#include <stdbool.h>

#define LOOK_RIGHT   1
#define LOOK_LEFT    -1
#define LOOK_UP      0

#define MX_NDX            0
#define MY_NDX            1
#define X1_NDX            2
#define Y1_NDX            3
#define X2_NDX            4
#define Y2_NDX            5
#define PIXEL_CNT_NDX     6
#define CONFIDENCE_NDX    7

#define NUM_COLOR_STATS    8

#define PAN_SEEK_OFFSET    66

// --- GLOBAL VARIABLES --- //
volatile bool colorStatsProcessed;
bool inSeekPosition;

// --- PROTOTYPES --- //
void trackColorInit(int8_t dir);
uint8_t getBallY( void );
bool seeBall( void );
bool cameraSeekLeft( uint8_t uncheckedBalls[][2], uint8_t numUncheckedBalls );
bool cameraSeekRight( uint8_t uncheckedBalls[][2], uint8_t numUncheckedBalls );

#endif // #ifndef TRACKCOLOR_H_
