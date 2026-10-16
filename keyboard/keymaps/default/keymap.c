// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <math.h>

enum layers {
    _BASE,
    _NUMPAD,
    _SYM,
    _NAV,
    _MOUSE,
    _L5,
    _L6,
    _ALT,
};

/*
 *      ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
 *      │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │       │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
 *      ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
 *      │ ` │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │ = │
 *      ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
 *      │ A │ S │ D │ F │ G │           │ H │ J │ K │ L │ ; │
 *      ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
 *      │ Z │ X │ C │ V │ B │           │ N │ M │ , │ . │ / │
 *      └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
 *               ┌───┬───┬───┐         ┌───┬───┬───┐
 *               │Esc│Shf│Num│         │ ↑ │Ent│ ' │
 *               ├───┼───┼───┤         ├───┼───┼───┤
 *               │Bsp│Tab│Del│         │ ↓ │Sft│Spc│
 *               └───┴───┴───┘         └───┴───┴───┘
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        // left                          right
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_PGUP, 	KC_MINS,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_PGDN,    	KC_EQL, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   
        LCTL_T(KC_A), KC_S, KC_D, LCTL_T(KC_F), LSFT_T(KC_G),       LSFT_T(KC_H), LCTL_T(KC_J), KC_K, KC_L, RGUI_T(KC_SCLN),
        KC_Z,    KC_X,    KC_C,    LT(_NUMPAD, KC_V), KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH,
        // left thumbs                   right thumbs
        LT(_NAV, KC_ESC), KC_GRV, KC_PSCR,                    KC_HOME,   KC_END,  LT(_NAV, KC_QUOT),
        KC_BSPC, LT(_ALT, KC_TAB), KC_DEL,                         LT(_NUMPAD, KC_BSLS), LT(_NAV, KC_ENT), KC_SPC
    ),

    /* numpad, hold V or toggle with left thumb Num */
    [_NUMPAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, KC_PAST, KC_PSLS, KC_PMNS, _______, _______,
        _______, _______, _______, _______, _______, _______,       _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
        _______, _______, _______, _______, _______,                KC_P4,   KC_P5,   KC_P6,   _______, _______,
        _______, _______, _______, _______, _______,                KC_P1,   KC_P2,   KC_P3,   _______, _______,
        _______, _______, _______,                                   _______, KC_PENT, _______,
        _______, _______, _______,                                   _______, KC_PDOT, KC_P0
    ),

    [_SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,
        _______, _______, _______,                                   _______, _______, _______,
        _______, _______, _______,                                   _______, _______, _______
    ),

    /* navigation / F-keys, hold left thumb Esc */
    [_NAV] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______,	 _______, KC_F6, KC_F7,   KC_F8,   KC_F9,   KC_F10,
        _______, _______, _______, _______, _______, KC_LBRC,       KC_RBRC, _______, _______, _______, _______, KC_F11,
        _______, _______, _______, _______, _______,                KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_F12,
        _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,
        _______, KC_PGUP, KC_HOME,                                   KC_VOLD, KC_VOLD,KC_PSCR,
        _______,_______,_______,				     _______,_______,_______
    ),

    /* mouse, hold S */
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,       _______, _______, MS_BTN1, MS_UP,   MS_BTN2, _______,
        _______, _______, _______, _______, _______,                _______, MS_LEFT, MS_DOWN, MS_RGHT, _______,
        _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,
        _______, _______, _______,                                   _______, _______, _______,
        _______, _______, _______,                                   _______, _______, _______
    ),

    [_L5] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,
        _______, _______, _______,                                   _______, _______, _______,
        _______, _______, _______,                                   _______, _______, _______
    ),

    [_L6] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,
        _______, _______, _______,                                   _______, _______, _______,
        _______, _______, _______,                                   _______, _______, _______
    ),

    /* alt shortcuts, hold left thumb Tab */
    [_ALT] = LAYOUT(
        LALT(KC_1), LALT(KC_2), LALT(KC_3), LALT(KC_4), LALT(KC_5), _______,    _______, _______, _______, _______, _______, _______,
        LALT(KC_Q), _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______,
        LSFT(LALT(KC_1)), LSFT(LALT(KC_2)), LSFT(LALT(KC_3)), LSFT(LALT(KC_4)), LSFT(LALT(KC_5)),    _______, _______, _______, LALT(KC_SCLN), _______,
        LALT(KC_Z), LALT(KC_X), LALT(KC_C), LALT(KC_V), LALT(KC_B),             _______, _______, _______, _______, _______,
        _______, _______, _______,                                              LALT(KC_UP), LALT(KC_RGHT), _______,
        _______, _______, _______,                                              LALT(KC_DOWN), _______, LALT(KC_LEFT)
    ),
};

enum combo_events {
    CB_YU_LPRN,
    CB_UI_RPRN,
    CB_HJ_LBRC,
    CB_JK_RBRC,
    CB_NM_LCBR,
    CB_MCOMM_RCBR,
};

const uint16_t PROGMEM cb_yu[]    = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM cb_ui[]    = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM cb_hj[]    = {LSFT_T(KC_H), LCTL_T(KC_J), COMBO_END};
const uint16_t PROGMEM cb_jk[]    = {LCTL_T(KC_J), KC_K, COMBO_END};
const uint16_t PROGMEM cb_nm[]    = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM cb_mcomm[] = {KC_M, KC_COMM, COMBO_END};

combo_t key_combos[] = {
    [CB_YU_LPRN]    = COMBO(cb_yu, KC_LPRN),
    [CB_UI_RPRN]    = COMBO(cb_ui, KC_RPRN),
    [CB_HJ_LBRC]    = COMBO(cb_hj, KC_LBRC),
    [CB_JK_RBRC]    = COMBO(cb_jk, KC_RBRC),
    [CB_NM_LCBR]    = COMBO(cb_nm, KC_LCBR),
    [CB_MCOMM_RCBR] = COMBO(cb_mcomm, KC_RCBR),
};

/* Numpad layer indicator: numbers red, + blue, - pulsing yellow, rest off */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!layer_state_is(_NUMPAD)) {
        return true;
    }
    rgb_matrix_set_color_all(RGB_BLACK);
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t   i   = g_led_config.matrix_co[row][col];
            keypos_t  key = {.row = row, .col = col};
            if (i == NO_LED || i < led_min || i >= led_max) {
                continue;
            }
            switch (keymap_key_to_keycode(_NUMPAD, key)) {
                case KC_KP_1 ... KC_KP_9:
                case KC_KP_0:
                    rgb_matrix_set_color(i, RGB_RED);
                    break;
                case KC_KP_PLUS:
                    rgb_matrix_set_color(i, RGB_BLUE);
                    break;
                case KC_KP_MINUS: {
                    uint8_t v   = (uint8_t)(127.0f + 127.0f * sinf(timer_read32() / 300.0f));
                    RGB     rgb = hsv_to_rgb((HSV){43, 255, v});
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                    break;
                }
            }
        }
    }
    return true;
}
