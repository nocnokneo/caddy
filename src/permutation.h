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
/**
 * @file
 * @brief Iterative (non-recursive!) permutation generator
 */
#ifndef PERMS_H_
#define PERMS_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Reorder an array of values to the next higher permutation
 *
 * The "next higher" permuation is the one that is lexicographically one step
 * higher than the input order. The order that would compare smaller to all
 * other permutations is the one in which all elements are sorted in ascending
 * order.  This is the initial order that should be used in order to cycle
 * through all possible permutations.
 *
 * Typical usage example:
 *
 * @code
 * uint8_t myArray[] = { 1, 2, 3 };
 * do {
 *     // ... do something with current permuation of myArray
 * } while (generateNextPermutation(myArray, myArray + 3);
 * @endcode
 *
 * @remarks This iterative permutation generation algorithm was taken, with
 * slight modifications, from the GNU implementation of the C++ STL
 * (libstdc++). It was chosen for for its lower memory usage over simpler and
 * more common recursive implementations.
 *
 * @return true if the next higher permutation could be generated, false
 * otherwise
 */
bool generateNextPermutation(uint8_t *first, uint8_t *last);

#endif // #ifndef PERMS_H_
