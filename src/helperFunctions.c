/*
 * This file is part of Caddy.
 *
 *  Caddy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Caddy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Caddy.  If not, see <http://www.gnu.org/licenses/>.
 */
/* helperFunctions.c
 *
 *    Useful functions used in several locations.
 *
 */

#include "helperFunctions.h"

void myDelay(u16 outerDelay)
{
    u16 i, j;
    for (i = 0; i < outerDelay; i++)
        for (j = 0; j < MAX_U16; j++) ;
}

void msDelay(u16 ms)
{
    u16 i;
    for (i = 0; i < ms; i++)
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
    while (i < arraySize)
    {
        if (array[i] == value)
            return i;
        i++;
    }
    return -1;
}

// tells bot where fixed goals are
inline void initGoalList(void)
{
    goalListSize = 0;
    addToGoalList(BONUS_BALL_1);
    addToGoalList(BONUS_BALL_2);
    addToGoalList(SENSOR_NODE);
}

inline void addToGoalList(u08 nodeNum)
{
    if (!isInGoalList(nodeNum))
    {
        goalList[goalListSize++] = nodeNum;
        numKnownGoals++;
    }
}

BOOL removeFromGoalList(u08 nodeNum)
{
    s08 i = getIndex(nodeNum, goalList, goalListSize);
    if (i == -1)
    {
        numUnreachedGoals--;
        numKnownGoals++;
        return FALSE;
    }

    for (; i < goalListSize - 1; i++)
    {
        goalList[i] = goalList[i + 1];
    }
    goalListSize--;
    numUnreachedGoals--;

    return TRUE;
}

// returns 0 if no ball is in goalList
u08 getUpcomingBallNum(void)
{
    u08 i = 1;
    u08 nodeNum = pathList[pathListIndex + i];
    while (isBallNode(nodeNum))
    {
        if (isInGoalList(nodeNum))
        {
            return nodeNum;
        }
        i++;
        nodeNum = pathList[pathListIndex + i];
    }

    return 0;
}

inline BOOL isInGoalList(u08 nodeNum)
{
    return getIndex(nodeNum, goalList, goalListSize) != -1;
}

inline void printGoalList(void)
{
#if DEBUGGING
    u08 i;

    lcdWriteStr("                ", 0, 0);

    if (goalListSize == 0)
    {
        lcdWriteStr("(empty)", 0, 0);
    } else
    {
        for (i = 0; i < goalListSize; i++)
        {
            lcdPrintDecU08(goalList[i], 0, 3 * i);
        }
    }
#endif
}

inline void copyList(u08 srcList[], u08 destList[], u08 numElements)
{
    u08 i;
    for (i = 0; i < numElements; i++)
    {
        destList[i] = srcList[i];
    }
}
