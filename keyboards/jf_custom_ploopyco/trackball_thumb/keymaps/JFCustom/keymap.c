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
#include QMK_KEYBOARD_H
#define PLOOPY_DRAGSCROLL_INVERT 1



// Tap Dance keycodes
enum td_keycodes {
    MSE_BTN5_LAYR_1, // Our example key: Forward mouse button when held, switch to layer 1,  forward mouse button when tapped.
    MSE_BTN4_PRCSN   // Hold mse btn4 toggles precision mode, tapped send back.
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;
bool td_precision_state = false;
//bool qk_tap_dance_state_t = false;
//bool state = false;
//enum {
//    MSE_BTN5_LAYR_1,
//    MSE_BTN4_PRCSN
//};

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void mseBtn4_finished(qk_tap_dance_state_t *state, void *user_data);
void mseBtn4_reset(qk_tap_dance_state_t *state, void *user_data);
void mseBtn5_finished(qk_tap_dance_state_t *state, void *user_data);
void mseBtn5_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN4, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN5,
        MO(1)
    ),
    [1] = LAYOUT(
        _______, _______, _______, DPI_CONFIG, _______,
        DRAG_SCROLL
    )
};

// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void mseBtn4_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
	    xprintf("Registering button 4\n");
            register_code16(KC_BTN4);
            break;
        case TD_SINGLE_HOLD:
	    xprintf("In precision mode\n");
	    // If we're holding switch to precision mode use the dpi_prec_array
        // to figure out the appropriate precision.
	    pointing_device_set_cpi( dpi_prec_array[keyboard_config.dpi_config] );
            break;
	case TD_NONE:
	case TD_UNKNOWN:
	case TD_DOUBLE_SINGLE_TAP:
	    // Nothing to do
	    break;
    }
}

void mseBtn4_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
	    xprintf("UN-Registering button 4\n");
            unregister_code16(KC_BTN4);
            break;
        case TD_SINGLE_HOLD:
	    xprintf("out of precision mode\n");
	    pointing_device_set_cpi( dpi_array[keyboard_config.dpi_config] );
            break;
	case TD_NONE:
	case TD_UNKNOWN:
	case TD_DOUBLE_SINGLE_TAP:
	    // Nothing to do
	    break;
    }
}
// Handle the possible states for each tapdance keycode you define:
void mseBtn5_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
	    xprintf("Registering button 5\n");
            register_code16(KC_BTN5);
            break;
        case TD_SINGLE_HOLD:
	    layer_on(1);
            break;
	case TD_NONE:
	case TD_UNKNOWN:
	case TD_DOUBLE_SINGLE_TAP:
	    // Nothing to do
	    break;
    }
}

void mseBtn5_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
	    xprintf("UN-Registering button 5\n");
            unregister_code16(KC_BTN5);
            break;
        case TD_SINGLE_HOLD:
	    layer_off(1);
            break;
	case TD_NONE:
	case TD_UNKNOWN:
	case TD_DOUBLE_SINGLE_TAP:
	    // Nothing to do
	    break;
    }
}
// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [MSE_BTN5_LAYR_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mseBtn5_finished, mseBtn5_reset),
    [MSE_BTN4_PRCSN]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mseBtn4_finished, mseBtn4_reset)
};

