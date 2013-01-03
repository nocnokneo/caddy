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
#ifndef SERVOS_H
#define SERVOS_H

// avr-libc
#include <stdint.h>

/**
 * @brief Servo to control the left/right swivel motion of the camera
 *
 * Allows the camera to look down corridors to the side
 *
 * Position is held by actively driving the servo.
 */
#define PAN    0

/**
 * @brief Servo to control the forward/back rocking motion of the camera
 *
 * Allows the camera to look down at the ground (e.g. for line tracking) and
 * to look forward to see if balls lie in the path ahead.
 *
 * The tilt also controls the bonus ball scooping cup since the cup and the
 * camera are on the same rigid assembly.
 *
 * Position is held by actively driving the servo.
 */
#define TILT   1

/**
 * @brief Servo to control the boom arm
 *
 * The boom moves the long arm which holds the entire camera/scoop/pan/tilt
 * assembly.
 *
 * This is used for the bonus ball pickup maneuver as well as positioning of
 * the camera.
 *
 * Position is held mechanically (servo can be passive after moving to
 * position)
 */
#define BOOM   2

/**
 * @brief Servo to control the lift and scooping blade
 *
 * The lift servo, with just simple rotational actuation, drives the complex
 * mechanical motion of lift assembly which:
 *  - Opens/closes the ground ball scooping blade
 *  - Lifts captured ground balls into the hopper
 *  - Aligns the robot with the corner of a wall using the 90 degree "V" shape
 *    of the front of the lift (used as the first step of the bonus ball
 *    pickup maneuver)
 *
 * Position is held mechanically (servo can be passive after moving to
 * position)
 */
#define LIFT   3

/**
 * @brief Servo to control the hopper door
 *
 * Opens and closes hopper door (e.g. to release the balls into the corral at
 * the end of the Roborodentia course)
 *
 * Position is held mechanically (servo can be passive after moving to
 * position)
 */
#define DOOR   4

// Servo positions
#define PAN_CENTER         128 //133
#define MAX_PAN_LEFT       50
#define MAX_PAN_RIGHT      195

#define TILT_BB_GRAB       133
#define TILT_VERT          128   ///< requires boom to be MAX_BOOM_UP
#define TILT_LOOKUP        186
#define TILT_BACK          MAX_TILT_BACK
#define TILT_FORWARD       MAX_TILT_FORWARD
#define MAX_TILT_BACK      195
#define MAX_TILT_FORWARD   70

#define BOOM_UP            MAX_BOOM_UP
#define BOOM_BB_GRAB       183   ///< cup 2.32 inches off ground
#define MAX_BOOM_UP        45
#define MAX_BOOM_DOWN      148

#define LIFT_OPEN          MAX_LIFT_OPEN
#define LIFT_UP            MAX_LIFT_UP
#define LIFT_CORRAL        150   ///< Lift position needed to release balls into corral
#define LIFT_BB_READY      114   ///< Places the "V" of the lift 3 inches off ground, ready for bonus ball grabbing maneuver
#define MAX_LIFT_OPEN      183   ///< Mechanical limit in which the ground ball blade is fully open
#define MAX_LIFT_UP        74    ///< @todo: increase if lift hits boom on reset

#define DOOR_CLOSED        MAX_DOOR_CLOSED
#define DOOR_OPEN          MAX_DOOR_OPEN
#define MAX_DOOR_CLOSED    71    ///< Close door _just_ to the point of touching
#define MAX_DOOR_OPEN      200   ///< Mechanical limit of the door lever arm

void moveServosToStart(void);
void grabBonusBall(void);
void moveServo(uint8_t servoNum, uint8_t servoPos);
void setServo(uint8_t servoNum, uint8_t servoPos);
void disableServo(uint8_t servoNum);

#endif  // #ifndef
