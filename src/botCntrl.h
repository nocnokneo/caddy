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
/**
 * @file
 * @brief High-level logic controlling Caddy's actions
 */
#ifndef BOTCNTRL_H_
#define BOTCNTRL_H_

// avr-libc
#include <stdint.h>
#include <stdbool.h>

// Global variables
extern uint8_t botNode;
extern int8_t botHeading;
extern uint8_t numUnreachedGoals;

inline void runRoborodentiaCourse(void);
inline void initBotGlobals(void);
inline bool positionBot(void);
inline void moveToJunction(uint8_t numJunctions, bool justTurned);
void bbSequence(void);
void nestSequence(void);
inline void bbPositioning(int8_t bbHeading, int8_t nextHeading);

#endif // #ifndef BOTCNTRL_H_
