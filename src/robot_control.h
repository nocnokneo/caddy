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
 *
 * \sa \ref problem_summary
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

/**
 * @brief Run the Roborodentia course from start to finish
 *
 * Returns once all balls have been collected and placed in the nest.
 */
inline void runRoborodentiaCourse(void);

/**
 * @brief Turn bot, if necessary, at junctions and ball nodes
 *
 * Maintains (owns) botHeading global variable. Performs bonus ball pickup
 * liftDown actions.
 *
 * @return True when bot just turned. (Used to tell moveToJunction to
 * begin looking for next junction immediately.)
 *
 * @pre The camera is NOT streaming
 */
inline bool positionBot(void);
inline void moveToJunction(uint8_t numJunctions, bool justTurned);
void bbSequence(void);

/**
 * @brief Sequence of actions to peform once the nest is reached
 *
 * Main purpose is to release the balls from the hopper.
 */
void nestSequence(void);

/**
 * @brief Orients Caddy to grab a bonus ball, grabs the ball, and reorients
 * for the next node
 *
 * @param[in] bbHeading    Heading Caddy must have for bonus ball pickup
 * @param[in] nextHeading  Heading Caddy must have after bonus ball pickup
 */
inline void bonusBallPickUpManeuver(int8_t bbHeading, int8_t nextHeading);

#endif // #ifndef BOTCNTRL_H_
