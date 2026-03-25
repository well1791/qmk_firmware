/* Copyright 2024 weteor
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
#include "keycodes.h"
#include "os_detection.h"

enum layers {
    _ALPHA = 0,
    _NUMSYM, // Numbers and Symbols
    _FUNCT, // Functional
    _NAV_L,
    _NAV_R,
    _MEDIA,
    _GO, // GO = Go-to shortcuts
    _MOUSE,
    _QWERTY,
};

/*
 * ============================================================
 * ==== Fingers => [I]ndex | [M]iddle | [R]ing   | [P]inky ====
 * ====  Rows   => [H]ome  | [T]op    | [B]ottom | [S]ide  ====
 * ============================================================
 */


// ===========================================================
// ==================     Alpha     ==========================
// ===========================================================
//                     | | | | |    | | | | |
//                     | |*|*| |    | |*|*| |
const uint16_t PROGMEM al_hm_hr[] = {AL_HM, AL_HR, COMBO_END};
//                     | | | | |    | | | | |
//                     | |*| |*|    |*| |*| |
const uint16_t PROGMEM al_hi_hr[] = {AL_HI, AL_HR, COMBO_END};
//                     | | | | |    | | | | |
//                     | | |*|*|    |*|*| | |
const uint16_t PROGMEM al_hi_hm[] = {AL_HI, AL_HM, COMBO_END};
//                     | | | | |    | | | | |
//                     |*| | |*|    |*| | |*|
const uint16_t PROGMEM al_hi_hp_l[] = {AL_HI, AL_HPL, COMBO_END};
const uint16_t PROGMEM al_hi_hp_r[] = {AL_HI, AL_HPR, COMBO_END};
// ----------------------------------------------------------
//                     | |*| | |    | | |*| |
//                     | | | |*|    |*| | | |
const uint16_t PROGMEM al_hi_tr[] = {AL_HI, AL_TR, COMBO_END};
//                     | | |*| |    | |*| | |
//                     | | | |*|    |*| | | |
const uint16_t PROGMEM al_hi_tm[] = {AL_HI, AL_TM, COMBO_END};
//                     |*| | | |    | | | |*|
//                     | | | |*|    |*| | | |
const uint16_t PROGMEM al_hi_tp[] = {AL_HI, AL_TP, COMBO_END};
//                     | |*| | |    | | |*| |
//                     | | |*| |    | |*| | |
const uint16_t PROGMEM al_hm_tr[] = {AL_HM, AL_TR, COMBO_END};
// -----------------------------------------------------------
//                     | |*|*| |    | |*|*| |
//                     | | | | |    | | | | |
const uint16_t PROGMEM al_tm_tr[] = {AL_TM, AL_TR, COMBO_END};
//                     | |*| |*|    |*| |*| |
//                     | | | | |    | | | | |
const uint16_t PROGMEM al_ti_tr[] = {AL_TI, AL_TR, COMBO_END};
//                     | | |*|*|    |*|*| | |
//                     | | | | |    | | | | |
const uint16_t PROGMEM al_ti_tm[] = {AL_TI, AL_TM, COMBO_END};
//                      |*| | |*|   |*| | |*|
//                      | | | | |   | | | | |
const uint16_t PROGMEM al_ti_tp[] = {AL_TI, AL_TP, COMBO_END};
// -----------------------------------------------------------
//                     | | |*| |    | |*| | |
//                     | |*| | |    | | |*| |
const uint16_t PROGMEM al_tm_hr[] = {AL_TM, AL_HR, COMBO_END};
//                     | | | |*|    |*| | | |
//                     | |*| | |    | | |*| |
const uint16_t PROGMEM al_ti_hr[] = {AL_TI, AL_HR, COMBO_END};
//                     | | | |*|    |*| | | |
//                     | | |*| |    | |*| | |
const uint16_t PROGMEM al_ti_hm[] = {AL_TI, AL_HM, COMBO_END};
//                     | | | |*|    |*| | | |
//                     |*| | | |    | | | |*|
const uint16_t PROGMEM al_ti_hp_l[] = {AL_TI, AL_HPL, COMBO_END};
const uint16_t PROGMEM al_ti_hp_r[] = {AL_TI, AL_HPR, COMBO_END};
// -----------------------------------------------------------
//                     | | | | |       | | | | |
//                     | |*|*|*|       |*|*|*| |
const uint16_t PROGMEM al_hi_hm_hr[] = {AL_HI, AL_HM, AL_HR, COMBO_END};
//                     | |*|*|*|       |*|*|*| |
//                     | | | | |       | | | | |
const uint16_t PROGMEM al_ti_tm_tr[] = {AL_TI, AL_TM, AL_TR, COMBO_END};
//                     | | |*| |       | |*| | |
//                     | |*| |*|       |*| |*| |
const uint16_t PROGMEM al_hi_tm_hr[] = {AL_HI, AL_TM, AL_HR, COMBO_END};
//                     | |*|*| |       | |*|*| |
//                     | | | |*|       |*| | | |
const uint16_t PROGMEM al_hi_tm_tr[] = {AL_HI, AL_TM, AL_TR, COMBO_END};
//                     | |*| | |       | | |*| |
//                     | | |*|*|       |*|*| | |
const uint16_t PROGMEM al_hi_hm_tr[] = {AL_HI, AL_HM, AL_TR, COMBO_END};
//                     | | |*|*|       |*|*| | |
//                     | |*| | |       | | |*| |
const uint16_t PROGMEM al_ti_tm_hr[] = {AL_TI, AL_TM, AL_HR, COMBO_END};
//                     | | | |*|       |*| | | |
//                     | |*|*| |       | |*|*| |
const uint16_t PROGMEM al_ti_hm_hr[] = {AL_TI, AL_HM, AL_HR, COMBO_END};
// -----------------------------------------------------------
//                     | | | | |          | | | | |
//                     |*|*|*|*|          |*|*|*|*|
const uint16_t PROGMEM al_hi_hr_hm_hp_l[] = {AL_HI, AL_HR, AL_HM, AL_HPL, COMBO_END};
const uint16_t PROGMEM al_hi_hr_hm_hp_r[] = {AL_HI, AL_HR, AL_HM, AL_HPR, COMBO_END};
//                     |*|*|*|*|          |*|*|*|*|
//                     | | | | |          | | | | |
const uint16_t PROGMEM al_ti_tr_tm_tp[] = {AL_TI, AL_TR, AL_TM, AL_TP, COMBO_END};
// -----------------------------------------------------------
//                     | | | | |       | | | | |
//                     | | |*| |       | |*| | |
//                         | |*|       |*| |
const uint16_t PROGMEM al_bi_hm[] = {AL_BI, AL_HM, COMBO_END};
//                     | | | | |       | | | | |
//                     | |*| | |       | | |*| |
//                         |*| |       | |*|
const uint16_t PROGMEM al_bm_hr[] = {AL_BM, AL_HR, COMBO_END};
//                     | | | | |       | | | | |
//                     | |*| | |       | | |*| |
//                         | |*|       |*| |
const uint16_t PROGMEM al_bi_hr[] = {AL_BI, AL_HR, COMBO_END};
//                     | | | | |       | | | | |
//                     | | | | |       | | | | |
//                         |*|*|       |*|*|
const uint16_t PROGMEM al_bi_bm[] = {AL_BI, AL_BM, COMBO_END};
//                     | | | | |       | | | | |
//                     |*| | | |       | | | |*|
//                         | |*|       |*| |
const uint16_t PROGMEM al_bi_hp_l[] = {AL_BI, AL_HPL, COMBO_END};
const uint16_t PROGMEM al_bi_hp_r[] = {AL_BI, AL_HPR, COMBO_END};
//                     | | | | |       | | | | |
//                     | |*| | |       | | |*| |
//                         |*|*|       |*|*|
const uint16_t PROGMEM al_bi_bm_hr[] = {AL_BI, AL_BM, AL_HR, COMBO_END};

