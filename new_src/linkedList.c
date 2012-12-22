/* linkedList.c
 *
 *    Linked list functions.
 *
 */
 #include "linkedList.h"

// Frees all nodes in list at head
inline void freeList(PATH_LIST_PTR head)
{
	while(head != NULL)
	{
		head = freeNode(head);
	}
}

// Frees node at head and returns pointer to next node
inline PATH_LIST_PTR freeNode(PATH_LIST_PTR head)
{
	PATH_LIST_PTR temp = NULL;
	temp = head;
	head = head->nextNode;
	free(temp);
	return head;
}

/*

//
// CRoboAIDoc ====== LINKED LIST HELPER FUNCTIONS ================
//

PathList* CRoboAIDoc::appendLast(PathList* head, PathList* newNode)
{
	PathList *current = head;

	if(head == NULL)
	{
		head = newNode;
	}
	else if(newNode != NULL)
	{
		while(current->nextNode != NULL)
		{
			current = current->nextNode;
		}
		current->nextNode = newNode;
	}

	return head;
}

PathList* CRoboAIDoc::addNodeFirst(PathList* head, Coord newCoord)
{
	PathList *current = head;
	PathList *temp = NULL;
	PathList *newNode;
	
	newNode = (struct PathList *)malloc(sizeof(struct PathList));
	newNode->coord = newCoord;
	newNode->nextNode = NULL;

	if(head == NULL)
	{
		head = newNode;
	}
	else
	{
		temp = head;
		head = newNode;
		head->nextNode = temp;
	}
	return head;
}

*/
