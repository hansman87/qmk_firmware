/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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


//check numlock and turn on when needed
// static void check_numlock(void) {
//     Host Keyboard LED Status
//     led_t led_state = host_keyboard_led_state();
//     if (!(led_state.num_lock)){
//         tap_code16(KC_NLCK);
//     }
// };


enum scylla_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_SPECIAL,
    LAYER_GAMING,
};

uint16_t hue = 213;
uint16_t sat = 255;
uint16_t val = 180;

/*void get_blstate(void) {
 *    hue = rgblight_get_hue();
 *    sat = rgblight_get_sat();
 *    val = rgblight_get_val();
 * }
 *
 * void reset_blstate(void) {
 *    rgblight_sethsv_noeeprom(hue, sat, val);
 * }
 */
void get_blstate(void) {
    val = rgblight_get_val();
}

void reset_blstate(void) {
    hue = rgblight_get_hue();
    sat = rgblight_get_sat();
    rgblight_sethsv_noeeprom(hue, sat, val);
}




#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_4x6_5(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    LT(2, KC_R),    KC_T,       KC_Y,    LT(2, KC_U),    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    LT(1, KC_F),    KC_G,       KC_H,    LT(1, KC_J), KC_K, KC_L, KC_SCLN, KC_RSFT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    KC_Z,    KC_X,    KC_C,    LT(3, KC_V),    KC_B,       KC_N,    LT(3, KC_M), KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_BSPC, KC_SPC,   DF(4),      KC_RGUI,  KC_ENTER,KC_HOME,
                                           KC_DEL, KC_CLCK,     KC_RALT,KC_EQL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT_split_4x6_5(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       RGB_MOD, RGB_TOG,   RGB_RMOD, BL_STEP,  RGB_VAI, RGB_VAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_TAB, XXXXXXX, KC_HOME, KC_UP, KC_PGUP, XXXXXXX,    KC_LBRC,   KC_P7,   KC_P8,   KC_P9, KC_RBRC, KC_NUMLOCK,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,    KC_PPLS,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_EQUAL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      _______, XXXXXXX, KC_END, KC_PGDN, KC_PGDOWN, XXXXXXX,    KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_PDOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, DF(0),    _______, _______,KC_P0,
                                           _______, _______,      _______,_______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT_split_4x6_5(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_ESC, KC_MNXT, KC_HOME, KC_UP, KC_PGUP, XXXXXXX,    XXXXXXX, KC_PGUP, KC_UP, KC_HOME, KC_VOLU, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSHIFT, KC_MPLY,   KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,    KC_BTN1, KC_LEFT, KC_DOWN, KC_RGHT, KC_MUTE, KC_RSFT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_MPRV, KC_END, KC_PGDN,  KC_PGDOWN, XXXXXXX,    KC_BTN2, KC_PGDOWN, XXXXXXX, KC_END, KC_VOLD, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    KC_RGUI, XXXXXXX,XXXXXXX,
                                           KC_DEL, KC_RCTL,    KC_RALT,XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

      [LAYER_SPECIAL] = LAYOUT_split_4x6_5(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRACKET, KC_RBRACKET, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_LBRACKET, XXXXXXX, KC_SCOLON, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSHIFT, KC_QUOTE, KC_MINUS, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_RSFT, KC_LBRACKET, KC_RBRACKET, XXXXXXX, KC_RSHIFT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST, QK_BOOT,    QK_BOOT, EEP_RST, LSFT(KC_LBRACKET), LSFT(KC_RBRACKET), XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,XXXXXXX,
                                           XXXXXXX, XXXXXXX,    XXXXXXX,XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
    [LAYER_GAMING] = LAYOUT_split_4x6_5(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J, KC_K, KC_L, KC_SCLN, KC_RSFT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_BSPC, KC_SPC,   DF(1),      KC_RGUI,  KC_ENTER,XXXXXXX,
                                           KC_DEL, KC_RCTL,     KC_RALT,XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void matrix_init_user(void) {
    //rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
    rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
    get_blstate();
    register_code(KC_NUMLOCK);

//     if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
//       register_code(KC_NUMLOCK);
//       unregister_code(KC_NUMLOCK);
//   }
};
// void led_set_keymap(uint8_t usb_led) {
//   if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
//     register_code(KC_NUMLOCK);
//     unregister_code(KC_NUMLOCK);
//     rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
//     rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
//     rgb_matrix_update_pwm_buffers();
//   }
// }
//#define RBG_VAL 120

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(biton32(state)) {
        case LAYER_BASE:
            get_blstate();
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
            //rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
            reset_blstate();
            break;
        case LAYER_LOWER:
            get_blstate();
            rgblight_sethsv_noeeprom(HSV_RED);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            reset_blstate();
            break;
        case LAYER_RAISE:
            get_blstate();
            rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            reset_blstate();
            break;
        case LAYER_SPECIAL:
            get_blstate();
            rgblight_sethsv_noeeprom(HSV_BLUE);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            reset_blstate();
            break;
        case LAYER_GAMING:
            get_blstate();
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            reset_blstate();
            break;
        default:
            get_blstate();
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
            //rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
            rgblight_set_speed_noeeprom(60);
            reset_blstate();
            break;
    }
    return state;
}

layer_state_t default_layer_state_set_kb (layer_state_t state) {
    switch(biton32(state)) {
        case LAYER_BASE:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
            //rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
            break;
        case LAYER_GAMING:
            get_blstate();
            rgblight_sethsv_noeeprom(HSV_GREEN);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            reset_blstate();
            break;
        case LAYER_LOWER:
            get_blstate();
            rgblight_sethsv_noeeprom(HSV_RED);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            reset_blstate();
            break;
        default:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
            //rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
            rgblight_set_speed_noeeprom(60);
            break;
    }
    return state;
}

void shutdown_user(void) {
    #ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
    //   rgblight_setrgb_blue();
    #endif // RGBLIGHT_ENABLE
    #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
    //rgb_matrix_set_color_all(RGB_BLUE);
    rgb_matrix_update_pwm_buffers();
    #endif // RGB_MATRIX_ENABLE
}
