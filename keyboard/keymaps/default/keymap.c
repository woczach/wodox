// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <math.h>

enum layers {
    _BASE,
    _NUMPAD,
    _SYM,
    _NAV,
    _MOUSE,
    _DEV,
    _TMUX,
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

    /* DEV (nvim) layer, <leader> = space; keys sit on their mnemonic letter. Search group */
    NV_SF, NV_SG, NV_SW, NV_RR, NV_SB, NV_SRES,
    /* nvim, file / format */
    NV_EX, NV_WQ, NV_W, NV_FMT,
    /* nvim, LSP */
    NV_GRN, NV_GRD, NV_GRR, NV_GRA,
    /* vim text objects: ci( ci" ci{ vi( vi{ */
    NV_CIP, NV_CIQ, NV_CIB, NV_VIP, NV_VIB,
    /* nvim mini.surround: add around word / delete / replace */
    NV_SADD, NV_SDEL, NV_SREP,

    /* TMUX layer (prefix C-b), custom binds from .tmux.conf */
    TM_Y, TM_S, TM_D, TM_R,
    /* tmux, windows / panes */
    TM_NEW, TM_KILL, TM_VSPL, TM_HSPL, TM_ZOOM, TM_COPY, TM_NEXT, TM_PREV,
    /* tmux, pane focus */
    TM_PL, TM_PD, TM_PU, TM_PR, TM_PNXT,
    /* tmux, window list / jump / rename */
    TM_LIST, TM_W1, TM_W2, TM_W3, TM_W4, TM_W5, TM_REN,
};

#define DEV_FIRST NV_SF
#define DEV_LAST  TM_REN

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
        LT(_NAV, KC_ESC), OSL(_TMUX), OSL(_DEV),                    KC_HOME,   KC_END,  LT(_NAV, KC_QUOT),
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

    /* nvim macros, tap (one-shot, next key only) or hold left thumb, top row 3rd key. Each macro sits on its mnemonic letter. */
    [_DEV] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        NV_WQ,   NV_SW,   NV_EX,   NV_RR,   NV_FMT,  _______,       _______, NV_VIB,  NV_VIP,  NV_CIP,  NV_CIQ,  NV_CIB,
        NV_SADD, NV_SRES, NV_GRD,  NV_SF,   NV_SG,                  _______, _______, _______, _______, _______,
        NV_W,    NV_SDEL, NV_SREP, _______, NV_SB,                  NV_GRN,  NV_GRR,  NV_GRA,  _______, _______,
        _______, _______, _______,                                   _______, _______, _______,
        _______, _______, _______,                                   _______, _______, _______
    ),

    /* tmux macros (C-b prefix), tap (one-shot, next key only) or hold left thumb, top row 2nd key. Letters match the tmux key where possible */
    [_TMUX] = LAYOUT(
        TM_W1,   TM_W2,   TM_W3,   TM_W4,   TM_W5,   _______,       TM_HSPL, _______, _______, _______, _______, _______,
        _______, TM_LIST, _______, TM_R,    _______, _______,       _______, TM_Y,    _______, _______, TM_PNXT, TM_PREV,
        _______, TM_S,    TM_D,    _______, _______,                TM_PL,   TM_PD,   TM_PU,   TM_PR,   _______,
        TM_ZOOM, TM_KILL, TM_NEW,  TM_VSPL, _______,                TM_NEXT, _______, TM_REN,  _______, TM_COPY,
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
    CB_UI_LPRN,
    CB_IO_RPRN,
    CB_JK_LBRC,
    CB_KL_RBRC,
    CB_MCOMM_LCBR,
    CB_COMMDOT_RCBR,
    CB_45_PSCR,
    CB_ER_GRV,
    CB_RT_TILD,
    CB_YU_SLSH,
};

