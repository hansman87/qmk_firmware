/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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

#include "trackball_thumb.h"

#ifndef OPT_DEBOUNCE
#    define OPT_DEBOUNCE 5  // (ms) 			Time between scroll events
#endif
#ifndef SCROLL_BUTT_DEBOUNCE
#    define SCROLL_BUTT_DEBOUNCE 100  // (ms) 			Time between scroll events
#endif
#ifndef PLOOPY_DPI_OPTIONS
#    define PLOOPY_DPI_OPTIONS \
         { 500, 600, 750, 1000, 1375 }
    #define PLOOPY_DPI_PREC_OPTIONS { 250, 300, 375, 500, 625 }

#    ifndef PLOOPY_DPI_DEFAULT
#        define PLOOPY_DPI_DEFAULT 1
#    endif
#endif
#ifndef PLOOPY_DPI_DEFAULT
#    define PLOOPY_DPI_DEFAULT 0
#endif
#ifndef PLOOPY_DRAGSCROLL_DPI
#    define PLOOPY_DRAGSCROLL_DPI 100  // Fixed-DPI Drag Scroll
#endif
#ifndef PLOOPY_DRAGSCROLL_MULTIPLIER
#    define PLOOPY_DRAGSCROLL_MULTIPLIER 0.75  // Variable-DPI Drag Scroll
#endif
keyboard_config_t keyboard_config;
uint16_t          dpi_array[] = PLOOPY_DPI_OPTIONS;
//uint16_t dpi_prec_array[] = PLOOPY_DPI_PREC_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))
#define PLOOPY_DPI_OPTIONS { 500, 600, 750, 1000, 1375 }


// TODO: Implement libinput profiles
// https://wayland.freedesktop.org/libinput/doc/latest/pointer-acceleration.html
// Compile time accel selection
// Valid options are ACC_NONE, ACC_LINEAR, ACC_CUSTOM, ACC_QUADRATIC

// Trackball State
bool     is_scroll_clicked = false;
uint16_t MotionStart       = 0;      // Timer for accel, 0 is resting state
uint16_t last_scroll       = 0;  // Previous confirmed wheel event
uint16_t last_mid_click    = 0;  // Stops scrollwheel from being read if it was pressed;
bool     debug_encoder     = false;
bool     is_drag_scroll    = false;
uint16_t drag_scroll_cnt = 0;

// require, since core encoder.c (where is is normally defined isn't present
__attribute__((weak)) bool encoder_update_user(uint8_t index, bool clockwise) { return true; }

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
#ifdef MOUSEKEY_ENABLE
    tap_code(clockwise ? KC_WH_U : KC_WH_D);
#else
    report_mouse_t mouse_report = pointing_device_get_report();
    mouse_report.v              = clockwise ? 1 : -1;
    pointing_device_set_report(mouse_report);
    pointing_device_send();
#endif
    return true;
}

void encoder_init(void) { opt_encoder_init(); }

bool encoder_read(void) {
    // Lovingly ripped from the Ploopy Source

    // If the mouse wheel was just released, do not scroll.
    if (timer_elapsed(last_mid_click) < SCROLL_BUTT_DEBOUNCE) {
        return false;
    }

    // Limit the number of scrolls per unit time.
    if (timer_elapsed(last_scroll) < OPT_DEBOUNCE) {
        return false;
    }

    // Don't scroll if the middle button is depressed.
    if (is_scroll_clicked) {
#ifndef IGNORE_SCROLL_CLICK
        return false;
#endif
    }

    last_scroll = timer_read();
    uint16_t p1 = adc_read(OPT_ENC1_MUX);
    uint16_t p2 = adc_read(OPT_ENC2_MUX);
    if (debug_encoder) dprintf("OPT1: %d, OPT2: %d\n", p1, p2);

    int dir = opt_encoder_handler(p1, p2);

    if (dir == 0) return false;
    ;
    encoder_update_kb(0, dir == 1);
    return true;
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (is_drag_scroll) {
        mouse_report.h = mouse_report.x;
#ifdef PLOOPY_DRAGSCROLL_INVERT
        // Invert vertical scroll direction
        mouse_report.v = -mouse_report.y;
#else
        mouse_report.v = mouse_report.y;
#endif
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return pointing_device_task_user(mouse_report);
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    // Update Timer to prevent accidental scrolls
    if ((record->event.key.col == 1) && (record->event.key.row == 0)) {
        last_mid_click    = timer_read();
        is_scroll_clicked = record->event.pressed;
    }

    if (!process_record_user(keycode, record)) {
        return false;
    }

    if (keycode == DPI_CONFIG && record->event.pressed) {
        keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
        eeconfig_update_kb(keyboard_config.raw);
        pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
    }

    if (keycode == DRAG_SCROLL) {
#ifndef PLOOPY_DRAGSCROLL_MOMENTARY
        if (record->event.pressed)
#endif
        {
            is_drag_scroll ^= 1;
        }

#ifdef PLOOPY_DRAGSCROLL_FIXED
        pointing_device_set_cpi(is_drag_scroll ? PLOOPY_DRAGSCROLL_DPI : dpi_array[keyboard_config.dpi_config]);
#else
        pointing_device_set_cpi(is_drag_scroll ? (dpi_array[keyboard_config.dpi_config] * PLOOPY_DRAGSCROLL_MULTIPLIER) : dpi_array[keyboard_config.dpi_config]);
#endif
    }

/* If Mousekeys is disabled, then use handle the mouse button
 * keycodes.  This makes things simpler, and allows usage of
 * the keycodes in a consistent manner.  But only do this if
 * Mousekeys is not enable, so it's not handled twice.
 */
#ifndef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t currentReport = pointing_device_get_report();
        if (record->event.pressed) {
            currentReport.buttons |= 1 << (keycode - KC_MS_BTN1);
        } else {
            currentReport.buttons &= ~(1 << (keycode - KC_MS_BTN1));
        }
        pointing_device_set_report(currentReport);
        pointing_device_send();
    }
#endif

    return true;
}

// Hardware Setup
void keyboard_pre_init_kb(void) {
    // debug_enable  = true;
    // debug_matrix  = true;
    // debug_mouse   = true;
    // debug_encoder = true;

    setPinInput(OPT_ENC1);
    setPinInput(OPT_ENC2);

    /* Ground all output pins connected to ground. This provides additional
     * pathways to ground. If you're messing with this, know this: driving ANY
     * of these pins high will cause a short. On the MCU. Ka-blooey.
     */
#ifdef UNUSABLE_PINS
    const pin_t unused_pins[] = UNUSABLE_PINS;

    for (uint8_t i = 0; i < (sizeof(unused_pins) / sizeof(pin_t)); i++) {
        setPinOutput(unused_pins[i]);
        writePinLow(unused_pins[i]);
    }
#endif

    // This is the debug LED.
#if defined(DEBUG_LED_PIN)
    setPinOutput(DEBUG_LED_PIN);
    writePin(DEBUG_LED_PIN, debug_enable);
#endif

    keyboard_pre_init_user();
}

void pointing_device_init_kb(void) { pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]); }

void eeconfig_init_kb(void) {
    keyboard_config.dpi_config = PLOOPY_DPI_DEFAULT;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    // is safe to just read DPI setting since matrix init
    // comes before pointing device init.
    keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.dpi_config > DPI_OPTION_SIZE) {
        eeconfig_init_kb();
    }
    matrix_init_user();
}
