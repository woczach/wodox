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
 * Macros (previously Vial EEPROM macros 0-15):
 *   MACRO_0 = Ctrl+Alt+Shift+X
 *   MACRO_2 = Ctrl+Alt+Shift+Z
 */
enum custom_keycodes {
    MACRO_0 = SAFE_RANGE,
    MACRO_2,
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
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, KC_F11,
        _______, _______, _______, _______, _______,                KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_F12,
        MACRO_2, MACRO_0, _______, _______, _______,                _______, _______, _______, _______, _______,
        _______, _______, KC_HOME,                                   KC_VOLD, KC_VOLD,_______,
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

/* Breathing brightness, phase-shifted so neighbouring keys pulse together. */
static RGB breathe(uint8_t hue, uint8_t phase) {
    uint8_t val = (uint8_t)(140 + 115 * sinf((float)(timer_read32() + phase * 40) / 900.0f));
    return hsv_to_rgb((HSV){hue, 255, val});
}

/*
 * Per-layer RGB. The base layer keeps the configured default animation.
 *   NUMPAD: numbers rainbow-breathe, * red, + orange, - green, / blue, . yellow
 *   NAV:    F-keys rainbow-breathe, arrows green->red, other keys tinted
 *   ALT:    only the keys present on the layer glow (rainbow breathe)
 */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (layer_state_is(_NAV)) {
        rgb_matrix_set_color_all(RGB_BLACK);
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint8_t   i   = g_led_config.matrix_co[row][col];
                keypos_t  key = {.row = row, .col = col};
                uint16_t  kc  = keymap_key_to_keycode(_NAV, key);
                if (i == NO_LED || i < led_min || i >= led_max || kc == KC_TRANSPARENT || kc == KC_NO) {
                    continue;
                }
                if (kc >= KC_F1 && kc <= KC_F12) {
                    uint8_t f   = kc - KC_F1;
                    RGB     rgb = breathe((uint8_t)(f * 255 / 12 + timer_read32() / 24), f);
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                    continue;
                }
                switch (kc) {
                    case KC_LEFT: {
                        RGB c = hsv_to_rgb((HSV){85, 255, 255});
                        rgb_matrix_set_color(i, c.r, c.g, c.b);
                        break;
                    }
                    case KC_DOWN: {
                        RGB c = hsv_to_rgb((HSV){57, 255, 255});
                        rgb_matrix_set_color(i, c.r, c.g, c.b);
                        break;
                    }
                    case KC_UP: {
                        RGB c = hsv_to_rgb((HSV){28, 255, 255});
                        rgb_matrix_set_color(i, c.r, c.g, c.b);
                        break;
                    }
                    case KC_RGHT: {
                        RGB c = hsv_to_rgb((HSV){0, 255, 255});
                        rgb_matrix_set_color(i, c.r, c.g, c.b);
                        break;
                    }
                    case MACRO_0:
                        rgb_matrix_set_color(i, RGB_CYAN);
                        break;
                    case MACRO_2:
                        rgb_matrix_set_color(i, RGB_MAGENTA);
                        break;
                    case KC_HOME:
                        rgb_matrix_set_color(i, RGB_PURPLE);
                        break;
                    case KC_VOLD:
                        rgb_matrix_set_color(i, RGB_WHITE);
                        break;
                }
            }
        }
        return true;
    }

    if (layer_state_is(_NUMPAD)) {
        rgb_matrix_set_color_all(RGB_BLACK);
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint8_t   i   = g_led_config.matrix_co[row][col];
                keypos_t  key = {.row = row, .col = col};
                uint16_t  kc  = keymap_key_to_keycode(_NUMPAD, key);
                if (i == NO_LED || i < led_min || i >= led_max || kc == KC_TRANSPARENT || kc == KC_NO) {
                    continue;
                }
                switch (kc) {
                    case KC_KP_1 ... KC_KP_9:
                    case KC_KP_0: {
                        uint8_t n   = (kc == KC_KP_0) ? 0 : (uint8_t)(kc - KC_KP_1 + 1);
                        RGB     rgb = breathe((uint8_t)(n * 255 / 10 + timer_read32() / 24), n);
                        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                        break;
                    }
                    case KC_KP_ASTERISK:
                        rgb_matrix_set_color(i, RGB_RED);
                        break;
                    case KC_KP_PLUS:
                        rgb_matrix_set_color(i, RGB_ORANGE);
                        break;
                    case KC_KP_MINUS:
                        rgb_matrix_set_color(i, RGB_GREEN);
                        break;
                    case KC_KP_SLASH:
                        rgb_matrix_set_color(i, RGB_BLUE);
                        break;
                    case KC_KP_DOT:
                        rgb_matrix_set_color(i, RGB_YELLOW);
                        break;
                }
            }
        }
        return true;
    }

    if (layer_state_is(_ALT)) {
        rgb_matrix_set_color_all(RGB_BLACK);
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint8_t   i   = g_led_config.matrix_co[row][col];
                keypos_t  key = {.row = row, .col = col};
                uint16_t  kc  = keymap_key_to_keycode(_ALT, key);
                if (i == NO_LED || i < led_min || i >= led_max || kc == KC_TRANSPARENT || kc == KC_NO) {
                    continue;
                }
                uint8_t phase = (uint8_t)(row * 6 + col * 3);
                RGB     rgb   = breathe((uint8_t)(phase * 8 + timer_read32() / 24), phase);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
        return true;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MACRO_0:
            if (record->event.pressed) {
                tap_code16(MEH(KC_X));
            }
            return false;
        case MACRO_2:
            if (record->event.pressed) {
                tap_code16(MEH(KC_Z));
            }
            return false;
    }
    return true;
}
