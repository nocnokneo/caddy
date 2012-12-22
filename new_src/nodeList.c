/* nodeList.c
 *
 *   Saves SRAM by storing graph of arena in FLASH.
 *   See doc directory for image of arena with node numbers.
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
 *        4/11/05 - Re-structured for FLASH - Logan
 */

#include "nodeList.h"


inline BOOL isJunction( u08 nodeNum )
{
   return (nodeNum >= JUNCTION_MIN && nodeNum <= JUNCTION_MAX);
}

inline BOOL isBallNode( u08 nodeNum )
{
   return (nodeNum >= BALL_NODE_MIN && nodeNum <= BALL_NODE_MAX);
}


u08 getCostToNode(NODE *node, u08 nodeNum)
{
   u08 i;
   for(i=0; i < node->numAdjNodes; i++)
   {
      if(node->adjNodes[i] == nodeNum)
         return node->adjCosts[i];
   }
   return 0;
}


u08 getNodeAtHeading(NODE *node, s08 heading)
{
   u08 i;
   for (i=0; i < node->numAdjNodes; i++)
   {
      if(node->adjHeadings[i] == heading)
         return node->adjNodes[i];
   }
   return 0;
}


void getNode( u08 nodeNum, NODE *node )
{
   if( nodeNum >= NUM_NODES )
   {
      node = NULL;
   }
   
   switch( nodeNum )
   {
      case 0:                          // START_NODE
         node->numAdjNodes = 1;
         node->   adjNodes[0] = 21;
         node->   adjCosts[0] = 9;
         node->adjHeadings[0] = -64;
         break;
      case 1:                          // First ball node
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 21;
         node->   adjNodes[1] = 22;
         node->   adjCosts[0] = 4;
         node->   adjCosts[1] = 4;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 0;
         break;
      case 2:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 22;
         node->   adjNodes[1] = 23;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 64;
         break;
      case 3:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 23;
         node->   adjNodes[1] = 24;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = 0;
         node->adjHeadings[1] = -128;
         break;
      case 4:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 24;
         node->   adjNodes[1] = 25;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 3;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 64;
         break;
      case 5:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 26;
         node->   adjNodes[1] = 41;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 64;
         break;
      case 6:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 27;
         node->   adjNodes[1] = 28;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = 64;
         node->adjHeadings[1] = -64;
         break;
      case 7:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 27;
         node->   adjNodes[1] = 32;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 3;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 0;
         break;
      case 8:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 28;
         node->   adjNodes[1] = 30;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 3;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 0;
         break;
      case 9:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 22;
         node->   adjNodes[1] = 29;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 3;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 0;
         break;
      case 10:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 29;
         node->   adjNodes[1] = 30;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 3;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 64;
         break;
      case 11:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 12;
         node->   adjNodes[1] = 29;
         node->   adjCosts[0] = 4;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = 0;
         node->adjHeadings[1] = -128;
         break;
      case 12:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 11;
         node->   adjNodes[1] = 33;
         node->   adjCosts[0] = 4;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 0;
         break;
      case 13:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 33;
         node->   adjNodes[1] = 34;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 1;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 64;
         break;
      case 14:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 15;
         node->   adjNodes[1] = 34;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 4;
         node->adjHeadings[0] = S_EAST;
         node->adjHeadings[1] = N_WEST;
         break;
      case 15:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 14;
         node->   adjNodes[1] = 31;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 4;
         node->adjHeadings[0] = N_WEST;
         node->adjHeadings[1] = S_EAST;
         break;
      case 16:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 32;
         node->   adjNodes[1] = 40;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 64;
         break;
      case 17:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 34;
         node->   adjNodes[1] = 35;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 3;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 64;
         break;
      case 18:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 39;
         node->   adjNodes[1] = 40;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = 0;
         node->adjHeadings[1] = -128;
         break;
      case 19:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 20;
         node->   adjNodes[1] = 40;
         node->   adjCosts[0] = 4;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 0;
         break;
      case 20:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 19;
         node->   adjNodes[1] = 41;
         node->   adjCosts[0] = 4;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = 0;
         node->adjHeadings[1] = -128;
         break;
      case 21:                         // First Junction Node
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 0;
         node->   adjNodes[1] = 1;
         node->   adjCosts[0] = 9;
         node->   adjCosts[1] = 4;
         node->adjHeadings[0] = 64;
         node->adjHeadings[1] = 0;
         break;
      case 22:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 1;
         node->   adjNodes[1] = 2;
         node->   adjNodes[2] = 9;
         node->   adjCosts[0] = 4;
         node->   adjCosts[1] = 2;
         node->   adjCosts[2] = 3;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 64;
         node->adjHeadings[2] = 0;
         break;
      case 23:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 2;
         node->   adjNodes[1] = 3;
         node->   adjNodes[2] = 28;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->   adjCosts[2] = 2;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = -128;
         node->adjHeadings[2] = 64;
         break;
      case 24:                         // BONUS_BALL_1
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 3;
         node->   adjNodes[1] = 4;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 3;
         node->adjHeadings[0] = 0;
         node->adjHeadings[1] = 64;
         break;
      case 25:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 4;
         node->   adjNodes[1] = 26;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 0;
         break;
      case 26:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 5;
         node->   adjNodes[1] = 25;
         node->   adjNodes[2] = 27;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->   adjCosts[2] = 2;
         node->adjHeadings[0] = 64;
         node->adjHeadings[1] = -128;
         node->adjHeadings[2] = 0;
         break;
      case 27:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 6;
         node->   adjNodes[1] = 7;
         node->   adjNodes[2] = 26;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 3;
         node->   adjCosts[2] = 2;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 0;
         node->adjHeadings[2] = -128;
         break;
      case 28:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 6;
         node->   adjNodes[1] = 8;
         node->   adjNodes[2] = 23;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 3;
         node->   adjCosts[2] = 2;
         node->adjHeadings[0] = 64;
         node->adjHeadings[1] = 0;
         node->adjHeadings[2] = -64;
         break;
      case 29:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 9;
         node->   adjNodes[1] = 10;
         node->   adjNodes[2] = 11;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 3;
         node->   adjCosts[2] = 2;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 64;
         node->adjHeadings[2] = 0;
         break;
      case 30:                          // BONUS_BALL_2
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 8;
         node->   adjNodes[1] = 10;
         node->   adjNodes[2] = 31;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 3;
         node->   adjCosts[2] = 3;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = -64;
         node->adjHeadings[2] = 64;
         break;
      case 31:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 15;
         node->   adjNodes[1] = 30;
         node->   adjNodes[2] = 32;
         node->   adjCosts[0] = 4;
         node->   adjCosts[1] = 3;
         node->   adjCosts[2] = 1;
         node->adjHeadings[0] = N_WEST;
         node->adjHeadings[1] = -64;
         node->adjHeadings[2] = 64;
         break;
      case 32:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 7;
         node->   adjNodes[1] = 16;
         node->   adjNodes[2] = 31;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 2;
         node->   adjCosts[2] = 1;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 64;
         node->adjHeadings[2] = -64;
         break;
      case 33:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 12;
         node->   adjNodes[1] = 13;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = 64;
         break;
      case 34:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 13;
         node->   adjNodes[1] = 14;
         node->   adjNodes[2] = 17;
         node->   adjCosts[0] = 1;
         node->   adjCosts[1] = 4;
         node->   adjCosts[2] = 3;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = S_EAST;
         node->adjHeadings[2] = 64;
         break;
      case 35:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 17;
         node->   adjNodes[1] = 36;
         node->   adjCosts[0] = 3;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = -128;
         break;
      case 36:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 35;
         node->   adjNodes[1] = 37;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = 0;
         node->adjHeadings[1] = 64;
         break;
      case 37:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 36;
         node->   adjNodes[1] = 38;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = -128;
         break;
      case 38:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 37;
         node->   adjNodes[1] = 39;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = 0;
         node->adjHeadings[1] = 64;
         break;
      case 39:
         node->numAdjNodes = 2;
         node->   adjNodes[0] = 18;
         node->   adjNodes[1] = 38;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->adjHeadings[0] = -128;
         node->adjHeadings[1] = -64;
         break;
      case 40:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 16;
         node->   adjNodes[1] = 18;
         node->   adjNodes[2] = 19;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->   adjCosts[2] = 2;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 0;
         node->adjHeadings[2] = -128;
         break;
      case 41:
         node->numAdjNodes = 3;
         node->   adjNodes[0] = 5;
         node->   adjNodes[1] = 20;
         node->   adjNodes[2] = 42;
         node->   adjCosts[0] = 2;
         node->   adjCosts[1] = 2;
         node->   adjCosts[2] = 5;
         node->adjHeadings[0] = -64;
         node->adjHeadings[1] = 0;
         node->adjHeadings[2] = -128;
         break;
      case 42:                         // STOP_NODE
         node->numAdjNodes = 1;
         node->   adjNodes[0] = 41;
         node->   adjCosts[0] = 5;
         node->adjHeadings[0] = 0;
         break;
   }
}
