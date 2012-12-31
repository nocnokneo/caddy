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
 * @brief Simple user interface to change parameters without reprogramming
 *
 * The user interface is implemented as push buttons and LEDs on a small
 * solder-less breadboard connected to Caddy using CAT5 cable and RJ-45
 * connector for quick and easy attach/detach.
 */
#ifndef TETHERUI_H_
#define TETHERUI_H_

#define NAV_LCD_MODE        0
#define LINE_LCD_MODE       1

inline void runTetherUI(void);

#endif // #ifndef TETHERUI_H_
