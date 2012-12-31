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
//updatePath.h
#ifndef UPDATEPATH_H
#define UPDATEPATH_H

#include "caddy.h"

#define MAX_PATH_LIST_SIZE 70

#define START_NODE      0              // initial node
#define START_HEADING   -64            // initial heading
#define STOP_NODE       42             // node by nest
#define INITIAL_PATH_LIST_SIZE    29
#define INITIAL_PATH_LIST   {0,21,1,22,2,23,3,24,3,23,28,8,30,31,32,16,40,18,39,38,37,38,39,18,40,19,20,41,42,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

// FIXED PATH
//#define INITIAL_PATH_LIST_SIZE    47
//#define INITIAL_PATH_LIST   {0,21,1,22,9,29,11,12,33,13,34,17,35,36,37,38,39,18,40,19,20,41,5,26,25,4,24,3,23,2,22,9,29,10,30,8,28,6,27,7,32,16,40,19,20,41,42,0,0,00,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


#define NO_PARENT  0xff
#define MAX_COST   0xff

typedef struct searchNode
{
    u08 parent;
    u08 pathCost;
    BOOL visited;
} SEARCH_NODE;


extern u08 pathList[];
extern SEARCH_NODE searchSpace[];

u08 pathListSize;
u08 pathListIndex;


u08 updatePath( void );
inline u08 uniformCostSearch( u08 startNode, u08 goalNode /*, SEARCH_NODE searchSpace[]*/ );
struct PathList * addNodeByCost(struct PathList *head, u08 newNodeNum /*, SEARCH_NODE searchSpace[]*/ );
inline void recostructPath( u08 startNode, u08 goalNode /*, SEARCH_NODE searchSpace[]*/ );
u08 updatePathTo( u08 nodeNum );


#endif  // #ifndef
