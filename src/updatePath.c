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
#include "updatePath.h"
#include "botCntrl.h"
#include "servos.h"
#include "junctionCode.h"
#include "nodeList.h"
#include "ourLCD.h"
#include "perms.h"
#include "helperFunctions.h"

// avr-libc
#include <string.h>
#include <stdlib.h>

#define NO_PARENT  0xff
#define MAX_COST   0xff

typedef struct SearchNode
{
    uint8_t parent;
    uint8_t pathCost;
    bool    visited;
} SearchNodeType;

typedef struct PathListNode
{
    uint8_t nodeNum;
    struct PathListNode *nextNode;
} PathListNodeType ;

static SearchNodeType searchSpace[NUM_NODES];

// Globals
uint8_t pathList[MAX_PATH_LIST_SIZE];// = INITIAL_PATH_LIST;
uint8_t pathListSize;
uint8_t pathListIndex;

static inline uint8_t uniformCostSearch( uint8_t startNode, uint8_t goalNode /*, SEARCH_NODE searchSpace[]*/ );
static inline PathListNodeType * addNodeByCost(PathListNodeType *head, uint8_t newNodeNum /*, SEARCH_NODE searchSpace[]*/ );
static inline void recostructPath( uint8_t startNode, uint8_t goalNode /*, SEARCH_NODE searchSpace[]*/ );
static inline uint8_t updatePathTo( uint8_t nodeNum );
static inline void freeList(PathListNodeType *head);
static inline PathListNodeType * freeNode(PathListNodeType *head);

// returns distance of path found
uint8_t updatePath(void)
{
    uint8_t startCost[NUM_GOALS];
    uint8_t goalCost[NUM_GOALS][NUM_GOALS];
    uint8_t stopCost[NUM_GOALS];

    uint8_t tempGoalList[NUM_GOALS];

    uint8_t curPerm[NUM_GOALS];
    uint8_t bestPerm[NUM_GOALS];
    uint8_t bestCost;

    uint8_t i;
    uint8_t j;
    uint8_t tempCost;

    // find distances between goal nodes and start/stop nodes
    for (i = 0; i < goalListSize; i++)
    {
        startCost[i] = uniformCostSearch(botNode, goalList[i]);
        stopCost[i] = uniformCostSearch(goalList[i], STOP_NODE);
    }

    // find distances between every goal node
    for (i = 0; i < goalListSize; i++)
    {
        for (j = 0; j <= i; j++)
        {
            if (i == j)
                goalCost[i][j] = 0;
            else
            {
                tempCost = uniformCostSearch(goalList[i], goalList[j]);
                goalCost[i][j] = tempCost;
                goalCost[j][i] = tempCost;
            }
        }
    }

    // initialize list for permutations
    for (i = 0; i < goalListSize; i++)
    {
        curPerm[i] = i;
    }

    bestCost = MAX_COST;

    // make sure goalListSize > 0
    if (goalListSize == 0)
    {
        // set pathList to STOP_NODE
        return updatePathTo(STOP_NODE);
    }

    do
    {
        // Find distance of this permutation
        tempCost = startCost[curPerm[0]];
        for (i = 0; i < goalListSize - 1; i++)
            tempCost += goalCost[curPerm[i]][curPerm[i + 1]];
        tempCost += stopCost[curPerm[i]];

        // save tempCost and perm, if this permutation is better
        if (tempCost < bestCost)
        {
            bestCost = tempCost;
            copyList(curPerm, bestPerm, goalListSize);
        }

    } while (generateNextPermutation(curPerm, curPerm + goalListSize));

    // Re-order goalList according to bestPerm.
    copyList(goalList, tempGoalList, goalListSize);
    for (i = 0; i < goalListSize; i++)
        goalList[i] = tempGoalList[bestPerm[i]];

    // Replace current projectedPath with newly found best path
    pathListIndex = MAX_PATH_LIST_SIZE - 1;
    uniformCostSearch(goalList[goalListSize - 1], STOP_NODE);
    recostructPath(goalList[goalListSize - 1], STOP_NODE);
    for (i = goalListSize - 1; i > 0; i--)
    {
        uniformCostSearch(goalList[i - 1], goalList[i]);
        recostructPath(goalList[i - 1], goalList[i]);
    }
    uniformCostSearch(botNode, goalList[0]);
    recostructPath(botNode, goalList[0]);

    //printPathList();

    return bestCost;
}

