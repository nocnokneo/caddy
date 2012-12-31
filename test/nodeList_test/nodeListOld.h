/* nodeListOld.h
 *
 *    Declares and initializes nodeList, the arena's graph structure.
 *
 *    -Nodes are represented by numbers:
 *       -Nodes 0 and 42 are terminal nodes
 *       -Nodes 1-20 are ball nodes
 *       -Nodes 21-41 are junctions
 *    -Distance resolution is 6 inches.
 *    -Direction is measured in binary radians or brads. (see www.urcp.com)
 *
 *    Version History:
 *        2/17/05 - Created by Logan
 *        2/21/05 - Checked by Logan, Scott, and Patrik
 *                - Changed syntax for Atmel - Logan
 *                - Added more defines - Logan
 */

#ifndef NODELISTOLD_H
#define NODELISTOLD_H

#include "global.h"
#include "nodeList.h"

/*
#include "caddy.h"
#include "avrlibtypes.h"

#define MAX_ADJ_NODES   3         // max. nodes that can be adjacent to one node
#define NUM_NODES       43        // number of nodes in arena
#define N_WEST          -41       // direction of north west in binary radians (brads)
#define S_EAST          87        // direction of south east in binary radians (brads)

#define START_NODE      0         // initial node
#define START_HEADING   -64       // initial heading
#define STOP_NODE       42        // node by nest

#define BALL_NODE_MIN   1         // ball node number range
#define BALL_NODE_MAX   20
#define JUNCTION_MIN    21        // junction node number range
#define JUNCTION_MAX    41

#define NUM_BALL_NODES BALL_NODE_MAX-BALL_NODE_MAX+1

#define NEST_NODE       37        // fixed goal locations
#define BONUS_BALL_1    24
#define BONUS_BALL_2    30


struct node
{
  uint8_t numAdjNodes;                  // number of nodes adjacent to this node
  uint8_t adjNodes[MAX_ADJ_NODES];      // node numbers of adjacent nodes
  uint8_t adjCosts[MAX_ADJ_NODES];      // distances to       "       "  (6 inches)
  int8_t adjHeadings[MAX_ADJ_NODES];   // directions towards "       "   (brads)
};

extern struct node nodeList[];
*/

extern NODE nodeList[];

#endif  // #ifndef
