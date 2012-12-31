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
// camera.h

#ifndef CAMERA_H
#define CAMERA_H

#include "caddy.h"
#define CMU_BAUD 38400
// Packet types
#define NEW_PACKET   0
#define FE_RCV       1
#define T_RCV        2
#define ACK_RCV      3
#define NCK_RCV      4
#define ASCII_RCV    5


#define hiResMode()  rprintf("hr 1\r")
#define lowResMode() rprintf("hr 0\r")

u08 mode;
u16 byteNum;

inline void cameraWhiteBal( void );
inline void resetCamera( void );
void packetRcv( u08 c );
inline void lineMode2Rcv( u08 c );
inline void trackColorRcv( u08 c );
inline void streamModeOff( void );
inline void setVW(u08 x1, u08 y1, u08 x2, u08 y2);
//inline void downSample(u08 x, u08 y);


#endif  /* #ifndef CAMERA_H */
