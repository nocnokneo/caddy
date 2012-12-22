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
BOOL standardBallSearch( void );
inline BOOL nodeCode0( void );
inline BOOL nodeCode22( void );
inline BOOL diagNodeCode(void);
inline BOOL nodeCode37( void );


#endif
