/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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

enum my_rgb_layers {
    _BASE = 0,
    _NUMPAD = 1,
    _NOUSE = 2,
    _MAC = 3,
    _GAME = 4,
    _FLASH = 5,
};

uint16_t hue[5];
uint16_t sat[5];
uint16_t val[5];

static int NumberOfLayers = 5;

int default_layer = 0;
int current_layer = 0;
// bool has_layer_changed = false;
// static uint8_t current_layer;
//uint16_t hue = 255;
//uint16_t sat = 255;
//uint16_t val = 255;

void set_mode_breath(int current_layer)
{
    rgblight_sethsv(HSV_WHITE);  // Set it to white by default
    rgblight_mode(RGBLIGHT_MODE_BREATHING); // set to breathing by default
}

void set_mode_rainbow(int current_layer)
{
   //rgblight_sethsv(HSV_WHITE);  // Set it to white by default
    rgblight_enable();
    rgblight_sethsv(hue[current_layer], sat[current_layer], val[current_layer]);
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD); // set to breathing by default
}

void set_mode_breath_noeeprom(int current_layer)
{
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(hue[current_layer], sat[current_layer], val[current_layer]);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING); // set to breathing by default
}

void set_mode_static_noeeprom(int current_layer)
{
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); // set to breathing by default
}

void set_mode_rainbow_noeeprom(int current_layer)
{
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD); // set to breathing by default
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    // use the non noeeprom versions, to write these values to EEPROM too
    //rgblight_enable(); // Enable RGB by default
    set_mode_rainbow(0);
}

void get_blstate(int current_layer) {

    val[current_layer] = rgblight_get_val();
    hue[current_layer] = rgblight_get_hue();
    sat[current_layer] = rgblight_get_sat();
}

void reset_blstate(int current_layer) {

    rgblight_sethsv_noeeprom(hue[current_layer], sat[current_layer], val[current_layer]);
}

int delay_runonce;
// initializes a timer used to delay rgblight function invocation until the eeprom has
// already been read
void prepare_to_dong_rgblight_into_submission_I_mean_initialize_it(void) {
  delay_runonce = timer_read();
}



//waits until a delay timer has elapsed and then initializes rgblight without touching
//the eeprom
void dong_rgblight_into_submission_I_mean_initialize_it(void) {
  static bool runonce = true;
  if (runonce && (timer_elapsed(delay_runonce) > 2000)) {
      for (int i = 0; i < NumberOfLayers; i++)
  {
      hue[i] = 255;
      sat[i] = 255;
      val[i] = 255;
}
    runonce = false;
    set_mode_rainbow(0);
  }

}

layer_state_t layer_state_set_user(layer_state_t state) {
    get_blstate(biton32(state));
    switch(biton32(state)) {
        case 0:
            set_mode_rainbow_noeeprom(biton32(state));
            break;
        case 1:
           set_mode_static_noeeprom(biton32(state));
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case 2:
            set_mode_static_noeeprom(biton32(state));
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case 3:
            set_mode_breath_noeeprom(biton32(state));
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case 4:
            set_mode_breath_noeeprom(biton32(state));
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case 5:
            set_mode_static_noeeprom(biton32(state));
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        default:
            if (default_layer == 0 )
            {
                set_mode_rainbow_noeeprom(biton32(state));
            }
            if (default_layer == 3)
            {
                set_mode_breath_noeeprom(biton32(state));
                rgblight_sethsv_noeeprom(HSV_ORANGE);
            }
            if (default_layer == 4)
            {
                set_mode_breath_noeeprom(biton32(state));
                rgblight_sethsv_noeeprom(HSV_GREEN);
            }
            break;
    }
    reset_blstate(biton32(state));
    return state;
}


