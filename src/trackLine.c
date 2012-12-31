/* trackLine.c
 *
 *    Line detection and tracking
 *
 */

#include "trackLine.h"


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

    lineStatsProcessed = TRUE;

    // Initialize wheel speeds to forward, zero pwm
    forward(BOTH, 0);
    PWM_LEFT(l_base);
    PWM_RIGHT(r_base);

    // Set Low Resolution
    lowResMode();
    // Downsample the image
    rprintf("DS %d %d\r", DS_X_LINE, DS_Y_LINE);
    // set virtual window
    rprintf("vw %d %d %d %d\r", VW_X1_LINE, VW_Y1_LINE, VW_X2_LINE, VW_Y2_LINE);

    // Line mode type 0, mode 2
    // "per row statistics in the tracked region" p.41
    rprintf("lm 0 2\r");
    // Output mask hides everything but, mean p.45
    rprintf("om 5 %d\r", LINE_STAT_MASK);

    // Turn poll mode off so line packets can be streamed
    rprintf("PM 0\r");

    // start the tracking (Track Color)
    rprintf("tc %d %d %d %d %d %d\r",
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


BOOL isGoodScan(u08 y)
{
    u08 i = 0;

    for (i = y; i < y + SCAN_WIDTH; i++)
    {
        if (lineStats[i][X_MEAN] == 0 ||
            lineStats[i][X_MIN] < VW_X1_LINE+5 ||
            lineStats[i][X_MAX] > VW_X2_LINE-5 ||
            lineStats[i][LINE_COUNT] > 9)
      {
         return FALSE;
      }
   }
   return TRUE;
}

BOOL isJunctionScan(u08 y)
{
    u08 i = 0;

    for (i = y; i < y + JUNC_SCAN_WIDTH; i++)
    {
        if (lineStats[i][X_MEAN] == 0
            ||
            (lineStats[i][X_MIN] > VW_X1_LINE + 10 &&
             lineStats[i][X_MAX] < VW_X2_LINE - 10)
            ||
            lineStats[i][LINE_COUNT] < 9)
        {
            return FALSE;
        }
    }
    return TRUE;
}

BOOL mayBeBall(u08 y)
{
    u08 i = 0;

    for (i = y; i < y + BALL_SCAN_WIDTH; i++)
    {
        if (lineStats[i][X_MEAN] != 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

void analyzeLineStats(void)
{
    u08 i;
    u08 y;
    u16 sum;

    u08 lineY1;
    u08 lineX1;
    u08 lineY2;
    u08 lineX2;

    double m;
    s08 lineOffset;
    static s16 lineSlope = 0;
    static s16 lastSlope = 0;
    s16 damping;

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
    lineSlope = (s16) (slopeCoef * m);
    damping = lineSlope - lastSlope;
    lineOffset = lineCenter - (m * (LINE_Y3 - lineY1) + lineX1);
    correction = slopeCoef * m +
                 offCoef * (lineCenter - (m * (LINE_Y3 - lineY1) + lineX1)) +
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

   lineStatsProcessed = TRUE;
}