// ===========================================================
// ==================  Nums n Syms  ==========================
// ===========================================================
//                     | | | | |    | | | | |
//                     | |*|*| |    | |*|*| |
const uint16_t PROGMEM ns_hm_hr[] = {NS_HM, NS_HR, COMBO_END};
//                     | | | | |    | | | | |
//                     | |*| |*|    |*| |*| |
const uint16_t PROGMEM ns_hi_hr[] = {NS_HI, NS_HR, COMBO_END};
//                     | | | | |    | | | | |
//                     | | |*|*|    |*|*| | |
const uint16_t PROGMEM ns_hi_hm[] = {NS_HI, NS_HM, COMBO_END};
//                     | | | | |    | | | | |
//                     |*| | |*|    |*| | |*|
const uint16_t PROGMEM ns_hi_hp[] = {NS_HI, NS_HP, COMBO_END};
// ----------------------------------------------------------
//                     | |*| | |    | | |*| |
//                     | | | |*|    |*| | | |
const uint16_t PROGMEM ns_hi_tr[] = {NS_HI, NS_TR, COMBO_END};
//                     | | |*| |    | |*| | |
//                     | | | |*|    |*| | | |
const uint16_t PROGMEM ns_hi_tm[] = {NS_HI, NS_TM, COMBO_END};
//                     |*| | | |    | | | |*|
//                     | | | |*|    |*| | | |
const uint16_t PROGMEM ns_hi_tp[] = {NS_HI, NS_TP, COMBO_END};
//                     | |*| | |    | | |*| |
//                     | | |*| |    | |*| | |
const uint16_t PROGMEM ns_hm_tr[] = {NS_HM, NS_TR, COMBO_END};
// -----------------------------------------------------------
//                     | |*|*| |    | |*|*| |
//                     | | | | |    | | | | |
const uint16_t PROGMEM ns_tm_tr[] = {NS_TM, NS_TR, COMBO_END};
//                     | |*| |*|    |*| |*| |
//                     | | | | |    | | | | |
const uint16_t PROGMEM ns_ti_tr[] = {NS_TI, NS_TR, COMBO_END};
//                     | | |*|*|    |*|*| | |
//                     | | | | |    | | | | |
const uint16_t PROGMEM ns_ti_tm[] = {NS_TI, NS_TM, COMBO_END};
//                      |*| | |*|   |*| | |*|
//                      | | | | |   | | | | |
const uint16_t PROGMEM ns_ti_tp[] = {NS_TI, NS_TP, COMBO_END};
// -----------------------------------------------------------
//                     | | |*| |    | |*| | |
//                     | |*| | |    | | |*| |
const uint16_t PROGMEM ns_tm_hr[] = {NS_TM, NS_HR, COMBO_END};
//                     | | | |*|    |*| | | |
//                     | |*| | |    | | |*| |
const uint16_t PROGMEM ns_ti_hr[] = {NS_TI, NS_HR, COMBO_END};
//                     | | | |*|    |*| | | |
//                     | | |*| |    | |*| | |
const uint16_t PROGMEM ns_ti_hm[] = {NS_TI, NS_HM, COMBO_END};
//                     | | | |*|    |*| | | |
//                     |*| | | |    | | | |*|
const uint16_t PROGMEM ns_ti_hp[] = {NS_TI, NS_HP, COMBO_END};
// -----------------------------------------------------------
//                     | | | | |    | | | | |
//                     |*|*| | |    | | |*|*|
const uint16_t PROGMEM ns_hr_hp[] = {NS_HR, NS_HP, COMBO_END};
//                     |*|*| | |    | | |*|*|
//                     | | | | |    | | | | |
const uint16_t PROGMEM ns_tr_tp[] = {NS_TR, NS_TP, COMBO_END};
// -----------------------------------------------------------
//                     | | | | |       | | | | |
//                     | |*|*|*|       |*|*|*| |
const uint16_t PROGMEM ns_hi_hm_hr[] = {NS_HI, NS_HM, NS_HR, COMBO_END};
//                     | |*|*|*|       |*|*|*| |
//                     | | | | |       | | | | |
const uint16_t PROGMEM ns_ti_tm_tr[] = {NS_TI, NS_TM, NS_TR, COMBO_END};
//                     | | |*| |       | |*| | |
//                     | |*| |*|       |*| |*| |
const uint16_t PROGMEM ns_hi_tm_hr[] = {NS_HI, NS_TM, NS_HR, COMBO_END};
//                     | |*|*| |       | |*|*| |
//                     | | | |*|       |*| | | |
const uint16_t PROGMEM ns_hi_tm_tr[] = {NS_HI, NS_TM, NS_TR, COMBO_END};
//                     | |*| | |       | | |*| |
//                     | | |*|*|       |*|*| | |
const uint16_t PROGMEM ns_hi_hm_tr[] = {NS_HI, NS_HM, NS_TR, COMBO_END};
//                     | | |*|*|       |*|*| | |
//                     | |*| | |       | | |*| |
const uint16_t PROGMEM ns_ti_tm_hr[] = {NS_TI, NS_TM, NS_HR, COMBO_END};
//                     | | | |*|       |*| | | |
//                     | |*|*| |       | |*|*| |
const uint16_t PROGMEM ns_ti_hm_hr[] = {NS_TI, NS_HM, NS_HR, COMBO_END};
//                     | | | | |       | | | | |
//                     |*|*|*| |       | |*|*|*|
const uint16_t PROGMEM ns_hm_hr_hp[] = {NS_HM, NS_HR, NS_HP, COMBO_END};
//                     |*|*|*| |       | |*|*|*|
//                     | | | | |       | | | | |
const uint16_t PROGMEM ns_tm_tr_tp[] = {NS_TM, NS_TR, NS_TP, COMBO_END};
// -----------------------------------------------------------
//                     | | | | |       | | | | |
//                     | | |*| |       | |*| | |
//                         | |*|       |*| |
const uint16_t PROGMEM ns_bi_hm[] = {NS_BI, NS_HM, COMBO_END};
//                     | | | | |       | | | | |
//                     | |*| | |       | | |*| |
//                         |*| |       | |*|
const uint16_t PROGMEM ns_bm_hr[] = {NS_BM, NS_HR, COMBO_END};
//                     | | | | |       | | | | |
//                     | |*| | |       | | |*| |
//                         | |*|       |*| |
const uint16_t PROGMEM ns_bi_hr[] = {NS_BI, NS_HR, COMBO_END};
//                     | | | | |       | | | | |
//                     |*| | | |       | | | |*|
//                         | |*|       |*| |
const uint16_t PROGMEM ns_bi_hp[] = {NS_BI, NS_HP, COMBO_END};
//                     | | | | |       | | | | |
//                     | | | | |       | | | | |
//                         |*|*|       |*|*|
const uint16_t PROGMEM ns_bi_bm[] = {NS_BI, NS_BM, COMBO_END};
//                     | | | | |       | | | | |
//                     | |*| | |       | | |*| |
//                         |*|*|       |*|*|
const uint16_t PROGMEM ns_bi_bm_hr[] = {NS_BI, NS_BM, NS_HR, COMBO_END};

