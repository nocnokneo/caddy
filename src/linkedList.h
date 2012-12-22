// linkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "caddy.h"

typedef struct PathList
{
	u08 nodeNum;
	struct PathList * nextNode;
} PATH_LIST ;

typedef struct PathList *   PATH_LIST_PTR;


inline void freeList(PATH_LIST_PTR head);
inline PATH_LIST_PTR freeNode(PATH_LIST_PTR head);


#endif  // #ifndef
