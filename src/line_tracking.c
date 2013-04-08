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
#include "line_tracking.h"
#include "motor_control.h"
#include "camera.h"
#include "tweak_data.h"
#include "tether_ui.h"
#include "lcd_16x2.h"

// AVRLIB
#include "rprintf.h"

// avr-libc
#include <stdint.h>
#include <stdbool.h>

// Track BLACK line on WHITE background
#define LINE_RMIN    16
#define LINE_GMIN    16
#define LINE_BMIN    16
#define LINE_RMAX    50
#define LINE_GMAX    50
#define LINE_BMAX    40

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

// Global variables
volatile uint8_t lineStats[LINE_STATS_ROWS][LINE_STATS_COLS];
volatile bool lineStatsProcessed;

int8_t junctionY;
static int16_t correction;
static int8_t possibleBallY;


void adjustPWM( void )
{
    PWM_LEFT(MIN(MAX(l_base - correction, BASE_MIN), BASE_MAX));
    PWM_RIGHT(MIN(MAX(r_base + correction, BASE_MIN), BASE_MAX));

#if DEBUGGING
    if (lcdMode == LINE_LCD_MODE)
    {
        lcdPrintHex(MIN(MAX(l_base - correction, BASE_MIN), BASE_MAX), 1, 11);
        lcdPrintHex(MIN(MAX(r_base + correction, BASE_MIN), BASE_MAX), 1, 14);
    }
#endif
}

void trackLineInit(void)
{
#if DEBUGGING
    // Clear LCD
    if (lcdMode == LINE_LCD_MODE)
    {
        lcdWriteStr("                ", 0, 0);
        lcdWriteStr("                ", 1, 0);
    }
#endif

    // Assume we start on the center of the line and no junction in view
    correction = 0;
    junctionY = 0;

    lineStatsProcessed = true;

    // Initialize wheel speeds to forward, zero pwm
    forward(BOTH_MOTORS, 0);
    PWM_LEFT(l_base);
    PWM_RIGHT(r_base);

    // Set Low Resolution
    cameraLowResMode();
    // Downsample the image
    rprintf("DS %d %d\r", DS_X_LINE, DS_Y_LINE);
    // set virtual window
    rprintf("VW %d %d %d %d\r", VW_X1_LINE, VW_Y1_LINE, VW_X2_LINE, VW_Y2_LINE);

    // Line mode type 0, mode 2
    // "per row statistics in the tracked region" p.41
    rprintf("LM 0 2\r");
    // Output mask hides everything but, mean p.45
    rprintf("OM 5 %d\r", LINE_STAT_MASK);

    // Turn poll mode off so line packets can be streamed
    rprintf("PM 0\r");

    // Start the tracking (Track Color)
    rprintf("TC %d %d %d %d %d %d\r",
            LINE_RMIN, LINE_RMAX, LINE_GMIN,
            LINE_GMAX, LINE_BMIN, LINE_GMAX);

}

void restartLineMode( void )
{
    rprintf("lm 0 2\r");
    rprintf("PM 0\r");
    rprintf("tc %d %d %d %d %d %d\r",
            LINE_RMIN, LINE_RMAX, LINE_GMIN,
            LINE_GMAX, LINE_BMIN, LINE_GMAX);
}


bool isGoodScan(uint8_t y)
{
    uint8_t i = 0;

    for (i = y; i < y + SCAN_WIDTH; i++)
    {
        if (lineStats[i][X_MEAN] == 0 ||
            lineStats[i][X_MIN] < VW_X1_LINE+5 ||
            lineStats[i][X_MAX] > VW_X2_LINE-5 ||
            lineStats[i][LINE_COUNT] > 9)
      {
         return false;
      }
   }
   return true;
}

bool isJunctionScan(uint8_t y)
{
    uint8_t i = 0;

    for (i = y; i < y + JUNC_SCAN_WIDTH; i++)
    {
        if (lineStats[i][X_MEAN] == 0
            ||
            (lineStats[i][X_MIN] > VW_X1_LINE + 10 &&
             lineStats[i][X_MAX] < VW_X2_LINE - 10)
            ||
            lineStats[i][LINE_COUNT] < 9)
        {
            return false;
        }
    }
    return true;
}

bool mayBeBall(uint8_t y)
{
    uint8_t i = 0;

    for (i = y; i < y + BALL_SCAN_WIDTH; i++)
    {
        if (lineStats[i][X_MEAN] != 0)
        {
            return false;
        }
    }
    return true;
}

void analyzeLineStats(void)
{
    uint8_t i;
    uint8_t y;
    uint16_t sum;

    uint8_t lineY1;
    uint8_t lineX1;
    uint8_t lineY2;
    uint8_t lineX2;

    double m;
    int8_t lineOffset;
    static int16_t lineSlope = 0;
    static int16_t lastSlope = 0;
    int16_t damping;

    // find X1 and the row that corresponds to Y1
    sum = 0;
    y = 0;
    while (y < LINE_Y_MAX_NDX && !isGoodScan(y))
    {
        y++;
    }
    lineY1 = y;
    for (i = y; i < y + SCAN_WIDTH; i++)
    {
        sum += lineStats[i][X_MEAN];
    }
    lineX1 = sum / SCAN_WIDTH;

    // find X2 and the row that corresponds to Y2
    sum = 0;
    y = LINE_Y_MAX_NDX;
    while (y > lineY1 && !isGoodScan(y))
    {
        y--;
    }
    lineY2 = y;
    for (i = y; i < y + SCAN_WIDTH; i++)
    {
        sum += lineStats[i][X_MEAN];
    }
    lineX2 = sum / SCAN_WIDTH;

    // look for row where junction exists
    y = 0;
    while (y <= JUNC_Y_MAX_NDX && !isJunctionScan(y))
    {
        y++;
    }
    if (y > JUNC_Y_MAX_NDX)
    {
        junctionY = -VW_Y1_LINE;
    }
    else
    {
        junctionY = y;
    }

    // look for row where ball may exist
    y = 0;
    while (y <= BALL_Y_MAX_NDX && !mayBeBall(y))
    {
        y++;
    }
    if (y > BALL_Y_MAX_NDX)
    {
        possibleBallY = -VW_Y1_LINE;
    }
    else
    {
        possibleBallY = y;
    }

    // Correlate zero-based row numbers to Y values
    lineY1 += VW_Y1_LINE;
    lineY2 += VW_Y1_LINE;
    junctionY += VW_Y1_LINE;
    possibleBallY += VW_Y1_LINE;

    // calculate correction using line position and (if damping) rate of change
    m = (double) (lineX2 - lineX1) / (double) (lineY2 - lineY1);
    lastSlope = lineSlope;
    lineSlope = (int16_t) (slopeCoef * m);
    damping = lineSlope - lastSlope;
    lineOffset = lineCenter - (m * (LINE_Y3 - lineY1) + lineX1);
    correction = slopeCoef * m +
                 offCoef * lineOffset +
                 dampCoef * damping;

#if DEBUGGING
   if( lcdMode == LINE_LCD_MODE )
   {
      lcdPrintHex(lineY1, 0, 0);
      lcdPrintHex(lineX1, 0, 3);
      lcdPrintHex(lineY2, 1, 0);
      lcdPrintHex(lineX2, 1, 3);
      lcdPrintHex(damping, 0, 6);
      lcdPrintHex(lineSlope>>8, 0, 9);
      lcdPrintHex(lineSlope, 0, 11);
      lcdPrintHex(lineOffset, 0, 14);

      lcdPrintHex(junctionY, 1, 6);
   }
#endif

   lineStatsProcessed = true;
}
