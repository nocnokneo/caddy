// linkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "caddy.h"

typedef struct PathList     PATH_LIST;
typedef struct PathList *   PATH_LIST_PTR;
struct PathList
{
	u08 nodeNum;
	PATH_LIST_PTR nextNode;
};



inline void freeList(PATH_LIST_PTR head);
inline PATH_LIST_PTR freeNode(PATH_LIST_PTR head);


#endif  // #ifndef
