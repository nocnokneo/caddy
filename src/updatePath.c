/* updatePath.c
 *
 *    AI navigation algorithm.
 *
 */
 
#include "updatePath.h"

u08 pathList[MAX_PATH_LIST_SIZE];// = INITIAL_PATH_LIST;
SEARCH_NODE searchSpace[NUM_NODES];

// returns distance of path found
u08 updatePath( void )
{
   u08 startCost[NUM_GOALS];
   u08 goalCost[NUM_GOALS][NUM_GOALS];
   u08 stopCost[NUM_GOALS];

	u08 tempGoalList[NUM_GOALS];
	
   u08 curPerm[NUM_GOALS];
	u08 bestPerm[NUM_GOALS];
	u08 bestCost;

	u08 i;
   u08 j;
   u08 tempCost;
      
   // find distances between goal nodes and start/stop nodes
   for( i = 0; i < goalListSize; i++)
   {
      startCost[i] = uniformCostSearch( botNode, goalList[i] );
      stopCost[i] = uniformCostSearch( goalList[i], STOP_NODE );
   }
   
   // find distances between every goal node
   for( i = 0; i < goalListSize; i++)
   {
      for( j = 0; j <= i; j++)
      {
         if( i == j )
            goalCost[i][j] = 0;
         else
         {
            tempCost = uniformCostSearch( goalList[i], goalList[j] );
            goalCost[i][j] = tempCost;
            goalCost[j][i] = tempCost;
         }
      }
   }
   
   // initialize list for permutations
   for( i = 0; i < goalListSize; i++ )
   {
      curPerm[i] = i;
   }
   
   bestCost = MAX_COST;
   
   // make sure goalListSize > 0
	if( goalListSize == 0 )
	{
      // set pathList to STOP_NODE
      return updatePathTo( STOP_NODE );
	}
   
   do
   {
      // Find distance of this permutation
      tempCost = startCost[curPerm[0]];
      for( i = 0; i < goalListSize-1; i++ )
         tempCost += goalCost[curPerm[i]][curPerm[i+1]];
      tempCost += stopCost[curPerm[i]];

      // save tempCost and perm, if this permutation is better
      if( tempCost < bestCost )
      {
         bestCost = tempCost;
         copyList(curPerm, bestPerm, goalListSize);
      }
      
   } while( next_permutation(curPerm, curPerm + goalListSize) );

   // Re-order goalList according to bestPerm.
   copyList(goalList, tempGoalList, goalListSize);
   for( i = 0; i < goalListSize; i++ )
      goalList[i] = tempGoalList[bestPerm[i]];
      
   // Replace current projectedPath with newly found best path
   pathListIndex = MAX_PATH_LIST_SIZE - 1;
   uniformCostSearch( goalList[goalListSize-1], STOP_NODE );
   recostructPath( goalList[goalListSize-1], STOP_NODE );
   for( i = goalListSize-1; i > 0; i-- )
   {
      uniformCostSearch( goalList[i-1], goalList[i] );
      recostructPath( goalList[i-1], goalList[i] );
   }
   uniformCostSearch( botNode, goalList[0] );
   recostructPath( botNode, goalList[0] );


   //printPathList();


   return bestCost;
}

// returns distance of path found
u08 updatePathTo( u08 nodeNum )
{
   u08 tempCost = uniformCostSearch(botNode,nodeNum);
   pathListIndex = MAX_PATH_LIST_SIZE - 1;
   recostructPath(botNode, nodeNum);
   return tempCost;
}

// fills searchSpace with parent information
// returns distance of path found
inline u08 uniformCostSearch( u08 startNode, u08 goalNode /*, SEARCH_NODE searchSpace[NUM_NODES]*/ )
{
   NODE nodeData;
   u08 n;
   
   PATH_LIST_PTR visitList = NULL;
   u08 curNodeNum = startNode;
   u08 curCost = 0;
	
   // init searchSpace
   u08 i;
   for(i = 0; i < NUM_NODES; i++)
   {
      searchSpace[i].parent = NO_PARENT;
		searchSpace[i].pathCost = MAX_COST;
      searchSpace[i].visited = FALSE;
	}
   
   
   searchSpace[startNode].pathCost = 0;
	searchSpace[startNode].visited = TRUE;
	while( curNodeNum != goalNode )
	{
		// explore successors, if haven't visited yet
      getNode(curNodeNum, &nodeData);
      for( i = 0; i < nodeData.numAdjNodes; i++ )
      {
         n = nodeData.adjNodes[i];
         // if not visited and not found yet, add to visit list
			if( !searchSpace[n].visited && searchSpace[n].pathCost == MAX_COST)
			{
				searchSpace[n].parent = curNodeNum;
				searchSpace[n].pathCost = curCost + nodeData.adjCosts[i];
				visitList = addNodeByCost(visitList, n /*, searchSpace*/ );
			}
		}

		// visit next node w/ lowest cost, if one exists
		if(visitList == NULL)
		{
#if DEBUGGING
         lcdWriteStr("uniformCostSearc",0,0);
         lcdWriteStr("error           ",1,0);
         while(1) ;
#endif
			return MAX_COST;  //  b/c path not found
		}
		else
		{
			// get info of and remove first node of visitList
			curNodeNum = visitList->nodeNum;
			curCost = searchSpace[curNodeNum].pathCost;
			searchSpace[curNodeNum].visited = TRUE;
			visitList = freeNode(visitList);
		}
	}
   
   freeList(visitList);
   
   return searchSpace[goalNode].pathCost;
}


PATH_LIST_PTR addNodeByCost(PATH_LIST_PTR head, u08 newNodeNum /*, SEARCH_NODE searchSpace[NUM_NODES]*/ )
{
	PATH_LIST_PTR current = NULL;
	PATH_LIST_PTR next = NULL;
	PATH_LIST_PTR newNode = NULL;      // node being inserted

   // allocate space for new node
	newNode = (PATH_LIST_PTR)malloc(sizeof(PATH_LIST));
	newNode->nodeNum = newNodeNum;
	newNode->nextNode = NULL;

	//add to empty list
	if(head == NULL)
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

		while(next != NULL)
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
inline void recostructPath( u08 startNode, u08 goalNode /*, SEARCH_NODE searchSpace[NUM_NODES]*/ )
{

   pathList[pathListIndex] = goalNode;
   while( goalNode != startNode )
   {
      goalNode = searchSpace[goalNode].parent;
      pathListIndex--;
      pathList[pathListIndex] = goalNode;
   }
}
