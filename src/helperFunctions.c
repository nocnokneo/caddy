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
#include <stdbool.h>

void myDelay(uint16_t outerDelay)
{
    uint16_t i, j;
    for (i = 0; i < outerDelay; i++)
        for (j = 0; j < MAX_U16; j++) ;
}

void msDelay(uint16_t ms)
{
    uint16_t i;
    for (i = 0; i < ms; i++)
    {
        delay(1000); // 1000 microseconds
    }
}

/*
 * Searches for 'value' in 'array'.  If found, index where 'value'
 * was found is returned.  Otherwise, -1 is returned.
 */
int8_t getIndex(uint8_t value, const uint8_t array[], const uint8_t arraySize)
{
    uint8_t i = 0;
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

inline void addToGoalList(uint8_t nodeNum)
{
    if (!isInGoalList(nodeNum))
    {
        goalList[goalListSize++] = nodeNum;
        numKnownGoals++;
    }
}

bool removeFromGoalList(uint8_t nodeNum)
{
    int8_t i = getIndex(nodeNum, goalList, goalListSize);
    if (i == -1)
    {
        numUnreachedGoals--;
        numKnownGoals++;
        return false;
    }

    for (; i < goalListSize - 1; i++)
    {
        goalList[i] = goalList[i + 1];
    }
    goalListSize--;
    numUnreachedGoals--;

    return true;
}

// returns 0 if no ball is in goalList
uint8_t getUpcomingBallNum(void)
{
    uint8_t i = 1;
    uint8_t nodeNum = pathList[pathListIndex + i];
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

inline bool isInGoalList(uint8_t nodeNum)
{
    return getIndex(nodeNum, goalList, goalListSize) != -1;
}

inline void printGoalList(void)
{
#if DEBUGGING
    uint8_t i;

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

inline void copyList(uint8_t srcList[], uint8_t destList[], uint8_t numElements)
{
    uint8_t i;
    for (i = 0; i < numElements; i++)
    {
        destList[i] = srcList[i];
    }
}
