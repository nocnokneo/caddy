// botCntrl.h
#ifndef BOTCNTRL_H
#define BOTCNTRL_H

#include "caddy.h"


// --- GLOBALS --- //
extern u08 botNode;
extern s08 botHeading;
BOOL liftDown;

// --- Prototypes --- //
inline void runBot( void );
void initBotGlobals(void);
inline BOOL positionBot(void);
inline s08 getNextHeading(u08 nextBotNode);
inline void moveToJunction( u08 numJunctions, BOOL justTurned );
void stopBotOverJunction( void );
void bbSequence( void );
void nestSequence( void );
inline void bbPositioning( s08 bbHeading, s08 nextHeading );


#endif  // #ifndef
