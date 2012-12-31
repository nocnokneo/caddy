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
// nodeList.h
#ifndef NODELIST_H
#define NODELIST_H

#include "caddy.h"
#include <stdint.h>
#include <stdbool.h>

#define NUM_NODES       43        // number of nodes in arena

#define BALL_NODE_MIN   1         // ball node number range
#define BALL_NODE_MAX   20
#define JUNCTION_MIN    21        // junction node number range
#define JUNCTION_MAX    41

#define NUM_BALL_NODES  (BALL_NODE_MAX - BALL_NODE_MAX + 1)


#define MAX_ADJ_NODES   3         // max. nodes that can be adjacent to one node
#define N_WEST          -41       // direction of north west in binary radians (brads)
#define S_EAST          87        // direction of south east in binary radians (brads)

#define BONUS_BALL_1    24
#define BONUS_BALL_2    30
#define SENSOR_NODE     37

#define BB1_HEADING     32
#define BB2_HEADING     -96

#define NUM_FIXED_GOALS    3
#define NUM_RANDOM_GOALS   3
#define NUM_GOALS          NUM_FIXED_GOALS + NUM_RANDOM_GOALS

typedef struct nodeStruct
{
    uint8_t numAdjNodes;                  // number of nodes adjacent to this node
    uint8_t adjNodes[MAX_ADJ_NODES];      // node numbers of adjacent nodes
    uint8_t adjCosts[MAX_ADJ_NODES];      // distances to adjacent nodes (6 inches increments)
    int8_t adjHeadings[MAX_ADJ_NODES];   // directions towards adjacent nodes (brads)
} NODE;


inline bool isJunction( uint8_t nodeNum );
uint8_t getCostToNode(NODE *node, uint8_t nodeNum);
uint8_t getNodeAtHeading(NODE *node, int8_t heading);
inline bool isBallNode( uint8_t nodeNum );
void getNode( uint8_t nodeNum, NODE *node );


#endif  // #ifndef
