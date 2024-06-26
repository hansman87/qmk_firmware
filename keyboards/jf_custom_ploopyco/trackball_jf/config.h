/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY
#define PLOOPY_DRAGSCROLL_FIXED 1
#pragma once

<<<<<<< HEAD
=======
#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 5


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 0

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

>>>>>>> d4b0130785 (changes for bastardkb and ploopy)
/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define ROTATIONAL_TRANSFORM_ANGLE 20

// If board has a debug LED, you can enable it by defining this
// #define DEBUG_LED_PIN F7

/* PMW33XX Settings */
#define PMW33XX_CS_PIN             B0
#define POINTING_DEVICE_INVERT_Y
