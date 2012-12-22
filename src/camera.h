// camera.h

#ifndef CAMERA_H
#define CAMERA_H

#include "caddy.h"
#define CMU_BAUD 38400
// Packet types
#define NEW_PACKET   0
#define FE_RCV       1
#define T_RCV        2
#define ACK_RCV      3
#define NCK_RCV      4
#define ASCII_RCV    5


#define hiResMode()  rprintf("hr 1\r")
#define lowResMode() rprintf("hr 0\r")

u08 mode;
u16 byteNum;

void cameraWhiteBal( void );
void resetCamera( void );
BOOL cameraSeesBall( void );
BOOL cameraSeesNest( void );
void packetRcv( u08 c );
void lineMode2Rcv( u08 c );
void trackColorRcv( u08 c );
void streamModeOff( void );
inline void setVW(u08 x1, u08 y1, u08 x2, u08 y2);
inline void downSample(u08 x, u08 y);


#endif  // #ifndef
