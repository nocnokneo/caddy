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
// ourLcd.h
#ifndef OURLCD_H
#define OURLCD_H

#include <stdint.h>
#include <avr/io.h>

// LCD display geometry
#define LCD_LINES				2	//< visible lines
#define LCD_LINE_LENGTH			16	//< line length (in characters)

// Prototypes
void lcdInit(void);
void lcdPrintHex(uint8_t data, uint8_t row, uint8_t col);
void lcdPrintDec(int8_t data, uint8_t row, uint8_t col);

/**
 * @brief Print a string to the LCD
 *
 * Stops when a null (\0) is reached or 16 chars have been printed.
 *
 * @param str[in] Null-terminated string to print (max 16 chars)
 * @param row[in] Zero-based LCD row number to print on
 * @param col[in] Zero-based LCD column to print first character
 */
void lcdWriteStr(const char *str, uint8_t row, uint8_t col);

/**
 * @brief Print a 8-bit value to the LCD in decimal notation (2-3 characters)
 */
void lcdPrintDecU08(uint8_t data, uint8_t row, uint8_t col);
void lcdPrintDecS08(int8_t data, uint8_t row, uint8_t col);

#endif  // #ifndef
