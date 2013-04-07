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
 * @brief Global project include file (required by AVRLIB)
 *
 * A file of the name global.h is required by the AVRLIB and must contain, at
 * a minimum, a defining for F_CPU.
 */
#ifndef GLOBAL_H_
#define GLOBAL_H_

// global AVRLIB defines
#include "avrlibdefs.h"
// global AVRLIB types definitions
#include "avrlibtypes.h"

/** CPU clock speed [Hz]. (macro required by AVRLIB) */
#define F_CPU        16000000
/** CPU cycles per microsecond. (macro required by AVRLIB) */
#define CYCLES_PER_US ((F_CPU+500000)/1000000)

#endif /* end ifndef GLOBAL_H_ */
