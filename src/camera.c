/* camera.c
 *
 *    functions for changing settings for CMUcam2
 *    packet handler
 *
 */

#include "camera.h"


inline void cameraWhiteBal()
{
    // turn white balance on p.31
#if DEBUGGING
    lcdWriteStr("white Bal ", 0, 6);
#endif
    rprintf("cr 18 44\r");
    myDelay(200);
    // turn white balance off p.31
    rprintf("cr 18 40\r");
}


inline void resetCamera( void )
{
    mode = NEW_PACKET;
    byteNum = 0;

    rprintf("RM 3\r");
}

void packetRcv(u08 c)
{
    if (c == 0xff)
    {
        mode = NEW_PACKET;
        byteNum = 0;
    }
    else
    {
        switch (mode)
        {
        case NEW_PACKET:
            switch (c)
            {
            case 0xfe:
                mode = FE_RCV;
                break;
            case 'T':
                mode = T_RCV;
                break;
            default:
                break;
            }
            break;
        case FE_RCV:
            lineMode2Rcv(c);
            if (c == 0xfd)
            {
                mode = NEW_PACKET;
            }
            break;
        case T_RCV:
            trackColorRcv(c);
            break;
        }
    }
}


inline void lineMode2Rcv(u08 c)
{
    if (c == 0xfd)
    {
        lineStatsProcessed = FALSE;
        byteNum = 0;
    }
    else
    {
        lineStats[(byteNum - 1) / LINE_STATS_COLS]
                 [(byteNum - 1) % LINE_STATS_COLS] = c;
        byteNum++;
    }
}


inline void trackColorRcv(u08 c)
{
    lineStats[0][byteNum] = c;
    byteNum++;

    if (byteNum >= NUM_COLOR_STATS)
    {
        colorStatsProcessed = FALSE;
    }
}


inline void streamModeOff( void )
{
    rprintf("\r\r"); // add an extra return as recommended by CMUcam manual
    msDelay(32);     // wait for streaming to stop ( 16ms delay ok )
}


inline void setVW(u08 x1, u08 y1, u08 x2, u08 y2)
{
    rprintf("VW %d %d %d %d\r", x1, y1, x2, y2);
}
