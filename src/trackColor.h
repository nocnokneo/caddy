#ifndef TRACKCOLOR_H
#define TRACKCOLOR_H

#include "caddy.h"

// --- CONSTANTS --- //
#define LOOK_RIGHT   1
#define LOOK_LEFT    -1
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

#define PAN_SEEK_OFFSET   40  // *** placeholder -> needs to be determined!! ***

struct seekParams {
   u08 pan;
   u08 tilt;
   u08 x1; 
   u08 y1;
   u08 x2;
   u08 y2;
};

// --- GLOBAL VARIABLES --- //
volatile BOOL colorStatsProcessed;

// --- PROTOTYPES --- //
void trackColorInit(void);
u08 getBallY( void );
//BOOL cameraSeeksBall( u08 ballDist, s08 dir); 
BOOL cameraSeeksBall(u08 pan, u08 tilt, u08 x1, u08 y1, u08 x2, u08 y2);
BOOL cameraSeekLeft( u08 uncheckedBalls[][2], u08 numUncheckedBalls );
BOOL cameraSeekRight( u08 uncheckedBalls[][2], u08 numUncheckedBalls );
u08 xToDist(u08 y);
u08 distToX(u08 dist);

#endif  // #ifndef
