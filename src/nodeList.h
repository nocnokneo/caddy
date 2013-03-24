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
 * @brief Course defined by a connected grid of nodes
 *
 * Conserves SRAM by storing graph of arena in FLASH memory.
 * See doc directory for image of arena with node numbers.
 *
 * - Nodes are represented by numbers:
 *   - Nodes 0 and 42 are terminal nodes
 *   - Nodes 1-20 are ball nodes
 *   - Nodes 21-41 are junctions
 * - Distance resolution is 6 inches.
 * -Direction is measured in binary radians or brads. (see www.urcp.com)
 *
 * Version History:
 * 2/17/05 - Created by Logan
 * 2/21/05 - Checked by Logan, Scott, and Patrick
 *         - Changed syntax for Atmel - Logan
 *         - Added more defines - Logan
 * 4/11/05 - Re-structured for FLASH - Logan
 */
#ifndef NODELIST_H_
#define NODELIST_H_

#include <stdint.h>
#include <stdbool.h>

/** Total number of nodes in the arena map */
#define NUM_NODES       43

/** Beginning of node number range used for ball nodes */
#define BALL_NODE_MIN   1         
/** End of node number range used for ball nodes */
#define BALL_NODE_MAX   20
/** Beginning of node number range used for junction nodes */
#define JUNCTION_MIN    21
/** End of node number range used for junction nodes */
#define JUNCTION_MAX    41

#define NUM_BALL_NODES  (BALL_NODE_MAX - BALL_NODE_MAX + 1)


/** Maximum number nodes that can be adjacent to one node */
#define MAX_ADJ_NODES   3
/** Direction of north west in binary radians (brads) */
#define N_WEST          -41
/** Convenience macor for direction of south east in (brads) */
#define S_EAST          87

/** Node number of bonus ball 1 */
#define BONUS_BALL_1    24
/** Node number of bonus ball 2 */
#define BONUS_BALL_2    30
/** Node number of the nest release sensor */
#define SENSOR_NODE     37

/** The heading required to pickup bonus ball 1 */
#define BB1_HEADING     32
/** The heading required to pickup bonus ball 2 */
#define BB2_HEADING     -96

/** The number of goals known a priori (nest sensor and two bonus balls) */
#define NUM_FIXED_GOALS    3
/** The number of goals with unknown location at the start of a run (ground balls) */
#define NUM_RANDOM_GOALS   3
/** Total number of goals */
#define NUM_GOALS          NUM_FIXED_GOALS + NUM_RANDOM_GOALS

/**
 * @brief Definition of each node (vertex) in the course map node
 *
 * Defines the directions and distances to adjacent nodes.
 */
typedef struct nodeStruct
{
    /**
     * number of nodes adjacent to this node
     */
    uint8_t numAdjNodes;
    /**
     * node numbers of adjacent nodes
     */
    uint8_t adjNodes[MAX_ADJ_NODES];
    /**
     * distances to adjacent nodes (6 inches increments)
     */
    uint8_t adjCosts[MAX_ADJ_NODES];
    /**
     * directions towards adjacent nodes in 8-bit @link brads
     */
    int8_t adjHeadings[MAX_ADJ_NODES];
} NODE;


inline bool isJunction( uint8_t nodeNum );
uint8_t getCostToNode(NODE *node, uint8_t nodeNum);
uint8_t getNodeAtHeading(NODE *node, int8_t heading);
inline bool isBallNode( uint8_t nodeNum );
void getNode( uint8_t nodeNum, NODE *node );


#endif // #ifndef NODELIST_H_