// ===========================================================
// ==================  Functional   ==========================
// ===========================================================
//           | | | | |           | | | | |
//           | | |*|*|           |*|*| | |
const uint16_t PROGMEM ff_f2[] = {KC_F1, KC_F3, COMBO_END};
//           | | | | |           | | | | |
//           | |*|*| |           | |*|*| |
const uint16_t PROGMEM ff_f4[] = {KC_F3, KC_F5, COMBO_END};
//           | | |*|*|           |*|*| | |
//           | | | | |           | | | | |
const uint16_t PROGMEM ff_f7[] = {KC_F6, KC_F8, COMBO_END};
//           | |*|*| |           | |*|*| |
//           | | | | |           | | | | |
const uint16_t PROGMEM ff_f9[] = {KC_F8, KC_F10, COMBO_END};

// ===========================================================
// ==================  Navigation   ==========================
// ===========================================================
//           | | | | |             | | | | |
//           | |*| |*|             |*| |*| |
const uint16_t PROGMEM na_hi_hr[]  = {NA_MV_LT, NA_MV_RT, COMBO_END};
//           | |*| |*|             |*| |*| |
//           | | | | |             | | | | |
const uint16_t PROGMEM na_ti_tr[] = {NA_MV_TI, NA_MV_TR, COMBO_END};
//           | |*|*| |             | |*|*| |
//           | | | | |             | | | | |
const uint16_t PROGMEM na_tm_tr[]  = {NA_MV_TM, NA_MV_TR, COMBO_END};
//           | | | | |             | | | | |
//           | |*|*|*|             |*|*|*| |
const uint16_t PROGMEM na_hi_hm_hr[]  = {NA_MV_LT, NA_MV_HM,  NA_MV_RT, COMBO_END};
//           | |*|*|*|             |*|*|*| |
//           | | | | |             | | | | |
const uint16_t PROGMEM na_ti_tm_tr[]  = {NA_MV_TI, NA_MV_TM, NA_MV_TR, COMBO_END};