const uint16_t PROGMEM cb_ui[]      = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM cb_io[]      = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM cb_jk[]      = {LCTL_T(KC_J), KC_K, COMBO_END};
const uint16_t PROGMEM cb_kl[]      = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM cb_mcomm[]   = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM cb_commdot[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM cb_45[]      = {KC_4, KC_5, COMBO_END};
const uint16_t PROGMEM cb_er[]      = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM cb_rt[]      = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM cb_yu[]      = {KC_Y, KC_U, COMBO_END};

combo_t key_combos[] = {
    [CB_UI_LPRN]      = COMBO(cb_ui, KC_LPRN),
    [CB_IO_RPRN]      = COMBO(cb_io, KC_RPRN),
    [CB_JK_LBRC]      = COMBO(cb_jk, KC_LBRC),
    [CB_KL_RBRC]      = COMBO(cb_kl, KC_RBRC),
    [CB_MCOMM_LCBR]   = COMBO(cb_mcomm, KC_LCBR),
    [CB_COMMDOT_RCBR] = COMBO(cb_commdot, KC_RCBR),
    [CB_45_PSCR]      = COMBO(cb_45, KC_PSCR),
    [CB_ER_GRV]       = COMBO(cb_er, KC_GRV),
    [CB_RT_TILD]      = COMBO(cb_rt, KC_TILD),
    [CB_YU_SLSH]      = COMBO(cb_yu, KC_SLSH),
};

/* Breathing brightness, phase-shifted per key. */
static RGB pulse_rgb(uint8_t hue, uint8_t phase) {
    uint8_t val = (uint8_t)(140 + 115 * sinf((float)(timer_read() + phase * 20) / 700.0f));
    return hsv_to_rgb((HSV){hue, 255, val});
}

static void set_pulse(uint8_t i) {
    led_point_t p   = g_led_config.point[i];
    uint8_t     hue = (uint8_t)(p.x * 3 + p.y * 2 + timer_read() / 24);
    RGB         c   = pulse_rgb(hue, (uint8_t)(p.x + p.y));
    rgb_matrix_set_color(i, c.r, c.g, c.b);
}

/* Hue per DEV/TMUX macro group, so nvim/tmux keys are told apart at a glance. */
static uint8_t dev_hue(uint16_t kc) {
    switch (kc) {
        case NV_SF ... NV_SB: case NV_SRES: return 85;   // nvim search - green
        case NV_EX ... NV_FMT:              return 128;  // nvim file/format - cyan
        case NV_GRN ... NV_GRA:             return 43;   // nvim LSP - yellow
        case NV_CIP ... NV_VIB:             return 191;  // vim text objects - purple
        case NV_SADD ... NV_SREP:           return 213;  // surround - pink
        case TM_Y ... TM_R:                 return 21;   // tmux custom binds - orange
        case TM_NEW ... TM_PREV:            return 10;   // tmux windows/splits - red-orange
        case TM_PL ... TM_PNXT:             return 170;  // tmux pane focus - blue
        default:                            return 234;  // tmux list/jump/rename - magenta
    }
}

/* Fallback hue for layers without a hand-tuned effect. */
static uint8_t layer_hue(uint8_t layer) {
    switch (layer) {
        case _SYM:   return 43;
        case _MOUSE: return 170;
        default:     return 0;
    }
}

/*
 * Lights every key that has something assigned on `layer` (anything other than
 * KC_TRNS/KC_NO), dims the rest. Looks the keycode up by matrix position, so it
 * keeps working when the LAYOUT or LED order changes.
 */
static void light_configured_keys(uint8_t layer, uint8_t led_min, uint8_t led_max) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led;
            if (!rgb_matrix_map_row_column_to_led(row, col, &led) || led < led_min || led >= led_max) {
                continue;
            }
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){.row = row, .col = col});
            if (kc == KC_TRNS || kc == KC_NO) {
                rgb_matrix_set_color(led, RGB_OFF);
                continue;
            }
            uint8_t hue = ((layer == _DEV || layer == _TMUX) && kc >= DEV_FIRST && kc <= DEV_LAST) ? dev_hue(kc) : layer_hue(layer);
            RGB     c   = hsv_to_rgb((HSV){hue, 255, 200});
            rgb_matrix_set_color(led, c.r, c.g, c.b);
        }
    }
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
        if (layer != _BASE) {
            light_configured_keys(layer, led_min, led_max);
        }
        return true;
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        if (layer == _NUMPAD) {
            switch (i) {
                case 32:  // *
                    rgb_matrix_set_color(i, RGB_RED);
                    break;
                case 37:  // +
                    rgb_matrix_set_color(i, RGB_ORANGE);
                    break;
                case 30:  // -
                    rgb_matrix_set_color(i, RGB_GREEN);
                    break;
                case 31:  // /
                    rgb_matrix_set_color(i, RGB_BLUE);
                    break;
                case 46:  // .
                    rgb_matrix_set_color(i, RGB_YELLOW);
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
                case 43: {  // Left  - green
                    RGB c = hsv_to_rgb((HSV){85, 255, 255});
                    rgb_matrix_set_color(i, c.r, c.g, c.b);
                    break;
                }
                case 42: {  // Down
                    RGB c = hsv_to_rgb((HSV){57, 255, 255});
                    rgb_matrix_set_color(i, c.r, c.g, c.b);
                    break;
                }
                case 41: {  // Up
                    RGB c = hsv_to_rgb((HSV){28, 255, 255});
                    rgb_matrix_set_color(i, c.r, c.g, c.b);
                    break;
                }
                case 40: {  // Right - red
                    RGB c = hsv_to_rgb((HSV){0, 255, 255});
                    rgb_matrix_set_color(i, c.r, c.g, c.b);
                    break;
                }
                case 26:  // macro 0 (X)
                    rgb_matrix_set_color(i, RGB_CYAN);
                    break;
                case 27:  // macro 2 (Z)
                    rgb_matrix_set_color(i, RGB_MAGENTA);
                    break;
                case 20:  // Home
                    rgb_matrix_set_color(i, RGB_PURPLE);
                    break;
                case 48: case 49:  // Vol-
                    rgb_matrix_set_color(i, RGB_WHITE);
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

/* nvim macros leave insert/visual mode first so they work from anywhere. */
static void nv(const char *keys) {
    tap_code(KC_ESC);
    send_string(keys);
}

/* tmux prefix is C-b; small gap so tmux sees it as a separate key. */
static void tm(const char *keys) {
    tap_code16(C(KC_B));
    wait_ms(30);
    send_string(keys);
}

static void tm_key(uint8_t kc) {
    tap_code16(C(KC_B));
    wait_ms(30);
    tap_code(kc);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return !(keycode >= DEV_FIRST && keycode <= DEV_LAST) && keycode != MACRO_0 && keycode != MACRO_2;
    }
    switch (keycode) {
        case MACRO_0:    tap_code16(MEH(KC_X)); return false;
        case MACRO_2:    tap_code16(MEH(KC_Z)); return false;

        case NV_SF:      nv(" sf");      return false;  // telescope files
        case NV_SG:      nv(" sg");      return false;  // live grep
        case NV_SW:      nv(" sw");      return false;  // grep word under cursor
        case NV_RR:      nv(" rr");      return false;
        case NV_SB:      nv("  ");       return false;  // <leader><leader> buffers
        case NV_SRES:    nv(" sr");      return false;  // resume last search
        case NV_EX:      nv(":Ex\n");    return false;  // vim netrw
        case NV_WQ:      nv(":wq\n");    return false;  // vim
        case NV_W:       nv(":w\n");     return false;  // vim
        case NV_FMT:     nv(" f");       return false;  // conform format
        case NV_GRN:     nv("grn");      return false;  // LSP rename
        case NV_GRD:     nv("grd");      return false;  // LSP definition
        case NV_GRR:     nv("grr");      return false;  // LSP references
        case NV_GRA:     nv("gra");      return false;  // LSP code action
        case NV_CIP:     nv("ci(");      return false;  // vim
        case NV_CIQ:     nv("ci\"");     return false;  // vim
        case NV_CIB:     nv("ci{");      return false;  // vim
        case NV_VIP:     nv("vi(");      return false;  // vim
        case NV_VIB:     nv("vi{");      return false;  // vim
        case NV_SADD:    nv("saiw");     return false;  // mini.surround, then type the char
        case NV_SDEL:    nv("sd");       return false;
        case NV_SREP:    nv("sr");       return false;

        case TM_Y:       tm("y");        return false;  // tmux_browser.sh
        case TM_S:       tm("s");        return false;  // session switcher
        case TM_D:       tm("d");        return false;  // es.sh
        case TM_R:       tm("r");        return false;  // newfile.sh
        case TM_NEW:     tm("c");        return false;
        case TM_KILL:    tm("x");        return false;
        case TM_VSPL:    tm("%");        return false;
        case TM_HSPL:    tm("\"");       return false;
        case TM_ZOOM:    tm("z");        return false;
        case TM_COPY:    tm("[");        return false;
        case TM_NEXT:    tm("n");        return false;
        case TM_PREV:    tm("p");        return false;
        case TM_PL:      tm_key(KC_LEFT);  return false;
        case TM_PD:      tm_key(KC_DOWN);  return false;
        case TM_PU:      tm_key(KC_UP);    return false;
        case TM_PR:      tm_key(KC_RGHT);  return false;
        case TM_PNXT:    tm("o");        return false;
        case TM_LIST:    tm("w");        return false;
        case TM_W1:      tm("1");        return false;
        case TM_W2:      tm("2");        return false;
        case TM_W3:      tm("3");        return false;
        case TM_W4:      tm("4");        return false;
        case TM_W5:      tm("5");        return false;
        case TM_REN:     tm(",");        return false;
    }
    return true;
}

/*
 * VIA/Vial are gone, but their RGB config survives in EEPROM. Wipe it once
 * and force a known effect so the per-layer indicators always run.
 */
#define EECONFIG_EPOCH 0x776F0005

void keyboard_post_init_user(void) {
    if (eeconfig_read_user() != EECONFIG_EPOCH) {
        eeconfig_init();
        eeconfig_update_user(EECONFIG_EPOCH);
    }
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
}
