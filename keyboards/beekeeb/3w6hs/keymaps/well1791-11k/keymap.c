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
#include "keymap_keycodes.h"

enum layers {
    _ALPHA = 0,
    _NUMSYM, // Numbers and Symbols
    _FUNCT, // F1-F12
    _NAV_L,
    _NAV_R,
    _MEDIA,
    _GO, // GO = Go-to shortcuts
    _MOUSE,
    _QWERTY,
    _CHARS,
    _MODS,
};

/*
 * ============================================================
 * ==== Fingers => [I]ndex | [M]iddle | [R]ing   | [P]inky ====
 * ====  Rows   => [H]ome  | [T]op    | [B]ottom | [S]ide  ====
 * ============================================================
 *
 * Each layout group lives in its own _<name>.def module. Every module
 * is textually included three times below, gated on a #define, to feed
 * the three QMK singletons (C requires a single array per symbol):
 *
 *   Pass 1  KMB_COMBO_ARRAYS   -> combo key arrays (file scope)
 *   Pass 2  KMB_COMBO_ENTRIES  -> key_combos[] initializer
 *   Pass 3  KMB_LAYER          -> keymaps[][] initializer
 *
 * Modules with combos (alpha/numsym/funct/nav/qwerty/mods) populate
 * all three passes; layer-only modules (media/go/chars/mouse) populate
 * pass 3 only. (qwerty/mods combos: g+h alpha<->qwerty toggle; parity
 * mods chords — see _mods.def for reachability notes.)
 */

// ===========================================================
// ===== Pass 1: combo key arrays (file scope) ===============
// ===========================================================
#define KMB_COMBO_ARRAYS
#include "_alpha.def"
#include "_numsym.def"
#include "_funct.def"
#include "_nav.def"
#include "_qwerty.def"
#include "_mods.def"
#undef KMB_COMBO_ARRAYS

combo_t key_combos[] = {
    // ===========================================================
    // ===== Pass 2: combo registry entries =====================
    // ===========================================================
    #define KMB_COMBO_ENTRIES
    #include "_alpha.def"
    #include "_numsym.def"
    #include "_funct.def"
    #include "_nav.def"
    #include "_qwerty.def"
    #include "_mods.def"
    #undef KMB_COMBO_ENTRIES
};

// Compose sequence: tap RALT, then the mark, then the letter.
// 20ms gaps mirror kanata's (macro ralt 20 <mark> 20 <letter>).
static void compose_accent(keyrecord_t *record, uint16_t mark, uint16_t letter) {
    if (record->event.pressed) {
        tap_code16(KC_RALT);
        wait_ms(20);
        tap_code16(mark);
        wait_ms(20);
        tap_code16(letter);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QW_A ... QW_Z:
            if (record->event.pressed) tap_code16(KC_A + (keycode - QW_A));
            return false;
        case AL_SIR:
            if (record->event.pressed) tap_code(KC_Z);
            return false;
        case CHR_A: compose_accent(record, KC_QUOTE, KC_A); return false;        // á
        case CHR_E: compose_accent(record, KC_QUOTE, KC_E); return false;        // é
        case CHR_I: compose_accent(record, KC_QUOTE, KC_I); return false;        // í
        case CHR_O: compose_accent(record, KC_QUOTE, KC_O); return false;        // ó
        case CHR_U: compose_accent(record, KC_QUOTE, KC_U); return false;        // ú
        case CHR_N: compose_accent(record, LSFT(KC_GRV), KC_N); return false;    // ñ  (~ then n)
        case CHR_D: compose_accent(record, LSFT(KC_QUOTE), KC_U); return false;  // ü  (" then u)
    }
    return true;
}

// Mirrors kanata os_cwc: letters, digits, bspc/del, arrows and '-' keep
// caps-word alive; any other key ends it.
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_LEFT:
        case KC_RIGHT:
        case KC_UP:
        case KC_DOWN:
        case KC_MINUS:
            return true;
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // ===========================================================
    // ===== Pass 3: layer map ==================================
    // ===========================================================
    #define KMB_LAYER
    #include "_alpha.def"
    #include "_numsym.def"
    #include "_funct.def"
    #include "_nav.def"
    #include "_media.def"
    #include "_go.def"
    #include "_chars.def"
    #include "_mouse.def"
    #include "_qwerty.def"
    #include "_mods.def"
    #undef KMB_LAYER
};