combo_t key_combos[] = {
    // ===========================================================
    // ==================     Alpha     ==========================
    // ===========================================================
    COMBO(al_hm_hr, KC_N),
    COMBO(al_hi_hr, KC_S),
    COMBO(al_hi_hm, KC_R),
    COMBO(al_hi_tr, KC_T),
    COMBO(al_tm_tr, KC_D),
    COMBO(al_ti_tr, KC_L),
    COMBO(al_ti_tm, KC_C),
    COMBO(al_hi_hp_l, KC_P),
    COMBO(al_hi_hp_r, KC_P),
    COMBO(al_hi_tp, KC_Y),
    COMBO(al_ti_tp, KC_B),
    COMBO(al_tm_hr, KC_F),
    COMBO(al_hm_tr, KC_V),
    COMBO(al_hi_tm, KC_W),
    COMBO(al_ti_hr, KC_Q),
    COMBO(al_ti_hm, KC_X),
    // -----------------------------------------------
    COMBO(al_hi_hm_hr, KC_SPACE),
    COMBO(al_ti_tm_tr, KC_ESCAPE),
    COMBO(al_hi_tm_hr, OSL(_NUMSYM)),
    COMBO(al_ti_hm_hr, OSL(_FUNCT)),
    COMBO(al_hi_tm_tr, OSL(_GO)),
    COMBO(al_hi_hm_tr, OSL(_MEDIA)),
    // COMBO(???, OSL(_MOUSE)),
    COMBO(al_bi_bm, OSM(MOD_LSFT)),
    COMBO(al_bi_hr, OSM(MOD_LCTL)),
    COMBO(al_bi_hm, OSM(MOD_LALT)),
    COMBO(al_bi_hp_l, OSM(MOD_LGUI)),
    COMBO(al_bi_hp_r, OSM(MOD_LGUI)),

    // ===========================================================
    // ==================  Nums N Syms  ==========================
    // ===========================================================
    COMBO(ns_hi_hm, KC_2),
    COMBO(ns_hm_hr, KC_4),
    COMBO(ns_ti_tm, KC_7),
    COMBO(ns_tm_tr, KC_9),
    COMBO(ns_hi_hr, KC_LPRN), // (
    COMBO(ns_ti_tr, KC_RPRN), // )
    COMBO(ns_hi_hp, KC_LBRC), // [
    COMBO(ns_ti_tp, KC_RBRC), // ]
    COMBO(ns_bi_hm, KC_LCBR), // {
    COMBO(ns_bm_hr, KC_RCBR), // }
    COMBO(ns_bi_hr, KC_LABK), // <
    COMBO(ns_bi_hp, KC_RABK), // >
    COMBO(ns_hi_tp, KC_MINUS),
    COMBO(ns_ti_hp, KC_UNDERSCORE),
    COMBO(ns_hi_tr, KC_SLASH),
    COMBO(ns_ti_hr, KC_BACKSLASH),
    COMBO(ns_hi_tm, KC_COMMA),
    COMBO(ns_tm_hr, KC_DOT),
    COMBO(ns_hr_hp, KC_DQT),
    COMBO(ns_tr_tp, KC_PERCENT),
    COMBO(ns_hi_hm_hr, KC_QUESTION),
    COMBO(ns_ti_tm_tr, KC_EXCLAIM),
    COMBO(ns_hi_tm_hr, KC_SEMICOLON),
    COMBO(ns_hi_tm_tr, KC_COLON),
    COMBO(ns_hi_hm_tr, KC_AMPERSAND),
    COMBO(ns_ti_tm_hr, KC_PIPE),
    COMBO(ns_hm_hr_hp, KC_GRAVE),
    COMBO(ns_tm_tr_tp, KC_TILDE),
    COMBO(ns_bi_bm, KC_EQUAL),
    COMBO(ns_bi_bm_hr, KC_DOLLAR),

    // ===========================================================
    // ==================  Functional   ==========================
    // ===========================================================
    COMBO(ff_f2, KC_F2),
    COMBO(ff_f4, KC_F4),
    COMBO(ff_f7, KC_F7),
    COMBO(ff_f9, KC_F9),

    // ===========================================================
    // ==================  Navigation   ==========================
    // ===========================================================
    COMBO(na_hi_hr, KC_END),
    COMBO(na_ti_tr, KC_HOME),
    COMBO(na_tm_tr, KC_DELETE),
    COMBO(na_ti_tm_tr, KC_ESCAPE),
    COMBO(na_hi_hm_hr, KC_SPACE),
};

