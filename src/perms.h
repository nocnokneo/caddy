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
// perms.h
#ifndef PERMS_H
#define PERMS_H

#include "caddy.h"
#include <stdint.h>
#include <stdbool.h>

bool next_permutation(uint8_t *first, uint8_t *last);
void iter_swap(uint8_t *a, uint8_t *b);
void iter_reverse(uint8_t *a, uint8_t *b);

#endif // #ifndef
