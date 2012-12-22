/* helperFunctions.c
 *
 *    Useful functions used in several locations.
 *
 */

#include "helperFunctions.h"

 
void myDelay(u16 outerDelay)
{
   u16 i, j;
   for(i=0; i<outerDelay; i++)
   {
      for(j=0; j<MAX_U16; j++) ;
   }
}


void msDelay(u16 ms)
{
   u16 i;
   for (i=0; i < ms; i++)
   {
      delay(1000); // 1000 microseconds
   }
}


/*
 * Searches for 'value' in 'array'.  If found, index where 'value'
 * was found is returned.  Otherwise, -1 is returned.
 */
s08 getIndex(u08 value, const u08 array[], const u08 arraySize)
{
	u08 i = 0;
	while( i < arraySize )
	{
		if( array[i] == value )
			return i;
		i++;
	}
	return -1;
}

// tells bot where fixed goals are
inline void initGoalList( void )
{
   goalListSize = 0;
   addToGoalList(BONUS_BALL_1);
   addToGoalList(BONUS_BALL_2);
   addToGoalList(SENSOR_NODE);
}

inline void addToGoalList( u08 nodeNum )
{
   goalList[goalListSize++] = nodeNum;
}

BOOL removeFromGoalList( u08 nodeNum )
{
   s08 i = getIndex( nodeNum, goalList, goalListSize );
   if( i == -1 )
      return FALSE;
   
   for(; i < goalListSize-1; i++ )
   {
      goalList[i] = goalList[i+1];
   }
   goalListSize--;
   
   return TRUE;
}


BOOL nextBallNodesInGoalList( void )
{
   u08 i = 1;
   u08 nodeNum = pathList[pathListIndex + i];
   while( isBallNode( nodeNum ) )
   {
      if( isInGoalList( nodeNum ) )
      {
         return TRUE;
      }
      i++;
      nodeNum = pathList[pathListIndex + i];
   }
   
   return FALSE;
}


inline BOOL isInGoalList( u08 nodeNum )
{
   return getIndex(nodeNum, goalList, goalListSize) != -1;
}

inline void printGoalList( void )
{
#if DEBUGGING
   u08 i;
   
   lcdWriteStr("                ", 0, 0);
   lcdWriteStr("                ", 1, 0);
   
   if( goalListSize == 0 )
   {
      lcdWriteStr("(empty)",0,0);
   }
   else
   {
      for( i = 0; i < goalListSize; i++ )
      {
         lcdPrintDecU08( goalList[i], 0, 3*i );
      }
   }
#endif
}
