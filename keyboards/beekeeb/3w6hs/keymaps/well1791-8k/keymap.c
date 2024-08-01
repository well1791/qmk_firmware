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
};

// na_ stands for "navigation"
const uint16_t PROGMEM na_spc[] = {KC_LEFT, KC_DOWN, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM na_esc[] = {KC_TAB, KC_UP, KC_BSPC, COMBO_END};
const uint16_t PROGMEM na_del[] = {KC_UP, KC_BSPC, COMBO_END};
const uint16_t PROGMEM na_home[] = {KC_TAB, KC_BSPC, COMBO_END};
const uint16_t PROGMEM na_end[] = {KC_LEFT, KC_RIGHT, COMBO_END};

// ff_ stands for "function"
const uint16_t PROGMEM ff_f4[] = {KC_F1, KC_F7, COMBO_END};
const uint16_t PROGMEM ff_f5[] = {KC_F8, KC_F2, COMBO_END};
const uint16_t PROGMEM ff_f6[] = {KC_F9, KC_F3, COMBO_END};
const uint16_t PROGMEM ff_f12[] = {KC_F10, KC_F11, COMBO_END};

// ns_ stands for "numbers and symbols"
const uint16_t PROGMEM ns_4[] = {KC_7, KC_1, COMBO_END};
const uint16_t PROGMEM ns_5[] = {KC_8, KC_2, COMBO_END};
const uint16_t PROGMEM ns_6[] = {KC_9, KC_3, COMBO_END};
const uint16_t PROGMEM ns_angbr_l[] = {KC_7, KC_8, COMBO_END};
const uint16_t PROGMEM ns_angbr_r[] = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM ns_sqrbr_l[] = {KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM ns_sqrbr_r[] = {KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM ns_curbr_l[] = {KC_7, KC_9, COMBO_END};
const uint16_t PROGMEM ns_curbr_r[] = {KC_1, KC_3, COMBO_END};
const uint16_t PROGMEM ns_paren_l[] = {KC_7, KC_0, COMBO_END};
const uint16_t PROGMEM ns_paren_r[] = {KC_1, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_dot[] = {KC_8, KC_3, COMBO_END};
const uint16_t PROGMEM ns_semicolon[] = {KC_9, KC_2, COMBO_END};
const uint16_t PROGMEM ns_slash[] = {KC_1, KC_9, COMBO_END};
const uint16_t PROGMEM ns_bslash[] = {KC_7, KC_3, COMBO_END};
const uint16_t PROGMEM ns_hyphen[] = {KC_1, KC_0, COMBO_END};
const uint16_t PROGMEM ns_underscore[] = {KC_7, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_comma[] = {KC_1, KC_8, COMBO_END};
const uint16_t PROGMEM ns_equals[] = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM ns_dblquots[] = {KC_3, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_qstn_mrk[] = {KC_1, KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM ns_excl_mrk[] = {KC_7, KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM ns_colon[] = {KC_1, KC_8, KC_3, COMBO_END};
const uint16_t PROGMEM ns_asterisk[] = {KC_1, KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM ns_ampersand[] = {KC_1, KC_2, KC_9, COMBO_END};
const uint16_t PROGMEM ns_pipe[] = {KC_7, KC_8, KC_3, COMBO_END};
const uint16_t PROGMEM ns_backticks[] = {KC_2, KC_3, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_tilde[] = {KC_8, KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM ns_dollar[] = {KC_1, KC_2, KC_3, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_percentage[] = {KC_7, KC_8, KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM ns_plus[] = {KC_7, KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM ns_hash[] = {KC_8, KC_3, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_at[] = {KC_9, KC_QUOTE, COMBO_END};
const uint16_t PROGMEM ns_circ[] = {KC_7, KC_2, COMBO_END};

// ===========================================================
// Finger - [P]inky  | [R]ing | [M]iddle | [I]ndex
//  Row   - [B]ottom | [T]op
// ===========================================================
//          | | | | |     mb_rb     | | | | |
//          | |*|*| |     mb_rb     | |*|*| |
const uint16_t PROGMEM al_mb_rb[] = {AL_MB, AL_RB, COMBO_END};
//          | | | | |     ib_rb     | | | | |
//          | |*| |*|     ib_rb     |*| |*| |
const uint16_t PROGMEM al_ib_rb[] = {AL_IB, AL_RB, COMBO_END};
//          | | | | |     ib_mb     | | | | |
//          | | |*|*|     ib_mb     |*|*| | |
const uint16_t PROGMEM al_ib_mb[] = {AL_IB, AL_MB, COMBO_END};
//          | | | | |     rb_pb     | | | | |
//          |*|*| | |     rb_pb     | | |*|*|
const uint16_t PROGMEM al_rb_pb_l[] = {AL_RB, AL_PBL, COMBO_END};
const uint16_t PROGMEM al_rb_pb_r[] = {AL_RB, AL_PBR, COMBO_END};
//          | | | | |     ib_pb     | | | | |
//          |*| | |*|     ib_pb     |*| | |*|
const uint16_t PROGMEM al_ib_pb_l[] = {AL_IB, AL_PBL, COMBO_END};
const uint16_t PROGMEM al_ib_pb_r[] = {AL_IB, AL_PBR, COMBO_END};
// ===========================================================
//          | |*| | |     ib_rt     | | |*| |
//          | | | |*|     ib_rt     |*| | | |
const uint16_t PROGMEM al_ib_rt[] = {AL_IB, AL_RT, COMBO_END};
//          | | |*| |     ib_mt     | |*| | |
//          | | | |*|     ib_mt     |*| | | |
const uint16_t PROGMEM al_ib_mt[] = {AL_IB, AL_MT, COMBO_END};
//          |*| | | |     ib_pt     | | | |*|
//          | | | |*|     ib_pt     |*| | | |
const uint16_t PROGMEM al_ib_pt[] = {AL_IB, AL_PT, COMBO_END};
//          | |*| | |     mb_rt     | | |*| |
//          | | |*| |     mb_rt     | |*| | |
const uint16_t PROGMEM al_mb_rt[] = {AL_MB, AL_RT, COMBO_END};
// ===========================================================
//          | |*|*| |     mt_rt     | |*|*| |
//          | | | | |     mt_rt     | | | | |
const uint16_t PROGMEM al_mt_rt[] = {AL_MT, AL_RT, COMBO_END};
//          | |*| |*|     it_rt     |*| |*| |
//          | | | | |     it_rt     | | | | |
const uint16_t PROGMEM al_it_rt[] = {AL_IT, AL_RT, COMBO_END};
//          | | |*|*|     it_mt     |*|*| | |
//          | | | | |     it_mt     | | | | |
const uint16_t PROGMEM al_it_mt[] = {AL_IT, AL_MT, COMBO_END};
//          |*|*| | |     rt_pt     | | |*|*|
//          | | | | |     rt_pt     | | | | |
const uint16_t PROGMEM al_rt_pt[] = {AL_RT, AL_PT, COMBO_END};
//          |*| | |*|     it_pt     |*| | |*|
//          | | | | |     it_pt     | | | | |
const uint16_t PROGMEM al_it_pt[] = {AL_IT, AL_PT, COMBO_END};
// ===========================================================
//          | | |*| |     mt_rb     | |*| | |
//          | |*| | |     mt_rb     | | |*| |
const uint16_t PROGMEM al_mt_rb[] = {AL_MT, AL_RB, COMBO_END};
//          | |*| | |     rt_pb     | | |*| |
//          |*| | | |     rt_pb     | | | |*|
const uint16_t PROGMEM al_rt_pb_l[] = {AL_RT, AL_PBL, COMBO_END};
const uint16_t PROGMEM al_rt_pb_r[] = {AL_RT, AL_PBR, COMBO_END};
//          | | | |*|     it_pb     |*| | | |
//          |*| | | |     it_pb     | | | |*|
const uint16_t PROGMEM al_it_pb_l[] = {AL_IT, AL_PBL, COMBO_END};
const uint16_t PROGMEM al_it_pb_r[] = {AL_IT, AL_PBR, COMBO_END};
//          | | | |*|     it_mb     |*| | | |
//          | | |*| |     it_mb     | |*| | |
const uint16_t PROGMEM al_it_mb[] = {AL_IT, AL_MB, COMBO_END};
//          | | | |*|     it_rb     |*| | | |
//          | |*| | |     it_rb     | | |*| |
const uint16_t PROGMEM al_it_rb[] = {AL_IT, AL_RB, COMBO_END};
// ===========================================================
//          | | | |*|     ib_it     |*| | | |
//          | | | |*|     ib_it     |*| | | |
const uint16_t PROGMEM al_ib_it[] = {AL_IB, AL_IT, COMBO_END};
//          | | |*| |     mb_mt     | |*| | |
//          | | |*| |     mb_mt     | |*| | |
const uint16_t PROGMEM al_mb_mt[] = {AL_MB, AL_MT, COMBO_END};
//          | |*| | |     rb_rt     | | |*| |
//          | |*| | |     rb_rt     | | |*| |
const uint16_t PROGMEM al_rb_rt[] = {AL_RB, AL_RT, COMBO_END};
//          |*| | | |     pb_pt     | | | |*|
//          |*| | | |     pb_pt     | | | |*|
const uint16_t PROGMEM al_pb_pt_l[] = {AL_PBL, AL_PT, COMBO_END};
const uint16_t PROGMEM al_pb_pt_r[] = {AL_PBR, AL_PT, COMBO_END};
// ===========================================================
//          | | | | |     ib_mb_rb     | | | | |
//          | |*|*|*|     ib_mb_rb     |*|*|*| |
const uint16_t PROGMEM al_ib_mb_rb[] = {AL_IB, AL_MB, AL_RB, COMBO_END};
//          | |*|*|*|     it_mt_rt     |*|*|*| |
//          | | | | |     it_mt_rt     | | | | |
const uint16_t PROGMEM al_it_mt_rt[] = {AL_IT, AL_MT, AL_RT, COMBO_END};
//          | |*|*| |     ib_mt_rt     | |*|*| |
//          | | | |*|     ib_mt_rt     |*| | | |
const uint16_t PROGMEM al_ib_mt_rt[] = {AL_IB, AL_MT, AL_RT, COMBO_END};
//          | | |*|*|     it_mt_rb     |*|*| | |
//          | |*| | |     it_mt_rb     | | |*| |
const uint16_t PROGMEM al_it_mt_rb[] = {AL_IT, AL_MT, AL_RB, COMBO_END};
//          | |*| | |     ib_mb_rt     | | |*| |
//          | | |*|*|     ib_mb_rt     |*|*| | |
const uint16_t PROGMEM al_ib_mb_rt[] = {AL_IB, AL_MB, AL_RT, COMBO_END};
//          | | |*| |     ib_mb_rt     | |*| | |
//          | |*| |*|     ib_mb_rt     |*| |*| |
const uint16_t PROGMEM al_ib_mt_rb[] = {AL_IB, AL_MT, AL_RB, COMBO_END};
//          | | | |*|     it_mb_rb     |*| | | |
//          | |*|*| |     it_mb_rb     | |*|*| |
const uint16_t PROGMEM al_it_mb_rb[] = {AL_IT, AL_MB, AL_RB, COMBO_END};
//          |*|*|*| |     mt_rt_pt     | |*|*|*|
//          | | | | |     mt_rt_pt     | | | | |
const uint16_t PROGMEM al_mt_rt_pt[] = {AL_MT, AL_RT, AL_PT, COMBO_END};
//          | | | | |     mb_rb_pb     | | | | |
//          |*|*|*| |     mb_rb_pb     | |*|*|*|
const uint16_t PROGMEM al_mb_rb_pb_l[] = {AL_MB, AL_RB, AL_PBL, COMBO_END};
const uint16_t PROGMEM al_mb_rb_pb_r[] = {AL_MB, AL_RB, AL_PBR, COMBO_END};
//          | | |*| |     mt_rb_pb     | |*| | |
//          |*|*| | |     mt_rb_pb     | | |*|*|
const uint16_t PROGMEM al_mt_rb_pb_l[] = {AL_MT, AL_RB, AL_PBL, COMBO_END};
const uint16_t PROGMEM al_mt_rb_pb_r[] = {AL_MT, AL_RB, AL_PBR, COMBO_END};
// ===========================================================
//          |*|*|*|*|     it_rt_mt_pt     |*|*|*|*|
//          | | | | |     it_rt_mt_pt     | | | | |
const uint16_t PROGMEM al_it_rt_mt_pt[] = {AL_IT, AL_RT, AL_MT, AL_PT, COMBO_END};
// ===========================================================


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

    // ===============================================
    //       mb_rb           //=>   | | | | |
    COMBO(al_mb_rb, KC_N),   //=>   | |*|*| |

    //       ib_rb           //=>   | | | | |
    COMBO(al_ib_rb, KC_S),   //=>   |*| |*| |

    //       ib_mb           //=>   | | | | |
    COMBO(al_ib_mb, KC_R),   //=>   |*|*| | |

    //       ib_rt           //=>   | | |*| |
    COMBO(al_ib_rt, KC_T),   //=>   |*| | | |

    //       mt_rt           //=>   | |*|*| |
    COMBO(al_mt_rt, KC_D),   //=>   | | | | |

    //       it_rt           //=>   |*| |*| |
    COMBO(al_it_rt, KC_L),   //=>   | | | | |

    //       it_mt           //=>   |*|*| | |
    COMBO(al_it_mt, KC_C),   //=>   | | | | |

    COMBO(al_ib_pb_l, KC_P), //=>   | | | | |
    COMBO(al_ib_pb_r, KC_P), //=>   |*| | |*|

    //       ib_pt           //=>   | | | |*|
    COMBO(al_ib_pt, KC_Y),   //=>   |*| | | |

    //       it_pt           //=>   |*| | |*|
    COMBO(al_it_pt, KC_B),   //=>   | | | | |

    //       mt_rb           //=>   | |*| | |
    COMBO(al_mt_rb, KC_F),   //=>   | | |*| |

    //       mb_rt           //=>   | | |*| |
    COMBO(al_mb_rt, KC_V),   //=>   | |*| | |

    //       ib_mt           //=>   | |*| | |
    COMBO(al_ib_mt, KC_W),   //=>   |*| | | |

    //       it_rb           //=>   |*| | | |
    COMBO(al_it_rb, KC_Q),   //=>   | | |*| |

    COMBO(al_it_pb_l, KC_X), //=>   |*| | | |
    COMBO(al_it_pb_r, KC_X), //=>   | | | |*|

    COMBO(al_rb_pb_l, KC_K), //=>   | | | | |
    COMBO(al_rb_pb_r, KC_K), //=>   | | |*|*|

    //       rt_pt           //=>   | | |*|*|
    COMBO(al_rt_pt, KC_J),   //=>   | | | | |

    COMBO(al_rt_pb_l, KC_Z), //=>   | | |*| |
    COMBO(al_rt_pb_r, KC_Z), //=>   | | | |*|

    // ===============================================
    //       ib_it                    //=>   |*| | | |
    COMBO(al_ib_it, OSM(MOD_LSFT)),   //=>   |*| | | |

    //       mb_mt                    //=>   | |*| | |
    COMBO(al_mb_mt, OSM(MOD_LGUI)),   //=>   | |*| | |

    //       rb_rt                    //=>   | | |*| |
    COMBO(al_rb_rt, OSM(MOD_LCTL)),   //=>   | | |*| |

    COMBO(al_pb_pt_l, OSM(MOD_LALT)), //=>   | | | |*|
    COMBO(al_pb_pt_r, OSM(MOD_LALT)), //=>   | | | |*|

    // ===============================================
    //       ib_mb_rb                 //=>   | | | | |
    COMBO(al_ib_mb_rb, KC_SPACE),     //=>   |*|*|*| |

    //       it_mt_rt                 //=>   |*|*|*| |
    COMBO(al_it_mt_rt, KC_ESCAPE),    //=>   | | | | |

    //       it_mt_rb                 //=>   |*|*| | |
    COMBO(al_it_mt_rb, KC_ENT),       //=>   | | |*| |

    //       ib_mb_rt                 //=>   | | |*| |
    COMBO(al_ib_mb_rt, KC_BSPC),      //=>   |*|*| | |

    //       it_rt_mt_pt              //=>   |*|*|*|*|
    COMBO(al_it_rt_mt_pt, KC_CAPS),   //=>   | | | | |

    //       ib_mt_rt                 //=>   | |*|*| |
    COMBO(al_ib_mt_rt, OSM(MOD_MEH)), //=>   |*| | | |

    //       ib_mt_rb                 //=>   | |*| | |
    COMBO(al_ib_mt_rb, OSL(_NS)),     //=>   |*| |*| |

    //       it_mt_rb                 //=>   |*| | | |
    COMBO(al_it_mb_rb, OSL(_FF)),     //=>   | |*|*| |

    //       mt_rt_pt                 //=>   | |*|*|*|
    COMBO(al_mt_rt_pt, OSL(_ME)),     //=>   | | | | |

    COMBO(al_mb_rb_pb_l, OSL(_GO)),   //=>   | | | | |
    COMBO(al_mb_rb_pb_r, OSL(_GO)),   //=>   | |*|*|*|
};

enum custom_keycodes {
    C_TAB = SAFE_RANGE,
    A_1,
    A_9,
    C_W,
    C_PGUP,
    C_PGDN,
    A_GRV,
    C_A_Q,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case C_TAB:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_TAB);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;

        case A_1:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_1);
            } else {
                unregister_code(KC_LALT);
            }
            return false;

        case A_9:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_9);
            } else {
                unregister_code(KC_LALT);
            }
            return false;

        case C_W:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_W);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;

        case C_PGUP:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_PGUP);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;

        case C_PGDN:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_PGDN);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;

        case A_GRV: // same app
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_GRAVE);
            } else {
                unregister_code(KC_LALT);
            }
            return false;

        case C_A_Q: // workspace (zen browser)
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LALT);
                tap_code(KC_Q);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LALT);
            }
            return false;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_AL] = LAYOUT_split_3x5_3(                      /*||*/
          AL_PT,   AL_RT,   AL_MT,   AL_IT, _______, /*||*/ _______,   AL_IT,   AL_MT,   AL_RT,   AL_PT,
         AL_PBL,   AL_RB,   AL_MB,   AL_IB, _______, /*||*/ _______,   AL_IB,   AL_MB,   AL_RB,  AL_PBR,
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                          _______, _______, _______, /*||*/ _______, _______, _______
    ),                                               /*||*/

    [_NS] = LAYOUT_split_3x5_3(                      /*||*/
           KC_0,    KC_9,    KC_8,    KC_7, _______, /*||*/ _______,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_QUOT,    KC_3,    KC_2,    KC_1, _______, /*||*/ _______,    KC_1,    KC_2,    KC_3, KC_QUOT,
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                          _______, _______, _______, /*||*/ _______, _______, _______
    ),                                               /*||*/

    [_FF] = LAYOUT_split_3x5_3(                      /*||*/
         KC_F11,   KC_F9,   KC_F8,   KC_F7, _______, /*||*/ _______,   KC_F7,   KC_F8,   KC_F9,  KC_F11,
         KC_F10,   KC_F3,   KC_F2,   KC_F1, _______, /*||*/ _______,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                          _______, _______, _______, /*||*/ _______, _______, _______
    ),                                               /*||*/

    [_NL] = LAYOUT_split_3x5_3(                      /*||*/
        TO(_AL), KC_BSPC,   KC_UP,  KC_TAB, _______, /*||*/ _______,  N_PGUP,  KC_TAB, KC_LGUI, TO(_NR),
         KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT, _______, /*||*/ _______,  N_PGDN,  KC_ESC, KC_LCTL, TO(_AL),
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                          _______, _______, _______, /*||*/ _______, _______, _______
    ),                                               /*||*/

    [_NR] = LAYOUT_split_3x5_3(                      /*||*/
        TO(_NL), KC_LGUI,  KC_TAB,  N_PGUP, _______, /*||*/ _______,  KC_TAB,   KC_UP, KC_BSPC, TO(_AL),
        TO(_AL), KC_LCTL,  KC_ESC,  N_PGDN, _______, /*||*/ _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT,
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                          _______, _______, _______, /*||*/ _______, _______, _______
    ),                                               /*||*/

    [_ME] = LAYOUT_split_3x5_3(                      /*||*/
        KC_BRIU, KC_MPRV, KC_VOLU, KC_MUTE, _______, /*||*/ _______, KC_MUTE, KC_VOLU, KC_MPRV, KC_BRIU,
        KC_BRID, KC_MNXT, KC_VOLD, KC_MPLY, _______, /*||*/ _______, KC_MPLY, KC_VOLD, KC_MNXT, KC_BRID,
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                          _______, _______, _______, /*||*/ _______, _______, _______
    ),                                               /*||*/

    [_GO] = LAYOUT_split_3x5_3(                      /*||*/
          C_A_Q,     A_9,  C_PGUP,  KC_TAB, _______, /*||*/ _______,  KC_TAB, C_PGUP,      A_9,   C_A_Q,
          A_GRV,   C_TAB,  C_PGDN,     C_W, _______, /*||*/ _______,     C_W, C_PGDN,    C_TAB,   A_GRV,
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                          _______, _______, _______, /*||*/ _______, _______, _______
    ),                                               /*||*/

    [_MO] = LAYOUT_split_3x5_3(                      /*||*/
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                          _______, _______, _______, /*||*/ _______, _______, _______
    )                                                /*||*/
};
