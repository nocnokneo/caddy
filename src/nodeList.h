// nodeList.h
#ifndef NODELIST_H
#define NODELIST_H

#include "caddy.h"


#define NUM_NODES       43        // number of nodes in arena

#define BALL_NODE_MIN   1         // ball node number range
#define BALL_NODE_MAX   20
#define JUNCTION_MIN    21        // junction node number range
#define JUNCTION_MAX    41

#define NUM_BALL_NODES  BALL_NODE_MAX-BALL_NODE_MAX+1


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

typedef struct nodeStruct NODE;
typedef struct nodeStruct* NODE_PTR;
struct nodeStruct
{
  u08 numAdjNodes;                  // number of nodes adjacent to this node
  u08 adjNodes[MAX_ADJ_NODES];      // node numbers of adjacent nodes
  u08 adjCosts[MAX_ADJ_NODES];      // distances to       "       "  (6 inches)
  s08 adjHeadings[MAX_ADJ_NODES];   // directions towards "       "   (brads)
};


inline BOOL isJunction( u08 nodeNum );
u08 getCostToNode(NODE *node, u08 nodeNum);
inline BOOL isBallNode( u08 nodeNum );
void getNode( u08 nodeNum, NODE *node );
u08 getNodeAtHeading(NODE *node, s08 heading);

#endif  // #ifndef
