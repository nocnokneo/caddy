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
#include "perms.h"

static void swap(uint8_t *a, uint8_t *b);
static void reverseArray(uint8_t *first, uint8_t *last);

bool generateNextPermutation(uint8_t *first, uint8_t *last)
{
    uint8_t *i = last - 1;
    if (first == last || first == i) // check for n=0 or n=1
        return false;

    for (;;)
    {
        uint8_t *ii = i--;
        if (*i < *ii)
        {
            uint8_t *j = last;
            while (!(*i < *--j)) ;

            swap(i, j);
            reverseArray(ii, last);

            return true;
        }
        if (i == first)
        {
            reverseArray(first, last);
            return false;
        }
    }

    // Should not reach this line
    return false;
}

/**
 * @brief Swap two values
 *
 * @param[in,out] a Pointer to value that should be copied to location pointed
 *                  to by b
 * @param[in,out] b Pointer to value that should be copied to location pointed
 *                  to by a
 */
static void swap(uint8_t *a, uint8_t *b)
{
    uint8_t tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @brief Reverse the order of elements in an array
 *
 * Optimized for space efficiency over speed.
 *
 * @param[in,out] head  Pointer to first element of array
 * @param[in,out] tail  Pointer to one element \em past the last element of
 *                      the array
 */
static void reverseArray(uint8_t *first, uint8_t *last)
{
    last--; // point last to element to begin reversing

    if (first < last)
    {
        while (first < last)
            swap(first++, last--);
    }
    else
    {
        while (last < first)
            swap(last++, first--);
    }
}
