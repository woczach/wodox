// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │Tab│ Q │ W │ E │ R │ T │
     * ├───┼───┼───┼───┼───┼───┤
     * │Bsp│ A │ S │ D │ F │ G │
     * ├───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │
     * ├───┼───┼───┼───┼───┼───┤
     * │Ctl│App│GUI│Alt│Spc│Spc│
     * └───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x7(
        RM_TOGG,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_U,
        RM_NEXT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_J,
        RM_VALU, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_M,
        RM_VALD, KC_MENU, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC, KC_L
    )
};
