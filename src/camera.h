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
/** @file
 * @brief Interface to the CMUcam vision system
 */
#ifndef CAMERA_H_
#define CAMERA_H_

#include <stdint.h>

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

/**
 * @brief Reset the packet receiving state and put the camera into raw send mode
 *
 * @sa CMUcam2 manual p.48
 */
inline void initCamera( void );

/**
 * @brief Stop the CMUcam from streaming data
 *
 * @sa CMUcam2 manual p.30
 */
inline void cameraStreamingOff( void );

/**
 * @brief Constrain field of view used for subsequent image processing commands
 *
 * @sa CMUcam2 manual p.55
 */
inline void setVirtualWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

/**
 * @brief Set the camera to 176x255 resolution
 *
 * @note This resolution is @em truncated from 176x287
 */
inline void cameraHighResMode(void);

/**
 * @brief Set the camera to 88x143 resolution
 */
inline void cameraLowResMode(void);

#endif // #ifndef CAMERA_H_
