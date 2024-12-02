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

enum layers {
    _AL = 0,
    _NS,
    _FF,
    _NA_L,
    _NA_R,
    _ME,
    _MO,
    _GO,
};

const uint16_t PROGMEM na_spc[] = {KC_LEFT, KC_DOWN, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM na_esc[] = {KC_TAB, KC_UP, KC_BSPC, COMBO_END};
const uint16_t PROGMEM na_del[] = {KC_UP, KC_BSPC, COMBO_END};
const uint16_t PROGMEM na_home[] = {KC_TAB, KC_BSPC, COMBO_END};
const uint16_t PROGMEM na_end[] = {KC_LEFT, KC_RIGHT, COMBO_END};

const uint16_t PROGMEM ff_f4[] = {KC_F1, KC_F7, COMBO_END};
const uint16_t PROGMEM ff_f5[] = {KC_F8, KC_F2, COMBO_END};
const uint16_t PROGMEM ff_f6[] = {KC_F9, KC_F3, COMBO_END};
const uint16_t PROGMEM ff_f12[] = {KC_F10, KC_F11, COMBO_END};

const uint16_t PROGMEM ns_4[] = {KC_7, KC_1, COMBO_END};
const uint16_t PROGMEM ns_5[] = {KC_8, KC_2, COMBO_END};
const uint16_t PROGMEM ns_6[] = {KC_9, KC_3, COMBO_END};
const uint16_t PROGMEM ns_paren_r[] = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM ns_paren_l[] = {KC_7, KC_8, COMBO_END};
const uint16_t PROGMEM ns_sqrbr_r[] = {KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM ns_sqrbr_l[] = {KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM ns_curbr_r[] = {KC_1, KC_3, COMBO_END};
const uint16_t PROGMEM ns_curbr_l[] = {KC_7, KC_9, COMBO_END};
const uint16_t PROGMEM ns_angbr_r[] = {KC_1, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_angbr_l[] = {KC_7, KC_0, COMBO_END};
const uint16_t PROGMEM ns_dot[] = {KC_8, KC_3, COMBO_END};
const uint16_t PROGMEM ns_semicolon[] = {KC_2, KC_9, COMBO_END};
const uint16_t PROGMEM ns_slash[] = {KC_1, KC_9, COMBO_END};
const uint16_t PROGMEM ns_bslash[] = {KC_7, KC_3, COMBO_END};
const uint16_t PROGMEM ns_hyphen[] = {KC_1, KC_0, COMBO_END};
const uint16_t PROGMEM ns_underscore[] = {KC_7, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_comma[] = {KC_1, KC_8, COMBO_END};
const uint16_t PROGMEM ns_equals[] = {KC_3, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_dblquots[] = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM ns_qstn_mrk[] = {KC_1, KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM ns_excl_mrk[] = {KC_7, KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM ns_colon[] = {KC_1, KC_8, KC_3, COMBO_END};
const uint16_t PROGMEM ns_asterisk[] = {KC_1, KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM ns_ampersand[] = {KC_1, KC_2, KC_9, COMBO_END};
const uint16_t PROGMEM ns_pipe[] = {KC_7, KC_8, KC_3, COMBO_END};
const uint16_t PROGMEM ns_backticks[] = {KC_2, KC_3, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_tilde[] = {KC_8, KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM ns_dollar[] = {KC_1, KC_3, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_percentage[] = {KC_7, KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM ns_plus[] = {KC_7, KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM ns_hash[] = {KC_8, KC_3, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_at[] = {KC_8, KC_9, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_circ[] = {KC_QUOTE, KC_9, COMBO_END};

const uint16_t PROGMEM al_s[] = {MODT_E, LT(_FF, KC_I), COMBO_END};
const uint16_t PROGMEM al_n[] = {LT(_FF, KC_I), MODT_A, COMBO_END};
const uint16_t PROGMEM al_r[] = {MODT_E, MODT_A, COMBO_END};
const uint16_t PROGMEM al_t[] = {MODT_A, LT(_NS, KC_U), COMBO_END};
const uint16_t PROGMEM al_d[] = {LT(_NS, KC_U), MODT_E, COMBO_END};
const uint16_t PROGMEM al_l[] = {MODT_E, MODT_O, COMBO_END};
const uint16_t PROGMEM al_c[] = {LT(_NS, KC_U), MODT_O, COMBO_END};
const uint16_t PROGMEM al_p[] = {MODT_H, LT(_NS, KC_U), COMBO_END};
const uint16_t PROGMEM al_y[] = {MODT_H, MODT_O, COMBO_END};
const uint16_t PROGMEM al_f[] = {MODT_E, KC_G, COMBO_END};
const uint16_t PROGMEM al_v[] = {MODT_H, KC_G, COMBO_END};
const uint16_t PROGMEM al_w[] = {MODT_H, MODT_A, COMBO_END};
const uint16_t PROGMEM al_q[] = {MODT_O, LT(_FF, KC_I), COMBO_END};
const uint16_t PROGMEM al_j[] = {MODT_O, KC_G, COMBO_END};

const uint16_t PROGMEM al_b_l[] = {LT(_NA_L, KC_M), MODT_E, COMBO_END};
const uint16_t PROGMEM al_b_r[] = {LT(_NA_R, KC_M), MODT_E, COMBO_END};
const uint16_t PROGMEM al_k_l[] = {LT(_NA_L, KC_M), MODT_A, COMBO_END};
const uint16_t PROGMEM al_k_r[] = {LT(_NA_R, KC_M), MODT_A, COMBO_END};
const uint16_t PROGMEM al_x_l[] = {LT(_NA_L, KC_M), MODT_H, COMBO_END};
const uint16_t PROGMEM al_x_r[] = {LT(_NA_R, KC_M), MODT_H, COMBO_END};
const uint16_t PROGMEM al_z_l[] = {LT(_NA_L, KC_M), MODT_O, COMBO_END};
const uint16_t PROGMEM al_z_r[] = {LT(_NA_R, KC_M), MODT_O, COMBO_END};

const uint16_t PROGMEM al_spc[] = {MODT_E, LT(_FF,KC_I), MODT_A, COMBO_END};
const uint16_t PROGMEM al_esc[] = {MODT_H, LT(_NS, KC_U), MODT_O, COMBO_END};
const uint16_t PROGMEM al_ret[] = {MODT_H, LT(_NS, KC_U), MODT_A, COMBO_END};
const uint16_t PROGMEM al_bspc[] = {MODT_E, LT(_FF, KC_I), MODT_O, COMBO_END};
const uint16_t PROGMEM al_tab_l[] = {LT(_FF, KC_I), MODT_A, LT(_NA_L, KC_M), COMBO_END};
const uint16_t PROGMEM al_tab_r[] = {LT(_NA_R, KC_M), MODT_A, LT(_FF, KC_I), COMBO_END};
const uint16_t PROGMEM al_caps[] = {MODT_A, LT(_FF, KC_I), MODT_H, COMBO_END};

const uint16_t PROGMEM al_osm_sft[] = {MODT_H, MODT_E, COMBO_END};
const uint16_t PROGMEM al_osm_gui[] = {LT(_NS, KC_U), LT(_FF, KC_I), COMBO_END};
const uint16_t PROGMEM al_osm_ctl[] = {MODT_O, MODT_A, COMBO_END};
const uint16_t PROGMEM al_osm_alt_l[] = {KC_G, LT(_NA_L, KC_M), COMBO_END};
const uint16_t PROGMEM al_osm_alt_r[] = {KC_G, LT(_NA_R, KC_M), COMBO_END};
const uint16_t PROGMEM al_osm_meh[] = {MODT_E, LT(_NS, KC_U), MODT_O, COMBO_END};

const uint16_t PROGMEM al_osl_ns[] = {MODT_E, LT(_NS, KC_U), MODT_A, COMBO_END};
const uint16_t PROGMEM al_osl_ff[] = {MODT_H, MODT_O, KC_G, COMBO_END};
const uint16_t PROGMEM al_osl_me[] = {LT(_NS, KC_U), MODT_O, KC_G, COMBO_END};
const uint16_t PROGMEM al_osl_mo_l[] = {LT(_NA_L, KC_M), MODT_A, LT(_NS, KC_U), COMBO_END};
const uint16_t PROGMEM al_osl_mo_r[] = {LT(_NA_R, KC_M), MODT_A, LT(_NS, KC_U), COMBO_END};
const uint16_t PROGMEM al_osl_go_l[] = {MODT_E, MODT_A, LT(_NA_L, KC_M), COMBO_END};
const uint16_t PROGMEM al_osl_go_r[] = {LT(_NA_R, KC_M), MODT_A, MODT_E, COMBO_END};

combo_t key_combos[] = {
    COMBO(na_spc, KC_SPACE),
    COMBO(na_esc, KC_ESCAPE),
    COMBO(na_del, KC_DELETE),
    COMBO(na_home, KC_HOME),
    COMBO(na_end, KC_END),

    COMBO(ff_f4, KC_F4),
    COMBO(ff_f5, KC_F5),
    COMBO(ff_f6, KC_F6),
    COMBO(ff_f12, KC_F12),

    COMBO(ns_4, KC_4),
    COMBO(ns_5, KC_5),
    COMBO(ns_6, KC_6),
    COMBO(ns_paren_r, KC_RPRN),
    COMBO(ns_paren_l, KC_LPRN),
    COMBO(ns_sqrbr_r, KC_RBRC),
    COMBO(ns_sqrbr_l, KC_LBRC),
    COMBO(ns_curbr_r, KC_RCBR),
    COMBO(ns_curbr_l, KC_LCBR),
    COMBO(ns_angbr_l, KC_LABK),
    COMBO(ns_angbr_r, KC_RABK),
    COMBO(ns_dot, KC_DOT),
    COMBO(ns_semicolon, KC_SEMICOLON),
    COMBO(ns_slash, KC_SLASH),
    COMBO(ns_bslash, KC_BACKSLASH),
    COMBO(ns_hyphen, KC_MINUS),
    COMBO(ns_underscore, KC_UNDERSCORE),
    COMBO(ns_comma, KC_COMMA),
    COMBO(ns_equals, KC_EQUAL),
    COMBO(ns_dblquots, KC_DQT),
    COMBO(ns_qstn_mrk, KC_QUESTION),
    COMBO(ns_excl_mrk, KC_EXCLAIM),
    COMBO(ns_colon, KC_COLON),
    COMBO(ns_asterisk, KC_ASTERISK),
    COMBO(ns_ampersand, KC_AMPERSAND),
    COMBO(ns_pipe, KC_PIPE),
    COMBO(ns_backticks, KC_GRAVE),
    COMBO(ns_tilde, KC_TILDE),
    COMBO(ns_dollar, KC_DOLLAR),
    COMBO(ns_percentage, KC_PERCENT),
    COMBO(ns_plus, KC_PLUS),
    COMBO(ns_hash, KC_HASH),
    COMBO(ns_at, KC_AT),
    COMBO(ns_circ, KC_CIRC),

    COMBO(al_spc, KC_SPACE),
    COMBO(al_esc, KC_ESCAPE),
    COMBO(al_ret, KC_ENTER),
    COMBO(al_bspc, KC_BACKSPACE),
    COMBO(al_tab_l, KC_TAB),
    COMBO(al_tab_r, KC_TAB),
    COMBO(al_caps, KC_CAPS),

    COMBO(al_s, KC_S),
    COMBO(al_n, KC_N),
    COMBO(al_r, KC_R),
    COMBO(al_t, KC_T),
    COMBO(al_d, KC_D),
    COMBO(al_l, KC_L),
    COMBO(al_c, KC_C),
    COMBO(al_p, KC_P),
    COMBO(al_y, KC_Y),
    COMBO(al_f, KC_F),
    COMBO(al_v, KC_V),
    COMBO(al_w, KC_W),
    COMBO(al_q, KC_Q),
    COMBO(al_j, KC_J),
    COMBO(al_b_l, KC_B),
    COMBO(al_b_r, KC_B),
    COMBO(al_k_l, KC_K),
    COMBO(al_k_r, KC_K),
    COMBO(al_x_l, KC_X),
    COMBO(al_x_r, KC_X),
    COMBO(al_z_l, KC_Z),
    COMBO(al_z_r, KC_Z),

    COMBO(al_osm_ctl, OSM(MOD_LCTL)),
    COMBO(al_osm_sft, OSM(MOD_LSFT)),
    COMBO(al_osm_alt_l, OSM(MOD_LALT)),
    COMBO(al_osm_alt_r, OSM(MOD_LALT)),
    COMBO(al_osm_gui, OSM(MOD_LGUI)),
    COMBO(al_osm_meh, OSM(MOD_MEH)),

    COMBO(al_osl_ns, OSL(_NS)),
    COMBO(al_osl_ff, OSL(_FF)),
    COMBO(al_osl_me, OSL(_ME)),
    COMBO(al_osl_mo_l, OSL(_MO)),
    COMBO(al_osl_mo_r, OSL(_MO)),
    COMBO(al_osl_go_l, OSL(_GO)),
    COMBO(al_osl_go_r, OSL(_GO)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_AL] = LAYOUT_split_3x5_3(
                   KC_G,  MODT_O, LT(_NS, KC_U),  MODT_H, _______,          _______,  MODT_H, LT(_NS, KC_U),  MODT_O,            KC_G,
        LT(_NA_R, KC_M),  MODT_A, LT(_FF, KC_I),  MODT_E, _______,          _______,  MODT_E, LT(_FF, KC_I),  MODT_A, LT(_NA_L, KC_M),
                _______, _______,       _______, _______, _______,          _______, _______,       _______, _______,         _______,
                                        _______, _______, _______,          _______, _______,       _______
    ),

    [_NS] = LAYOUT_split_3x5_3(
           KC_0,    KC_9,    KC_8,    KC_7, _______,          _______,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_QUOT,    KC_3,    KC_2,    KC_1, _______,          _______,    KC_1,    KC_2,    KC_3, KC_QUOT,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
                          _______, _______, _______,          _______, _______, _______
    ),

    [_FF] = LAYOUT_split_3x5_3(
         KC_F11,   KC_F9,   KC_F8,   KC_F7, _______,          _______,   KC_F7,   KC_F8,   KC_F9,  KC_F11,
         KC_F10,   KC_F3,   KC_F2,   KC_F1, _______,          _______,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
                          _______, _______, _______,          _______, _______, _______
    ),

    [_NA_L] = LAYOUT_split_3x5_3(
         TO(_AL), KC_BACKSPACE,   KC_UP,  KC_TAB, _______,          _______, LALT_T(KC_PGUP), _______, LGUI_T(KC_COPY), TO(_NA_R),
        KC_ENTER,      KC_LEFT, KC_DOWN, KC_RGHT, _______,          _______, LSFT_T(KC_PGDN), _______, LCTL_T(KC_PSTE),   TO(_AL),
         _______,      _______, _______, _______, _______,          _______,         _______, _______,         _______,   _______,
                                _______, _______, _______,          _______,         _______, _______
    ),

    [_NA_R] = LAYOUT_split_3x5_3(
        TO(_NA_L), LGUI_T(KC_COPY), _______, LALT_T(KC_PGUP), _______,          _______,  KC_TAB,   KC_UP, KC_BACKSPACE,  TO(_AL),
          TO(_AL), LCTL_T(KC_PSTE), _______, LSFT_T(KC_PGDN), _______,          _______, KC_LEFT, KC_DOWN,      KC_RGHT, KC_ENTER,
          _______,         _______, _______,         _______, _______,          _______, _______, _______,      _______,  _______,
                                    _______,         _______, _______,          _______, _______, _______
    ),

    [_ME] = LAYOUT_split_3x5_3(
        KC_BRIU, KC_MPRV, KC_VOLU, KC_MUTE, _______,          _______, KC_MUTE, KC_VOLU, KC_MPRV, KC_BRIU,
        KC_BRID, KC_MNXT, KC_VOLD, KC_MPLY, _______,          _______, KC_MPLY, KC_VOLD, KC_MNXT, KC_BRID,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
                          _______, _______, _______,          _______, _______, _______
    ),

    [_MO] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
                          _______, _______, _______,          _______, _______, _______
    ),

    [_GO] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
                          _______, _______, _______,          _______, _______, _______
    )
};