enum custom_keycodes {
    CTL_TAB = SAFE_RANGE,
    CTL_SFT_T,
    ALT_1,
    ALT_9,
    CTL_W,
    CTL_PGUP,
    CTL_PGDN,
    ALT_GRV,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_TAB: // CTL+TAB
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_TAB);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;

        case CTL_SFT_T: // CTL+SFT+T
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_T);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
            }
            return false;

        case ALT_1: // ALT+1
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_1);
            } else {
                unregister_code(KC_LALT);
            }
            return false;

        case ALT_9: // ALT+9
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_9);
            } else {
                unregister_code(KC_LALT);
            }
            return false;

        case CTL_W: // CTL+W
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_W);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;

        case CTL_PGUP: // CTL+PGUP
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_PGUP);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;

        case CTL_PGDN: // CTL+PGDN
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_PGDN);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;

        case ALT_GRV: // same app
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_GRAVE);
            } else {
                unregister_code(KC_LALT);
            }
            return false;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALPHA] = LAYOUT_split_3x5_3(
              AL_TP,   AL_TR,   AL_TM,   AL_TI, _______, /*||*/ _______,   AL_TI,   AL_TM,   AL_TR,   AL_TP,
             AL_HPL,   AL_HR,   AL_HM,   AL_HI,   AL_SI, /*||*/   AL_SI,   AL_HI,   AL_HM,   AL_HR,  AL_HPR,
            _______, _______,   AL_BM,   AL_BI, _______, /*||*/ _______,   AL_BI,   AL_BM, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    [_NUMSYM] = LAYOUT_split_3x5_3(
              NS_TP,   NS_TR,   NS_TM,   NS_TI, _______, /*||*/ _______,   NS_TI,   NS_TM,   NS_TR,   NS_TP,
              NS_HP,   NS_HR,   NS_HM,   NS_HI,   NS_SI, /*||*/   NS_SI,   NS_HI,   NS_HM,   NS_HR,   NS_HP,
            _______, _______,   NS_BM,   NS_BI, _______, /*||*/ _______,   NS_BI,   NS_BM, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    [_FUNCT] = LAYOUT_split_3x5_3(
             KC_F11,  KC_F10,   KC_F8,   KC_F6, _______, /*||*/ _______,   KC_F6,   KC_F8,  KC_F10,  KC_F11,
             KC_F12,   KC_F5,   KC_F3,   KC_F1, _______, /*||*/ _______,   KC_F1,   KC_F3,   KC_F5,  KC_F12,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    [_NAV_L] = LAYOUT_split_3x5_3(
        NA_MV_TP, NA_MV_TR, NA_MV_TM, NA_MV_TI, _______, /*||*/ _______, NA_MD_TI, NA_MD_TM, NA_MD_TR, TO(_NAV_R),
        NA_MV_HP, NA_MV_LT, NA_MV_HM, NA_MV_RT, _______, /*||*/ _______, NA_MD_HI, NA_MD_HM, NA_MD_HR,   NA_MD_HP,
         _______,  _______,  _______,  _______, _______, /*||*/ _______,  _______,  _______,  _______,    _______,
                             _______,  _______, _______, /*||*/ _______,  _______,  _______
    ),

    [_NAV_R] = LAYOUT_split_3x5_3(
      TO(_NAV_L), NA_MD_TR, NA_MD_TM, NA_MD_TI, _______, /*||*/ _______, NA_MV_TI, NA_MV_TM, NA_MV_TR, NA_MV_TP,
        NA_MD_HP, NA_MD_HR, NA_MD_HM, NA_MD_HI, _______, /*||*/ _______, NA_MV_LT, NA_MV_HM, NA_MV_RT, NA_MV_HP,
         _______,  _______,   _______, _______, _______, /*||*/ _______,  _______,  _______,  _______,  _______,
                              _______, _______, _______, /*||*/ _______,  _______,  _______
    ),

    [_MEDIA] = LAYOUT_split_3x5_3(
            KC_BRIU, KC_MPRV, KC_VOLU, KC_MUTE, _______, /*||*/ _______, KC_MUTE, KC_VOLU, KC_MPRV, KC_BRIU,
            KC_BRID, KC_MNXT, KC_VOLD, KC_MPLY, _______, /*||*/ _______, KC_MPLY, KC_VOLD, KC_MNXT, KC_BRID,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    // TODO: finish layout
    [_GO] = LAYOUT_split_3x5_3(
           ALT_9, ALT_GRV, CTL_PGUP, CTL_SFT_T, _______, /*||*/ _______, CTL_SFT_T, CTL_PGUP, ALT_GRV,   ALT_9,
           ALT_1, CTL_TAB, CTL_PGDN,     CTL_W, _______, /*||*/ _______,     CTL_W, CTL_PGDN, CTL_TAB,   ALT_1,
         _______, _______,  _______,   _______, _______, /*||*/ _______,   _______,  _______, _______, _______,
                            _______,   _______, _______, /*||*/ _______,   _______,  _______
    ),

    // TODO: finish layout
    [_MOUSE] = LAYOUT_split_3x5_3(
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    // TODO: finish layout and allow just one combo to go back to the main alpha layer
    [_QWERTY] = LAYOUT_split_3x5_3(
                        KC_Q, KC_W, KC_E, KC_R,    KC_T, /*||*/    KC_Y, KC_U,     KC_I,   KC_O,         KC_P,
                        KC_A, KC_S, KC_D, KC_F,    KC_G, /*||*/    KC_H, KC_J,     KC_K,   KC_L, KC_SEMICOLON,
                        KC_Z, KC_X, KC_C, KC_V,    KC_B, /*||*/    KC_N, KC_M, KC_COMMA, KC_DOT,     KC_SLASH,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),
};
