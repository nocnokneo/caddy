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
/** @file */
#include "camera.h"
#include <stdbool.h>

#define CMU_BAUD 38400

static uint8_t mode;
static uint16_t byteNum;

void packetRcv( uint8_t c );
inline void lineMode2Rcv( uint8_t c );
inline void trackColorRcv( uint8_t c );

inline void cmuCamInit(void)
{
    uartInit();
    uartSetBaudRate(CMU_BAUD);
    uartSetRxHandler(packetRcv);
    rprintfInit(uartSendByte);
}

inline void cameraWhiteBalance()
{
    // turn auto white balance on
#if DEBUGGING
    lcdWriteStr("white Bal ", 0, 6);
#endif
    rprintf("CR 18 44\r");
    myDelay(200);
    // turn auto white balance off
    rprintf("CR 18 40\r");
}

inline void resetCamera( void )
{
    mode = NEW_PACKET;
    byteNum = 0;

    rprintf("RM 3\r");
}

void packetRcv(uint8_t c)
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


inline void lineMode2Rcv(uint8_t c)
{
    if (c == 0xfd)
    {
        lineStatsProcessed = false;
        byteNum = 0;
    }
    else
    {
        lineStats[(byteNum - 1) / LINE_STATS_COLS]
                 [(byteNum - 1) % LINE_STATS_COLS] = c;
        byteNum++;
    }
}


inline void trackColorRcv(uint8_t c)
{
    lineStats[0][byteNum] = c;
    byteNum++;

    if (byteNum >= NUM_COLOR_STATS)
    {
        colorStatsProcessed = false;
    }
}


inline void streamModeOff( void )
{
    rprintf("\r\r"); // add an extra return as recommended by CMUcam manual
    msDelay(32);     // wait for streaming to stop ( 16ms delay ok )
}


inline void setVirtualWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    rprintf("VW %d %d %d %d\r", x1, y1, x2, y2);
}
