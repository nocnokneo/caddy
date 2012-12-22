/* junctionCode.c
 *
 *   Actions that occur at junctions.
 *
 *   (Pass by reference causes error.) -Logan
 */

#include "junctionCode.h"


BOOL checkedList[NUM_BALL_NODES];  // initialized in initBotGlobals
u08 goalList[NUM_GOALS];           // initialized in initBotGlobals

/*
 * Searches for ground balls, picks-up bonous balls, and computes best path.
 */
void junctionCode(void)
{
   u08 nodesWithBalls[NUM_RANDOM_GOALS];
   u08 numNodesWithBalls = NUM_RANDOM_GOALS;
   
   switch( botNode )
   {
      case(0):
         nodeCode0(nodesWithBalls, &numNodesWithBalls);
         break;
      case(21):
         break;
      case(22):
         nodeCode22(nodesWithBalls, &numNodesWithBalls);
         break;
      case(30):
         nodeCode30(nodesWithBalls, &numNodesWithBalls);
         break;
      default:
         standardBallSearch(nodesWithBalls, &numNodesWithBalls);
         break;
   }
   
   if( numNodesWithBalls > 0 )
   {
      // add to goal list
      // clear checked list, if last ball found
      // updatePath()
      // re-order goal list according to pathList (optional for LCD debugging)
   }
}

/* 
 * Returns true if a ball is found and the goal list is updated
 */
BOOL standardBallSearch(u08 nodesWithBalls[], u08 *numNodesWithBalls)
{
   NODE curNode, nextNode;
   //u08 curNodeNum;
   u08 nextNodeNum;
   s08 lookDir = -1;                   // look left first
   s08 hallHeading = 0;
   u08 ballDist = 0;
   u08 uncheckedBalls[3][2];
   u08 numUncheckedBalls = 0;
   BOOL foundBall = FALSE;
   u08 i;
   
   // Check for balls in two directions (left/right)
   for(i = 0; i < 2; i++)
   {
      ballDist = 0;
      hallHeading = botHeading + lookDir*64;
      nextNodeNum = botNode;
      numUncheckedBalls = 0;
      // Continue traversing nodes left of right until you hit the end
      while( nextNodeNum > 0 )
      {
         getNode(nextNodeNum, &curNode);
         nextNodeNum = getNodeAtHeading(&curNode, hallHeading);
         if( nextNodeNum > 0 )
         {
            getNode(nextNodeNum, &nextNode);
            // Keep track of how far away we are from the bot's current node
            ballDist += getCostToNode(&curNode, nextNodeNum);
            if (isBallNode(nextNodeNum) && !checkedList[nextNodeNum])
            {
               uncheckedBalls[numUncheckedBalls][BALL_DIST] = ballDist;
               uncheckedBalls[numUncheckedBalls][BALL_NODE_NUM] = nextNodeNum;
               checkedList[nextNodeNum] = TRUE;
               numUncheckedBalls++;
            }
         }
      }
      
      if(lookDir == -1 && numUncheckedBalls > 0) 
         foundBall |= cameraSeekLeft(uncheckedBalls, numUncheckedBalls);
      else if(lookDir == 1 && numUncheckedBalls > 0) 
         foundBall |= cameraSeekRight(uncheckedBalls, numUncheckedBalls);
      lookDir *= -1;
   }
   
#if DEBUGGING
   lcdWriteStr("Unchecked balls:", 0, 0);
   for(i = 0; i < numUncheckedBalls; i++)
   {
      lcdPrintHex(uncheckedBalls[BALL_NODE_NUM][i], 1, i*3);
   }
#endif
   // Returns true if one or more balls are found
   return foundBall;
}

inline void nodeCode0(u08 nodesWithBalls[], u08 *numNodesWithBalls)
{

}


inline void nodeCode22(u08 nodesWithBalls[], u08 *numNodesWithBalls)
{

}

inline void nodeCode30(u08 nodesWithBalls[], u08 *numNodesWithBalls)
{
   // if( !checkedList[14] || !checkedList[15] )
   // {
   //    switch(botHeading)
   //        special seek for balls on diagonal
   // }
}
