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
#include <stdint.h>

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

uint8_t mode;
uint16_t byteNum;

inline void cameraWhiteBal( void );
inline void resetCamera( void );
void packetRcv( uint8_t c );
inline void lineMode2Rcv( uint8_t c );
inline void trackColorRcv( uint8_t c );
inline void streamModeOff( void );
inline void setVW(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
//inline void downSample(uint8_t x, uint8_t y);


#endif  /* #ifndef CAMERA_H */
