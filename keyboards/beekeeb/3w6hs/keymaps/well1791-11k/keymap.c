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
    _AL = 0,
    _NS,
    _FF,
    _NL,
    _NR,
    _ME,
    _GO,
    _MO,
    _AL_QWERTY,
};

// ===========================================================
//           | | | | |             | | | | |
//           | |*|*|*|             |*|*|*| |
const uint16_t PROGMEM na_spc[]  = {KC_LEFT, KC_DOWN, KC_RIGHT, COMBO_END};
//           | |*|*|*|             |*|*|*| |
//           | | | | |             | | | | |
const uint16_t PROGMEM na_esc[]  = {KC_TAB, KC_UP, KC_BSPC, COMBO_END};
//           | |*|*| |             | |*|*| |
//           | | | | |             | | | | |
const uint16_t PROGMEM na_del[]  = {KC_UP, KC_BSPC, COMBO_END};
//           | |*| |*|             |*| |*| |
//           | | | | |             | | | | |
const uint16_t PROGMEM na_home[] = {KC_TAB, KC_BSPC, COMBO_END};
//           | | | | |             | | | | |
//           | |*| |*|             |*| |*| |
const uint16_t PROGMEM na_end[]  = {KC_LEFT, KC_RIGHT, COMBO_END};

// ===========================================================
//           | | | | |                   | | | | |
//           | | |*|*|                   |*|*| | |
const uint16_t PROGMEM ns_2[]          = {KC_1, KC_3, COMBO_END};
//           | | | | |                   | | | | |
//           | |*|*| |                   | |*|*| |
const uint16_t PROGMEM ns_4[]          = {KC_3, KC_5, COMBO_END};
//           | | |*|*|                   |*|*| | |
//           | | | | |                   | | | | |
const uint16_t PROGMEM ns_7[]          = {KC_6, KC_8, COMBO_END};
//           | |*|*| |                   | |*|*| |
//           | | | | |                   | | | | |
const uint16_t PROGMEM ns_9[]          = {KC_8, KC_0, COMBO_END};
// const uint16_t PROGMEM ns_angbr_l[]    = {KC_7, KC_8, COMBO_END};
// const uint16_t PROGMEM ns_angbr_r[]    = {KC_1, KC_2, COMBO_END};
// const uint16_t PROGMEM ns_sqrbr_l[]    = {KC_8, KC_9, COMBO_END};
// const uint16_t PROGMEM ns_sqrbr_r[]    = {KC_2, KC_3, COMBO_END};
// const uint16_t PROGMEM ns_curbr_l[]    = {KC_7, KC_9, COMBO_END};
// const uint16_t PROGMEM ns_curbr_r[]    = {KC_1, KC_3, COMBO_END};
// const uint16_t PROGMEM ns_paren_l[]    = {KC_7, KC_0, COMBO_END};
// const uint16_t PROGMEM ns_paren_r[]    = {KC_1, KC_QUOTE, COMBO_END};
// const uint16_t PROGMEM ns_dot[]        = {KC_8, KC_3, COMBO_END};
// const uint16_t PROGMEM ns_semicolon[]  = {KC_9, KC_2, COMBO_END};
// const uint16_t PROGMEM ns_slash[]      = {KC_1, KC_9, COMBO_END};
// const uint16_t PROGMEM ns_bslash[]     = {KC_7, KC_3, COMBO_END};
// const uint16_t PROGMEM ns_hyphen[]     = {KC_1, KC_0, COMBO_END};
// const uint16_t PROGMEM ns_underscore[] = {KC_7, KC_QUOTE, COMBO_END};
// const uint16_t PROGMEM ns_comma[]      = {KC_1, KC_8, COMBO_END};
// const uint16_t PROGMEM ns_equals[]     = {KC_9, KC_0, COMBO_END};
// const uint16_t PROGMEM ns_dblquots[]   = {KC_3, KC_QUOTE, COMBO_END};
// const uint16_t PROGMEM ns_qstn_mrk[]   = {KC_1, KC_2, KC_3, COMBO_END};
// const uint16_t PROGMEM ns_excl_mrk[]   = {KC_7, KC_8, KC_9, COMBO_END};
// const uint16_t PROGMEM ns_colon[]      = {KC_1, KC_8, KC_3, COMBO_END};
// const uint16_t PROGMEM ns_asterisk[]   = {KC_1, KC_8, KC_9, COMBO_END};
// const uint16_t PROGMEM ns_ampersand[]  = {KC_1, KC_2, KC_9, COMBO_END};
// const uint16_t PROGMEM ns_pipe[]       = {KC_7, KC_8, KC_3, COMBO_END};
// const uint16_t PROGMEM ns_backticks[]  = {KC_2, KC_3, KC_QUOTE, COMBO_END};
// const uint16_t PROGMEM ns_tilde[]      = {KC_8, KC_9, KC_0, COMBO_END};
// const uint16_t PROGMEM ns_dollar[]     = {KC_1, KC_2, KC_3, KC_QUOTE, COMBO_END};
// const uint16_t PROGMEM ns_percentage[] = {KC_7, KC_8, KC_9, KC_0, COMBO_END};
// const uint16_t PROGMEM ns_plus[]       = {KC_7, KC_2, KC_3, COMBO_END};
// const uint16_t PROGMEM ns_hash[]       = {KC_8, KC_3, KC_QUOTE, COMBO_END};
// const uint16_t PROGMEM ns_at[]         = {KC_9, KC_QUOTE, COMBO_END};
// const uint16_t PROGMEM ns_circ[]       = {KC_7, KC_2, COMBO_END};