// returns distance of path found
uint8_t updatePathTo(uint8_t nodeNum)
{
    uint8_t tempCost = uniformCostSearch(botNode, nodeNum);
    pathListIndex = MAX_PATH_LIST_SIZE - 1;
    recostructPath(botNode, nodeNum);
    return tempCost;
}

// fills searchSpace with parent information
// returns distance of path found
inline uint8_t uniformCostSearch(uint8_t startNode, uint8_t goalNode)
{
    NODE nodeData;
    uint8_t n;

    PathListNodeType *visitList = NULL;
    uint8_t curNodeNum = startNode;
    uint8_t curCost = 0;

    // init searchSpace
    uint8_t i;
    for (i = 0; i < NUM_NODES; i++)
    {
        searchSpace[i].parent = NO_PARENT;
        searchSpace[i].pathCost = MAX_COST;
        searchSpace[i].visited = false;
    }

    searchSpace[startNode].pathCost = 0;
    searchSpace[startNode].visited = true;
    while (curNodeNum != goalNode)
    {
        // explore successors, if haven't visited yet
        getNode(curNodeNum, &nodeData);
        for (i = 0; i < nodeData.numAdjNodes; i++)
        {
            n = nodeData.adjNodes[i];
            // if not visited and not found yet, add to visit list
            if (!searchSpace[n].visited && searchSpace[n].pathCost == MAX_COST)
            {
                searchSpace[n].parent = curNodeNum;
                searchSpace[n].pathCost = curCost + nodeData.adjCosts[i];
                visitList = addNodeByCost(visitList, n /*, searchSpace*/);
            }
        }

        // visit next node w/ lowest cost, if one exists
        if (visitList == NULL )
        {
#if DEBUGGING
            lcdWriteStr("uniformCostSearc", 0, 0);
            lcdWriteStr("error           ", 1, 0);
            while (1) ;
#endif
            return MAX_COST;  //  b/c path not found
        }
        else
        {
            // get info of and remove first node of visitList
            curNodeNum = visitList->nodeNum;
            curCost = searchSpace[curNodeNum].pathCost;
            searchSpace[curNodeNum].visited = true;
            visitList = freeNode(visitList);
        }
    }

    freeList(visitList);

    return searchSpace[goalNode].pathCost;
}

PathListNodeType * addNodeByCost(PathListNodeType *head, uint8_t newNodeNum)
{
    PathListNodeType *current = NULL;
    PathListNodeType *next = NULL;
    PathListNodeType *newNode = NULL;      // node being inserted

    // allocate space for new node
    newNode = (PathListNodeType *) malloc(sizeof(PathListNodeType));
    newNode->nodeNum = newNodeNum;
    newNode->nextNode = NULL;

    //add to empty list
    if (head == NULL )
    {
        return newNode;
    }

    //add to front of list
    if (searchSpace[head->nodeNum].pathCost > searchSpace[newNodeNum].pathCost)
    {
        next = head;
        head = newNode;
        head->nextNode = next;
    }

    //add after head
    else
    {
        current = head;
        next = head->nextNode;

        while (next != NULL )
        {
            if (searchSpace[next->nodeNum].pathCost >= searchSpace[newNodeNum].pathCost)
                break;

            current = current->nextNode;
            next = next->nextNode;
        }

        newNode->nextNode = next;
        current->nextNode = newNode;
    }

    return head;
}


// fills pathList in reverse order (from goalNode to startNode)
// PRE: searchSpace has been filled with parent info
//      pathListIndex points to the first position to fill
//      pathList is large enough to prevent pathListIndex from reaching below zero
// POST: pathListIndex points to first node in pathList
inline void recostructPath(uint8_t startNode, uint8_t goalNode)
{
    pathList[pathListIndex] = goalNode;
    while (goalNode != startNode)
    {
        goalNode = searchSpace[goalNode].parent;
        pathListIndex--;
        pathList[pathListIndex] = goalNode;
    }
}

// Frees all nodes in list at head
inline void freeList(PathListNodeType *head)
{
    while (head != NULL)
    {
        head = freeNode(head);
    }
}

// Frees node at head and returns pointer to next node
inline PathListNodeType * freeNode(PathListNodeType *head)
{
    PathListNodeType *temp = NULL;
    temp = head;
    head = head->nextNode;
    free(temp);
    return head;
}
