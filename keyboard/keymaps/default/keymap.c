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

    /* numpad, hold V or toggle with left thumb Num. Left QWERTY keys = RGB controls. */
    [_NUMPAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, KC_PAST, KC_PSLS, KC_PMNS, _______, _______,
        RM_TOGG, RM_NEXT, RM_PREV, RM_HUEU, RM_HUED, RM_SATU,       _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
        RM_SATD, RM_VALU, RM_VALD, RM_SPDU, RM_SPDD,                KC_P4,   KC_P5,   KC_P6,   _______, _______,
        RGB_M_P, RGB_M_B, RGB_M_R, _______, RGB_M_G,                KC_P1,   KC_P2,   KC_P3,   _______, _______,
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
        _______, _______, KC_HOME,                                   KC_VOLU, KC_VOLD,_______,
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

/*
 * Breathing brightness, phase-shifted per key. Honors the global RGB
 * hue/saturation/brightness so the RGB control keycodes dim/tint these
 * layers too (plain rgb_matrix_set_color bypasses them).
 */
static RGB pulse_rgb(uint8_t hue, uint8_t phase) {
    uint8_t val = (uint8_t)(140 + 115 * sinf((float)(timer_read() + phase * 20) / 700.0f));
    val         = (uint8_t)((uint16_t)val * rgb_matrix_config.hsv.v / 255);
    return hsv_to_rgb((HSV){(uint8_t)(hue + rgb_matrix_config.hsv.h), rgb_matrix_config.hsv.s, val});
}

static void set_pulse(uint8_t i) {
    led_point_t p   = g_led_config.point[i];
    uint8_t     hue = (uint8_t)(p.x * 3 + p.y * 2 + timer_read() / 24);
    RGB         c   = pulse_rgb(hue, (uint8_t)(p.x + p.y));
    rgb_matrix_set_color(i, c.r, c.g, c.b);
}

static void set_solid(uint8_t i, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t v = rgb_matrix_config.hsv.v;
    rgb_matrix_set_color(i, (uint8_t)((uint16_t)r * v / 255), (uint8_t)((uint16_t)g * v / 255), (uint8_t)((uint16_t)b * v / 255));
}

static void set_hue_solid(uint8_t i, uint8_t hue) {
    HSV hsv = {(uint8_t)(hue + rgb_matrix_config.hsv.h), rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v};
    RGB c   = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, c.r, c.g, c.b);
}

/*
 * Per-layer RGB driven purely by LED index (no matrix/keymap lookups).
 * Indices below are the current LAYOUT's LEDs; update them if the keymap moves.
 *   NUMPAD: numbers rainbow-breathe, * red, + orange, - green, / blue, . yellow
 *   NAV:    F-keys rainbow-breathe, arrows green->red, other keys tinted
 *   ALT:    only the keys on the layer glow (rainbow breathe)
 */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    if (layer != _NUMPAD && layer != _NAV && layer != _ALT) {
        return true;
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        if (layer == _NUMPAD) {
            switch (i) {
                case 32:  // *
                    set_solid(i, RGB_RED);
                    break;
                case 37:  // +
                    set_solid(i, RGB_ORANGE);
                    break;
                case 30:  // -
                    set_solid(i, RGB_GREEN);
                    break;
                case 31:  // /
                    set_solid(i, RGB_BLUE);
                    break;
                case 46:  // .
                    set_solid(i, RGB_YELLOW);
                    break;
                case 51: case 52: case 53:  // 1 2 3
                case 43: case 42: case 41:  // 4 5 6
                case 34: case 35: case 36:  // 7 8 9
                case 45:                    // 0
                    set_pulse(i);
                    break;
                default:
                    rgb_matrix_set_color(i, RGB_BLACK);
                    break;
            }
        } else if (layer == _NAV) {
            switch (i) {
                case 0: case 1: case 2: case 3: case 4:              // F1-F5
                case 32: case 31: case 30: case 29: case 28:         // F6-F10
                case 38: case 39:                                    // F11 F12
                    set_pulse(i);
                    break;
                case 43:  // Left  - green
                    set_hue_solid(i, 85);
                    break;
                case 42:  // Down
                    set_hue_solid(i, 57);
                    break;
                case 41:  // Up
                    set_hue_solid(i, 28);
                    break;
                case 40:  // Right - red
                    set_hue_solid(i, 0);
                    break;
                case 26:  // macro 0 (X)
                    set_solid(i, RGB_CYAN);
                    break;
                case 27:  // macro 2 (Z)
                    set_solid(i, RGB_MAGENTA);
                    break;
                case 20:  // Home
                    set_solid(i, RGB_PURPLE);
                    break;
                case 48: case 49:  // Vol-
                    set_solid(i, RGB_WHITE);
                    break;
                default:
                    rgb_matrix_set_color(i, RGB_BLACK);
                    break;
            }
        } else {  // _ALT
            switch (i) {
                case 0: case 1: case 2: case 3: case 4:
                case 10:
                case 11: case 12: case 13: case 14: case 15:
                case 23: case 24: case 25: case 26: case 27:
                case 40: case 45: case 47: case 48: case 49:
                    set_pulse(i);
                    break;
                default:
                    rgb_matrix_set_color(i, RGB_BLACK);
                    break;
            }
        }
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

/*
 * VIA/Vial are gone, but their RGB config survives in EEPROM. Wipe it once
 * and set a known effect so the per-layer indicators always run. This runs
 * only on the first boot after flashing; afterwards RM_NEXT/RM_PREV etc.
 * persist normally.
 */
#define EECONFIG_EPOCH 0x776F0006

void keyboard_post_init_user(void) {
    if (eeconfig_read_user() != EECONFIG_EPOCH) {
        eeconfig_init();
        eeconfig_update_user(EECONFIG_EPOCH);
        rgb_matrix_enable_noeeprom();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
    }
}
