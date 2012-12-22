// junctionCode.h
#ifndef JUNCTIONCODE_H
#define JUNCTIONCODE_H

#include "caddy.h"

#define BALL_DIST       0
#define BALL_NODE_NUM   1

extern BOOL checkedList[];
extern u08 goalList[];

u08 goalListSize;
u08 numKnownGoals;

void junctionCode(void);
BOOL standardBallSearch(u08 nodesWithBalls[], u08 *numNodesWithBalls);
inline void nodeCode0(u08 nodesWithBalls[], u08 *numNodesWithBalls);
inline void nodeCode22(u08 nodesWithBalls[], u08 *numNodesWithBalls);
inline void nodeCode30(u08 nodesWithBalls[], u08 *numNodesWithBalls);

#endif
