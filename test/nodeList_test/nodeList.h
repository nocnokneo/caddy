// nodeList.h
#ifndef NODELIST_H
#define NODELIST_H

#include "global.h"


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


typedef struct nodeStruct NODE;
struct nodeStruct
{
  uint8_t numAdjNodes;                  // number of nodes adjacent to this node
  uint8_t adjNodes[MAX_ADJ_NODES];      // node numbers of adjacent nodes
  uint8_t adjCosts[MAX_ADJ_NODES];      // distances to       "       "  (6 inches)
  int8_t adjHeadings[MAX_ADJ_NODES];   // directions towards "       "   (brads)
};



void getNode( uint8_t nodeNum, NODE *node );


#endif  // #ifndef
