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
// linkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "caddy.h"
#include <stdint.h>

typedef struct PathList
{
	uint8_t nodeNum;
	struct PathList * nextNode;
} PATH_LIST ;

typedef struct PathList *   PATH_LIST_PTR;


inline void freeList(PATH_LIST_PTR head);
inline PATH_LIST_PTR freeNode(PATH_LIST_PTR head);


#endif  // #ifndef
