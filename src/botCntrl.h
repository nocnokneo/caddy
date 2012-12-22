// botCntrl.h
#ifndef BOTCNTRL_H
#define BOTCNTRL_H

#include "caddy.h"


#define BEAM_IGNORE_COUNT      6
#define CORRAL_COUNT           3
#define LIFT_DONE_COUNT        8


// --- GLOBALS --- //
extern u08 botNode;
extern s08 botHeading;
extern u08 numUnreachedGoals;
BOOL liftDown;
u08 upComingBallNum;

// --- Prototypes --- //
inline void runBot( void );
inline void initBotGlobals(void);
inline BOOL positionBot(void);
inline s08 getNextHeading(u08 nextBotNode);
inline void moveToJunction( u08 numJunctions, BOOL justTurned );
void bbSequence( void );
void nestSequence( void );
inline void bbPositioning( s08 bbHeading, s08 nextHeading );


#endif  // #ifndef