layer_state_t default_layer_state_set_user(layer_state_t state) {
    get_blstate(biton32(state));
    switch(biton32(state)) {
        case 0:
            default_layer = 0;
            set_mode_rainbow_noeeprom(biton32(state));
            break;
        case 3:
            default_layer = 3;
            set_mode_breath_noeeprom(biton32(state));
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case 4:
            default_layer = 4;
            set_mode_breath_noeeprom(biton32(state));
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;

        default:
            if (default_layer == 0 )
            {
                set_mode_rainbow_noeeprom(biton32(state));
            }
            else if (default_layer == 3)
            {
                set_mode_breath_noeeprom(biton32(state));
                rgblight_sethsv_noeeprom(HSV_ORANGE);
            }
            else if (default_layer == 4)
            {
                set_mode_breath_noeeprom(biton32(state));
                rgblight_sethsv_noeeprom(HSV_GREEN);
            } else
            {
                set_mode_breath_noeeprom(biton32(state));
                rgblight_sethsv_noeeprom(HSV_GREEN);
            }
            break;
    }
    reset_blstate(biton32(state));
    return state;
}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        [0] = LAYOUT_split_4x6_5( KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
                             KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
                             KC_LSFT, KC_A, KC_S, KC_D, LT(1,KC_F), KC_G, KC_H, LT(1,KC_J), KC_K, KC_L, KC_SCLN, KC_RSFT,
                             KC_LCTL, KC_Z, KC_X, KC_C, LT(5,KC_V), KC_B, KC_N, LT(5,KC_M), KC_COMM, KC_DOT, KC_SLSH, KC_QUOT,
                             KC_RGUI, KC_LALT, KC_WH_D, KC_WH_U, KC_VOLD, KC_VOLU, KC_GRV, KC_APP,
                             KC_BSPC, KC_SPC, KC_LGUI, KC_ENT,
                             KC_INS, DF(3), KC_HOME, KC_END,
                             KC_DEL, KC_CAPS, KC_NUM, KC_RALT ),

        [1] = LAYOUT_split_4x6_5( KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
                             KC_TAB, KC_NO, KC_HOME, KC_UP, KC_PGUP, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_NO, KC_NUM,
                             KC_LSFT, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_PPLS, KC_P4, KC_P5, KC_P6, KC_NO, KC_PEQL,
                             KC_LCTL, KC_NO, KC_END, KC_NO, KC_PGDN, KC_NO, KC_PAST, KC_P1, KC_P2, KC_P3, KC_PSLS, KC_NO,
                             KC_LGUI, KC_LALT, KC_NO, KC_NO, KC_PCMM, KC_PDOT, KC_NO, KC_NO,
                             KC_BSPC, KC_SPC, KC_RGUI, KC_P0,
                             KC_INS, KC_NO, KC_HOME, KC_END,
                             KC_DEL, KC_CAPS, QK_BOOT, KC_RALT ),

        [2] = LAYOUT_split_4x6_5( KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, EE_CLR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_TRNS, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO ) ,

        [3] = LAYOUT_split_4x6_5( KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_RCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_LCTL, KC_TRNS,
                          KC_TRNS, DF(4), KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ) ,

        [4] = LAYOUT_split_4x6_5( KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
                                 KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
                                 KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_P, KC_BSLS,
                                 KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
                                 KC_LCTL, KC_LALT, KC_DOWN, KC_UP, KC_LEFT, KC_RGHT, KC_BSLS, KC_APP,
                                 KC_BSPC, KC_SPC, KC_LGUI, KC_ENT,
                                 KC_INS, DF(0), KC_HOME, KC_END,
                                 KC_DEL, KC_CAPS, KC_NUM, KC_LALT ),

        [5] = LAYOUT_split_4x6_5( KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, EE_CLR, KC_NO, KC_LBRC, KC_RBRC, KC_NO, KC_NO,
                                 KC_TRNS, KC_NO, KC_NO, DB_TOGG, KC_NO, QK_BOOT, QK_BOOT, KC_NO, LSFT(KC_LBRC), LSFT(KC_RBRC), KC_NO, KC_TRNS,
                                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                 KC_NO, KC_NO, KC_NO, KC_NO,
                                 KC_NO, KC_NO, KC_NO, KC_NO,
                                 KC_NO, KC_NO, KC_NO, KC_NO ),
};