// ===========================================================
// Finger - [P]inky  | [R]ing | [M]iddle | [I]ndex
//  Row   - [B]ottom | [T]op
// ===========================================================
//          | | | | |     hm_hr     | | | | |
//          | |*|*| |     hm_hr     | |*|*| |
const uint16_t PROGMEM al_hm_hr[] = {AL_HM, AL_HR, COMBO_END};
//          | | | | |     hi_hr     | | | | |
//          | |*| |*|     hi_hr     |*| |*| |
const uint16_t PROGMEM al_hi_hr[] = {AL_HI, AL_HR, COMBO_END};
//          | | | | |     hi_hm     | | | | |
//          | | |*|*|     hi_hm     |*|*| | |
const uint16_t PROGMEM al_hi_hm[] = {AL_HI, AL_HM, COMBO_END};
//          | | | | |     hi_hp     | | | | |
//          |*| | |*|     hi_hp     |*| | |*|
const uint16_t PROGMEM al_hi_hp_l[] = {AL_HI, AL_HPL, COMBO_END};
const uint16_t PROGMEM al_hi_hp_r[] = {AL_HI, AL_HPR, COMBO_END};

// ===========================================================
//          | |*| | |     hi_tr     | | |*| |
//          | | | |*|     hi_tr     |*| | | |
const uint16_t PROGMEM al_hi_tr[] = {AL_HI, AL_TR, COMBO_END};
//          | |*| | |     hm_tr     | | |*| |
//          | | |*| |     hm_tr     | |*| | |
const uint16_t PROGMEM al_hm_tr[] = {AL_HM, AL_TR, COMBO_END};
//          | | |*| |     hi_tm     | |*| | |
//          | | | |*|     hi_tm     |*| | | |
const uint16_t PROGMEM al_hi_tm[] = {AL_HI, AL_TM, COMBO_END};
//          |*| | | |     hi_tp     | | | |*|
//          | | | |*|     hi_tp     |*| | | |
const uint16_t PROGMEM al_hi_tp[] = {AL_HI, AL_TP, COMBO_END};
// ===========================================================
//          | |*|*| |     tm_tr     | |*|*| |
//          | | | | |     tm_tr     | | | | |
const uint16_t PROGMEM al_tm_tr[] = {AL_TM, AL_TR, COMBO_END};
//          | |*| |*|     ti_tr     |*| |*| |
//          | | | | |     ti_tr     | | | | |
const uint16_t PROGMEM al_ti_tr[] = {AL_TI, AL_TR, COMBO_END};
//          | | |*|*|     ti_tm     |*|*| | |
//          | | | | |     ti_tm     | | | | |
const uint16_t PROGMEM al_ti_tm[] = {AL_TI, AL_TM, COMBO_END};
//          |*| | |*|     ti_tp     |*| | |*|
//          | | | | |     ti_tp     | | | | |
const uint16_t PROGMEM al_ti_tp[] = {AL_TI, AL_TP, COMBO_END};
// ===========================================================
//          | | |*| |     tm_hr     | |*| | |
//          | |*| | |     tm_hr     | | |*| |
const uint16_t PROGMEM al_tm_hr[] = {AL_TM, AL_HR, COMBO_END};
//          | | | |*|     ti_hr     |*| | | |
//          | |*| | |     ti_hr     | | |*| |
const uint16_t PROGMEM al_ti_hr[] = {AL_TI, AL_HR, COMBO_END};
//          | | | |*|     ti_hm     |*| | | |
//          | | |*| |     ti_hm     | |*| | |
const uint16_t PROGMEM al_ti_hm[] = {AL_TI, AL_HM, COMBO_END};
//          | | | |*|     ti_hp     |*| | | |
//          |*| | | |     ti_hp     | | | |*|
const uint16_t PROGMEM al_ti_hp_l[] = {AL_TI, AL_HPL, COMBO_END};
const uint16_t PROGMEM al_ti_hp_r[] = {AL_TI, AL_HPR, COMBO_END};
// ===========================================================
//          | | | | |     hr_hp       | | | | |
//          |*|*| | |     hr_hp       | | |*|*|
const uint16_t PROGMEM al_hr_hp_l[] = {AL_HPL, AL_HR, COMBO_END};
const uint16_t PROGMEM al_hr_hp_r[] = {AL_HPL, AL_HR, COMBO_END};
//          |*|*| | |     tr_tp       | | |*|*|
//          | | | | |     tr_tp       | | | | |
const uint16_t PROGMEM al_tr_tp[]   = {AL_TP, AL_TR, COMBO_END};
//          | |*| | |     tr_hp       | | |*| |
//          |*| | | |     tr_hp       | | | |*|
const uint16_t PROGMEM al_tr_hp_l[] = {AL_HPL, AL_TR, COMBO_END};
const uint16_t PROGMEM al_tr_hp_r[] = {AL_HPL, AL_TR, COMBO_END};
// ===========================================================
//          | | | | |     hi_hm_hr     | | | | |
//          | |*|*|*|     hi_hm_hr     |*|*|*| |
const uint16_t PROGMEM al_hi_hm_hr[] = {AL_HI, AL_HM, AL_HR, COMBO_END};
//          | |*|*|*|     ti_tm_tr     |*|*|*| |
//          | | | | |     ti_tm_tr     | | | | |
const uint16_t PROGMEM al_ti_tm_tr[] = {AL_TI, AL_TM, AL_TR, COMBO_END};
//          | | |*| |     hi_tm_hr     | |*| | |
//          | |*| |*|     hi_tm_hr     |*| |*| |
const uint16_t PROGMEM al_hi_tm_hr[] = {AL_HI, AL_TM, AL_HR, COMBO_END};
//          | |*|*| |     hi_tm_tr     | |*|*| |
//          | | | |*|     hi_tm_tr     |*| | | |
const uint16_t PROGMEM al_hi_tm_tr[] = {AL_HI, AL_TM, AL_TR, COMBO_END};
//          | |*| | |     hi_hm_tr     | | |*| |
//          | | |*|*|     hi_hm_tr     |*|*| | |
const uint16_t PROGMEM al_hi_hm_tr[] = {AL_HI, AL_HM, AL_TR, COMBO_END};
//          | | |*|*|     ti_tm_hr     |*|*| | |
//          | |*| | |     ti_tm_hr     | | |*| |
const uint16_t PROGMEM al_ti_tm_hr[] = {AL_TI, AL_TM, AL_HR, COMBO_END};
//          | | | |*|     ti_hm_br     |*| | | |
//          | |*|*| |     ti_hm_br     | |*|*| |
const uint16_t PROGMEM al_ti_hm_br[] = {AL_TI, AL_HM, AL_HR, COMBO_END};
// ===========================================================
//          | | | | |     hi_hr_hm_hp     | | | | |
//          |*|*|*|*|     hi_hr_hm_hp     |*|*|*|*|
const uint16_t PROGMEM al_hi_hr_hm_hp_l[] = {AL_HI, AL_HR, AL_HM, AL_HPL, COMBO_END};
const uint16_t PROGMEM al_hi_hr_hm_hp_r[] = {AL_HI, AL_HR, AL_HM, AL_HPR, COMBO_END};
//          |*|*|*|*|     ti_tr_tm_tp     |*|*|*|*|
//          | | | | |     ti_tr_tm_tp     | | | | |
const uint16_t PROGMEM al_ti_tr_tm_tp[] = {AL_TI, AL_TR, AL_TM, AL_TP, COMBO_END};
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
const uint16_t PROGMEM ff_f9[] = {KC_F8, KC_F19, COMBO_END};


