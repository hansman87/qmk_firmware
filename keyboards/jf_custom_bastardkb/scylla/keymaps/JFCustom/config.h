
#define DYNAMIC_KEYMAP_MACRO_COUNT 8


/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#pragma once

#include "config_common.h"

/* Key matrix configuration. */
#define MATRIX_ROWS 10 // Rows are doubled-up.
#define MATRIX_COLS 6

#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed. */
#undef DEBOUNCE
#define DEBOUNCE 1

/* RGB settings. */
#define RGBLED_NUM 58
#define RGBLED_SPLIT \
    { 29, 29 }

    // Rainbow swirl as startup mode.


/* RGB matrix support. */
#ifdef RGB_MATRIX_ENABLE
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define RGBLIGHT_DEFAULT_SPD 16
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
//#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
//#   define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define RGB_MATRIX_STARTUP_SPD 16
#    define SPLIT_TRANSPORT_MIRROR
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_STARTUP_HUE 0
#    define RGB_MATRIX_STARTUP_SAT 255
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_STARTUP_HSV RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL
#endif  // RGB_MATRIX_ENABLE


