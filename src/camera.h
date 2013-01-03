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
#ifndef CAMERA_H_
#define CAMERA_H_

#include "caddy.h"
#include <stdint.h>

// Packet types
#define NEW_PACKET   0
#define FE_RCV       1
#define T_RCV        2

#define hiResMode()  rprintf("HR 1\r")
#define lowResMode() rprintf("HR 0\r")

/**
 * @brief Initialize the UART for communicating with the CMUcam
 */
inline void cmuCamInit(void);

/**
 * @brief Optimize the white balance for current conditions
 *
 * Turn auto-white balance on, give it time to settle, then turn auto-white
 * balance off.
 *
 * @sa CMUcam2 manual p.31
 */
inline void cameraWhiteBalance( void );

inline void resetCamera( void );
inline void streamModeOff( void );

/**
 * @brief Constrain field of view used for subsequent image processing commands
 *
 * @sa CMUcam2 manual p.55
 */
inline void setVirtualWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif // #ifndef CAMERA_H_
