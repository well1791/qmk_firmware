#pragma once

/*
 * ===========================================================
 * ==== Fingers => [P]inky  | [R]ing | [M]iddle | [I]ndex ====
 * ====  Rows   => [H]ome   | [T]op  | [B]ottom | [S]ide  ====
 * ===========================================================
 *
 * Notes:
 *     Side = the side of the index
 *     Bottom = usuallly just 2 columns (index and middle)
 */

// ===== AL_ - Alpha =====
// AL_SIL is a plain keycode; AL_SIR is a distinct custom keycode (enum
// below) with the same tap, so the al_sil_sir chord can pair the two
// side keys — the combo engine matches keys by keycode and cannot
// distinguish two identical keycodes.
#define AL_SIL KC_V
#define AL_HI KC_E
#define AL_HM KC_I
#define AL_HR KC_A
#define AL_HPL LT(_NAV_R, KC_M)
#define AL_HPR LT(_NAV_L, KC_M)
#define AL_TI KC_G
#define AL_TM KC_U
#define AL_TR KC_O
#define AL_TP KC_H
#define AL_BI KC_J
#define AL_BM KC_K

// ===== NS_ - Numbers and Symbols =====
#define NS_SI KC_GRAVE
#define NS_HI KC_1
#define NS_HM KC_3
#define NS_HR KC_5
#define NS_HP KC_QUOTE
#define NS_TI KC_6
#define NS_TM KC_8
#define NS_TR KC_0
#define NS_TP KC_COMMA
#define NS_BI KC_QUESTION
#define NS_BM KC_TILDE

// ===== NA_ - Navigation =====
// ----- MV_ - Movement
#define NA_MV_SI LCTL(KC_Z)
#define NA_MV_LT KC_LEFT
#define NA_MV_HM KC_DOWN
#define NA_MV_RT KC_RIGHT
#define NA_MV_HP LSFT_T(KC_ENT)
#define NA_MV_TI KC_TAB
#define NA_MV_TM KC_UP
#define NA_MV_TR KC_BSPC
#define NA_MV_TP TO(_ALPHA)
#define NA_MV_BI KC_DELETE
#define NA_MV_BM KC_NO
// ----- MD_ - Modifiers
#define NA_MD_SI KC_NO
#define NA_MD_HI LSFT_T(KC_PGDN)
#define NA_MD_HM KC_ESC
#define NA_MD_HR KC_LCTL
#define NA_MD_HP TO(_ALPHA)
#define NA_MD_TI LGUI_T(KC_PGUP)
#define NA_MD_TM KC_TAB
#define NA_MD_TR KC_LALT
#define NA_MD_BI LCTL(KC_V)
#define NA_MD_BM LCTL(KC_C)

// ===== QW_ - QWERTY =====
#define QW_HPL LT(_NAV_R, KC_A)
#define QW_HPR LT(_NAV_L, KC_M)

// ===== CHR_ - Compose accents (chars layer) =====
enum custom_keycodes {
    CHR_A = SAFE_RANGE, // á
    CHR_E,              // é
    CHR_I,              // í
    CHR_O,              // ó
    CHR_U,              // ú
    CHR_N,              // ñ
    CHR_D,              // ü (kanata used the 'd' key for diaeresis)
    // Right side-index: same tap as AL_SIL (v) but a distinct keycode
    // so the al_sil_sir chord can pair the two side keys.
    AL_SIR,
    // Namespaced qwerty letters: distinct keycodes so alpha combos
    // (plain KC_*) can't fire inside the gaming layer.
    // Must stay alphabetical: process_record_user maps QW_A..QW_Z
    // arithmetically via KC_A + (keycode - QW_A).
    QW_A, QW_B, QW_C, QW_D, QW_E, QW_F, QW_G, QW_H, QW_I, QW_J, QW_K,
    QW_L, QW_M, QW_N, QW_O, QW_P, QW_Q, QW_R, QW_S, QW_T, QW_U, QW_V,
    QW_W, QW_X, QW_Y, QW_Z,
};
