// helperFunctions.h
#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "caddy.h"

void myDelay(u16 outerDelay);
void msDelay(u16 ms);
s08  getIndex(u08 value, const u08 array[], const u08 arraySize);

inline void initGoalList( void );
inline BOOL isInGoalList( u08 nodeNum );
inline void addToGoalList( u08 nodeNum );
BOOL removeFromGoalList( u08 nodeNum );
inline void printGoalList( void );
BOOL nextBallNodesInGoalList( void );

#endif  // #ifndef
