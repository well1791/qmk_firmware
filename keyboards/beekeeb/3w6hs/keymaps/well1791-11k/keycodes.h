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
#define AL_SI KC_Z
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
#define NS_SI KC_AT
#define NS_HI KC_1
#define NS_HM KC_3
#define NS_HR KC_5
#define NS_HP KC_QUOTE
#define NS_TI KC_6
#define NS_TM KC_8
#define NS_TR KC_0
#define NS_TP KC_ASTERISK
#define NS_BI KC_PLUS
#define NS_BM KC_HASH

// ===== NA_ - Navigation =====
// ----- Movement
#define NA_MV_LT KC_LEFT
#define NA_MV_HM KC_DOWN
#define NA_MV_RT KC_RIGHT
#define NA_MV_HP KC_ENT
#define NA_MV_TI KC_TAB
#define NA_MV_TM KC_UP
#define NA_MV_TR KC_BSPC
#define NA_MV_TP TO(_ALPHA)
// ----- Modifiers
#define NA_MD_HI LSFT_T(KC_PGDN)
#define NA_MD_HM KC_ESC
#define NA_MD_HR KC_LCTL
#define NA_MD_HP TO(_ALPHA)
#define NA_MD_TI LGUI_T(KC_PGUP)
#define NA_MD_TM KC_TAB
#define NA_MD_TR KC_LALT
// #define NA_MD_TP TO(_NAV_R)
