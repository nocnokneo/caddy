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
