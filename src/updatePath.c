/* updatePath.c
 *
 *    AI navigation algorithm.
 *
 */
 
#include "updatePath.h"

u08 pathList[] = INITIAL_PATH_LIST;
SEARCH_NODE searchSpace[NUM_NODES];

void updatePathWithPerms( void )
{
   //SEARCH_NODE searchSpace[NUM_NODES];
}


void updatePathToClosestGoal( void )
{
   //SEARCH_NODE searchSpace[NUM_NODES];
}

void updatePathTo( u08 nodeNum )
{
   uniformCostSearch(botNode,nodeNum);
   pathListIndex = MAX_PATH_LIST_SIZE - 1;
   recostructPath(botNode, nodeNum);
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
         lcdWriteStr("error",0,0);
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
