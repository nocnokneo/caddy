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
