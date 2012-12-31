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
/* perms.h
 *
 * Generate permutations iteratively - not recursively because there stack
 * space is limited
 *
 */

#include "perms.h"
#include <stdint.h>
#include <stdbool.h>

bool next_permutation(uint8_t *first, uint8_t *last)
{
    uint8_t *i = last - 1;
    if (first == last)    // check for n=0
        return false;
    if (first == i)       // check for n=1
        return false;

    for (;;)
    {
        uint8_t *ii = i--;
        if (*i < *ii)
        {
            uint8_t *j = last;
            while (!(*i < *--j)) ;

            iter_swap(i, j);
            iter_reverse(ii, last);

            return true;
        }
        if (i == first)
        {
            iter_reverse(first, last);
            return false;
        }
    }

    return false;
}

// b points to element to swap with a.
void iter_swap(uint8_t *a, uint8_t *b)
{
    uint8_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

// b points one element beyond the last element be reversing
void iter_reverse(uint8_t *a, uint8_t *b)
{
    b--;                // point b to element to begin reversing

    if (a < b)
    {
        while (a < b)
            iter_swap(a++, b--);
    }
    else
    {
        while (b < a)
            iter_swap(b++, a--);
    }
}