combo_t key_combos[] = {
    // Letter Chords -- right hand
    // ===============================================
    COMBO(al_hm_hr, KC_T),
    COMBO(al_hi_hr, KC_L),
    COMBO(al_hi_hm, KC_D),
    COMBO(al_hi_tr, KC_C),
    COMBO(al_tm_tr, KC_U),
    COMBO(al_ti_tr, KC_V),
    COMBO(al_ti_tm, KC_Y),
    COMBO(al_hi_hp_l, KC_G),
    COMBO(al_hi_hp_r, KC_G),
    COMBO(al_hi_tp, KC_B),
    COMBO(al_ti_tp, KC_W),
    COMBO(al_tm_hr, KC_F),
    COMBO(al_hi_tm, KC_P),
    COMBO(al_ti_hr, KC_Q),
    COMBO(al_hm_tr, KC_X),
    COMBO(al_ti_hm, KC_J),
    // ===============================================
    COMBO(al_hi_hm_hr, KC_SPACE),
    COMBO(al_ti_tm_tr, KC_ESCAPE),
    //COMBO(al_hi_tm_tr, KC_ENT),
    //COMBO(al_hi_hm_tr, KC_BSPC),
    COMBO(al_ti_tr_tm_tp, KC_CAPS),
    COMBO(al_hi_tm_hr, OSL(_NS)),
    COMBO(al_ti_tm_hr, OSL(_FF)),
    COMBO(al_hr_hp_l, OSL(_GO)),
    COMBO(al_hr_hp_r, OSL(_GO)),
    COMBO(al_tr_tp, OSL(_ME)),

    // ===============================================
    COMBO(na_spc, KC_SPACE),
    COMBO(na_esc, KC_ESCAPE),
    COMBO(na_del, KC_DELETE),
    COMBO(na_home, KC_HOME),
    COMBO(na_end, KC_END),

    // ===============================================
    COMBO(ns_2, KC_2),
    COMBO(ns_4, KC_4),
    COMBO(ns_7, KC_7),
    COMBO(ns_9, KC_9),
    // COMBO(ns_paren_r, KC_RPRN),
    // COMBO(ns_paren_l, KC_LPRN),
    // COMBO(ns_sqrbr_r, KC_RBRC),
    // COMBO(ns_sqrbr_l, KC_LBRC),
    // COMBO(ns_curbr_r, KC_RCBR),
    // COMBO(ns_curbr_l, KC_LCBR),
    // COMBO(ns_angbr_l, KC_LABK),
    // COMBO(ns_angbr_r, KC_RABK),
    // COMBO(ns_dot, KC_DOT),
    // COMBO(ns_semicolon, KC_SEMICOLON),
    // COMBO(ns_slash, KC_SLASH),
    // COMBO(ns_bslash, KC_BACKSLASH),
    // COMBO(ns_hyphen, KC_MINUS),
    // COMBO(ns_underscore, KC_UNDERSCORE),
    // COMBO(ns_comma, KC_COMMA),
    // COMBO(ns_equals, KC_EQUAL),
    // COMBO(ns_dblquots, KC_DQT),
    // COMBO(ns_qstn_mrk, KC_QUESTION),
    // COMBO(ns_excl_mrk, KC_EXCLAIM),
    // COMBO(ns_colon, KC_COLON),
    // COMBO(ns_asterisk, KC_ASTERISK),
    // COMBO(ns_ampersand, KC_AMPERSAND),
    // COMBO(ns_pipe, KC_PIPE),
    // COMBO(ns_backticks, KC_GRAVE),
    // COMBO(ns_tilde, KC_TILDE),
    // COMBO(ns_dollar, KC_DOLLAR),
    // COMBO(ns_percentage, KC_PERCENT),
    // COMBO(ns_plus, KC_PLUS),
    // COMBO(ns_hash, KC_HASH),
    // COMBO(ns_at, KC_AT),
    // COMBO(ns_circ, KC_CIRC),

    // ===============================================
    COMBO(ff_f2, KC_F2),
    COMBO(ff_f4, KC_F4),
    COMBO(ff_f7, KC_F7),
    COMBO(ff_f9, KC_F9),
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
    [_AL] = LAYOUT_split_3x5_3(
              AL_TP,   AL_TR,   AL_TM,   AL_TI, _______, /*||*/ _______,   AL_TI,   AL_TM,   AL_TR,   AL_TP,
             AL_HPL,   AL_HR,   AL_HM,   AL_HI,   AL_SI, /*||*/   AL_SI,   AL_HI,   AL_HM,   AL_HR,  AL_HPR,
            _______, _______,   AL_BM,   AL_BI, _______, /*||*/ _______,   AL_BI,   AL_BM, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    // TODO: add the rest of symbols and combos
    [_NS] = LAYOUT_split_3x5_3(
            _______,    KC_0,    KC_8,    KC_6, _______, /*||*/ _______,    KC_6,    KC_8,    KC_0, _______,
            _______,    KC_5,    KC_3,    KC_1, _______, /*||*/ _______,    KC_1,    KC_3,    KC_5, _______,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    [_FF] = LAYOUT_split_3x5_3(
             KC_F11,  KC_F10,   KC_F8,   KC_F6, _______, /*||*/ _______,   KC_F6,   KC_F8,  KC_F10,  KC_F11,
             KC_F12,   KC_F5,   KC_F3,   KC_F1, _______, /*||*/ _______,   KC_F1,   KC_F3,   KC_F5,  KC_F12,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    [_NL] = LAYOUT_split_3x5_3(
            TO(_AL), KC_BSPC,   KC_UP,  KC_TAB, _______, /*||*/ _______, NA_PGUP,  KC_TAB, KC_LGUI,
    TO(_NR), KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT, _______, /*||*/ _______, NA_PGDN,  KC_ESC, KC_LCTL, TO(_AL),
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    [_NR] = LAYOUT_split_3x5_3(
             TO(_NL), KC_LGUI, KC_TAB, NA_PGUP, _______, /*||*/ _______, KC_TAB ,   KC_UP, KC_BSPC,
    TO(_AL), TO(_AL), KC_LCTL, KC_ESC, NA_PGDN, _______, /*||*/ _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    [_ME] = LAYOUT_split_3x5_3(
            KC_BRIU, KC_MPRV, KC_VOLU, KC_MUTE, _______, /*||*/ _______, KC_MUTE, KC_VOLU, KC_MPRV, KC_BRIU,
            KC_BRID, KC_MNXT, KC_VOLD, KC_MPLY, _______, /*||*/ _______, KC_MPLY, KC_VOLD, KC_MNXT, KC_BRID,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    [_GO] = LAYOUT_split_3x5_3(
           ALT_9, ALT_GRV, CTL_PGUP, CTL_SFT_T, _______, /*||*/ _______, CTL_SFT_T, CTL_PGUP, ALT_GRV,   ALT_9,
           ALT_1, CTL_TAB, CTL_PGDN,     CTL_W, _______, /*||*/ _______,     CTL_W, CTL_PGDN, CTL_TAB,   ALT_1,
         _______, _______,  _______,   _______, _______, /*||*/ _______,   _______,  _______, _______, _______,
                            _______,   _______, _______, /*||*/ _______,   _______,  _______
    ),

    // TODO: mouse actions
    [_MO] = LAYOUT_split_3x5_3(
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),

    // TODO: finish layout and avoid combos
    [_AL_QWERTY] = LAYOUT_split_3x5_3(
                           KC_Q, KC_W, KC_E, KC_R, KC_T, /*||*/ KC_Y, KC_U, KC_I, KC_O, KC_P,
                  LT(_NR, KC_A), KC_S, KC_D, KC_F, KC_G, /*||*/ KC_H, KC_J, KC_K, KC_L, LT(_NR, KC_SEMICOLON),
                           KC_Z, KC_X, KC_C, KC_V, KC_B, /*||*/ KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),
};
