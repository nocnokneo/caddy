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
#ifndef TRACKCOLOR_H
#define TRACKCOLOR_H

#include "caddy.h"

// --- CONSTANTS --- //
#define LOOK_RIGHT   1
#define LOOK_LEFT    -1
#define LOOK_UP      0

#define CAM_HEIGHT   10  // inches
#define X_PIXELS_PER_DEG   (174/44)
#define VW_X1_SEEK
#define VW_Y1_SEEK
#define VW_X2_SEEK
#define VW_Y2_SEEK

// Track the RED ball on black/white background
#define BALL_RMIN    150
#define BALL_RMAX    240
#define BALL_GMIN    16
#define BALL_GMAX    60
#define BALL_BMIN    16
#define BALL_BMAX    50

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
volatile BOOL colorStatsProcessed;
BOOL inSeekPosition;

// --- PROTOTYPES --- //
void trackColorInit(s08 dir);
u08 getBallY( void );
BOOL seeBall( void );
//BOOL cameraSeeksBall( u08 ballDist, s08 dir);
BOOL cameraSeekLeft( u08 uncheckedBalls[][2], u08 numUncheckedBalls );
//BOOL cameraSeekLeft( void );
BOOL cameraSeekRight( u08 uncheckedBalls[][2], u08 numUncheckedBalls );
u08 distToPix( u08 distance );


#endif  // #ifndef
