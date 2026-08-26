# Kanata → QMK 3W6HS Port Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Port all shortcut/layer behavior from the kanata config (`~/.config/kanata/`) into the QMK keymap `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/`, using kanata as the source of truth for every non-letter assignment.

**Architecture:** The QMK keymap is modular: `keymap.c` textually includes each `_<module>.def` three times, gated on `#define KMB_COMBO_ARRAYS` (combo key arrays), `KMB_COMBO_ENTRIES` (`key_combos[]` initializers), and `KMB_LAYER` (`keymaps[][]` initializers). Position macros live in `keycodes.h`. This plan adds three modules (`_chars.def`, `_mods.def`, keymap-level `config.h`) and rewrites the shortcut assignments in the existing modules to match kanata position-for-position.

**Tech Stack:** QMK firmware (C, RP2040), kanata config (reference only, read-only).

**Spec:** This document is self-contained. The design was approved in session on 2026-08-19 with these decisions: (1) port `_mods` as unreachable parity layer, (2) port qwerty toggle in **both** directions, (3) port the chars/compose layer, (4) map kanata's caps-as-esc/shift onto the left-inner thumb key.

## Global Constraints

- **kanata is the source of truth** for shortcuts, layer contents, and timing. Read-only: never edit anything under `~/.config/kanata/`.
- **The 11k alpha letters and letter-combo shapes stay exactly as they are.** Only shortcut-layer contents and shortcut chords change.
- **QMK combos are keycode-global, not layer-scoped.** A combo registered on `{KC_Z, X}` fires on any layer where both keycodes are held. This is why the qwerty layer gets namespaced `QW_*` keycodes (Task 7) — plain `KC_G`+`KC_U` in qwerty would trigger the alpha `C` chord. Never place a bare alpha-combo member keycode in another layer without checking the combo tables.
- **Validation = compile.** No test infrastructure exists for this keymap. After every task: `qmk compile -kb beekeeb/3w6hs -km well1791-11k` must succeed with zero errors (warnings about USB/size are pre-existing). Behavioral testing happens once, by the user, via flash (Task 10).
- **Commits:** user's rule is commit-only-when-requested. If executing without explicit commit authorization, skip the commit steps. Message style when committing: `[well1791] 11k: <description>` (matches repo history).
- **Do not modify** `keyboards/beekeeb/3w6hs/keyboard.json`, `rules.mk`, or any file outside `keymaps/well1791-11k/`.
- Working branch: `well1791/3w6hs` in `/mnt/storage/Code/qmk_firmware`. The keymap dir currently has uncommitted work-in-progress (the `.def` split) — build on top of it.

## Reference: position naming crosswalk

kanata chord tokens encode position; QMK macros encode position differently. Both sides of the split reuse the same keycodes (mirrored).

| Position | kanata token | QMK macro (alpha) | QMK macro (numsym) | Physical key (alpha layer) |
|---|---|---|---|---|
| top pinky | `ch_tpl`/`ch_tpr` | `AL_TP` | `NS_TP` | H (L) / H (R) |
| top ring | `ch_trl`/`ch_trr` | `AL_TR` | `NS_TR` | O |
| top middle | `ch_tml`/`ch_tmr` | `AL_TM` | `NS_TM` | U |
| top index | `ch_til`/`ch_tir` | `AL_TI` | `NS_TI` | G |
| side index (inner) | `ch_sil`/`ch_sir` | `AL_SI` | `NS_SI` | g / h position |
| home pinky | `ch_hpl`/`ch_hpr` | `AL_HPL`/`AL_HPR` (LT keys) | `NS_HPL`/`NS_HPR` (LT keys) | M / ' |
| home ring | `ch_hrl`/`ch_hrr` | `AL_HR` | `NS_HR` | A |
| home middle | `ch_hml`/`ch_hmr` | `AL_HM` | `NS_HM` | I |
| home index | `ch_hil`/`ch_hir` | `AL_HI` | `NS_HI` | E |
| bottom index | `ch_bil`/`ch_bir` | `AL_BI` | `NS_BI` | J |
| bottom middle | `ch_bml`/`ch_bmr` | `AL_BM` | `NS_BM` | K |

Nav layers use `NA_MV_*` (movement) and `NA_MD_*` (modifiers); funct layer uses plain `KC_F*`; mods/chars/media/go use direct keycodes. In nav/funct layers the finger letters follow the same i/m/r/p scheme (`NA_MV_TI` = top-index, etc.).

**LAYOUT argument order** (`LAYOUT_split_3x5_3`, 4 rows): row 1 = top: `TP TR TM TI SI || SI TI TM TR TP`; row 2 = home: `HPL HR HM HI SI || SI HI HM HR HPR`; row 3 = bottom: `__, __, BM, BI, __ || __, BI, BM, __, __`; row 4 = thumbs: left `outer, middle, inner || inner, middle, outer`.

## Reference: kanata timing → QMK config

| kanata (config.kbd defvar) | value | QMK define (keymap config.h) |
|---|---|---|
| `chord_timeout` | 35 | `COMBO_TERM 35` |
| `hold_timeout` | 150 | `TAPPING_TERM 150` |
| `one_shot_timeout` | 500 | `ONESHOT_TIMEOUT 500` |
| caps-word duration (1500 in `os_cwc`) | 1500 | `CAPS_WORD_IDLE_TIMEOUT 1500` |

---

### Task 1: Timing config + caps-word parity

**Files:**
- Create: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/config.h`
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/keymap.c` (add `caps_word_press_user`)

**Interfaces:**
- Consumes: nothing new. `CAPS_WORD_ENABLE = yes` already in `rules.mk`; `CW_TOGG` combo (`al_hi_hm_tr`) already wired in `_alpha.def`.
- Produces: `config.h` with timing defines; `caps_word_press_user()` in keymap.c. Later tasks rely on nothing from here except compile health.

kanata's `os_cwc` continues caps-word on: letters, digits, backspace, delete, arrows, `-`. Everything else (including space) ends it. QMK's `caps_word_press_user` returns true for keys that should not terminate caps-word.

- [ ] **Step 1: Create keymap config.h**

```c
// keymaps/well1791-11k/config.h
#pragma once

// Timing parity with kanata config.kbd (defvar block):
//   chord_timeout 35 / hold_timeout 150 / one_shot_timeout 500 / caps-word 1500
#define COMBO_TERM 35
#define TAPPING_TERM 150
#define ONESHOT_TIMEOUT 500
#define CAPS_WORD_IDLE_TIMEOUT 1500
```

- [ ] **Step 2: Add caps_word_press_user to keymap.c**

Add after the `process_record_user` function (before `keymaps[][]`):

```c
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
```

- [ ] **Step 3: Compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success.

- [ ] **Step 4: Commit (if authorized)**

`[well1791] 11k: add timing config and caps-word parity with kanata`

---

### Task 2: Funct layer — F11/F12 position fix

**Files:**
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_funct.def` (pass 3 block only)

**Interfaces:**
- Consumes: nothing.
- Produces: corrected `_FUNCT` layer. Nothing downstream depends on it.

kanata `_ff.kbd`: `ff_tp` = F12 (top pinky), `ff_hp` = F11 (home pinky). Current QMK has them swapped (`KC_F11` top, `KC_F12` home). The F1–F10 assignments already match kanata and stay.

- [ ] **Step 1: Swap F11/F12 in both halves**

Replace the `[_FUNCT]` layer block with:

```c
    [_FUNCT] = LAYOUT_split_3x5_3(
             KC_F12,  KC_F10,   KC_F8,   KC_F6, _______, /*||*/ _______,   KC_F6,   KC_F8,  KC_F10,  KC_F12,
             KC_F11,   KC_F5,   KC_F3,   KC_F1, _______, /*||*/ _______,   KC_F1,   KC_F3,   KC_F5,  KC_F11,
            _______, _______, _______, _______, _______, /*||*/ _______, _______, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),
```

Also update the module header comment: `Contains : layer [_FUNCT] (F12 top pinky / F11 home pinky, per kanata _ff.kbd)`.

- [ ] **Step 2: Compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success.

- [ ] **Step 3: Commit (if authorized)**

`[well1791] 11k: fix F11/F12 positions to match kanata`

---

### Task 3: Nav layers — copy/paste/undo/pgup/pgdn + enter tap-hold

**Files:**
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/keycodes.h` (`NA_MV_HP`)
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_nav.def` (pass 3 blocks)

**Interfaces:**
- Consumes: nothing.
- Produces: `NA_MV_HP` = `LSFT_T(KC_ENT)` (used in both nav layers). Nothing else references these positions.

kanata `_nav.kbd` keys missing from QMK today: `undo` (C-z) at the undo positions, `cpy` (C-c) / `pst` (C-v) at bottom c/v positions, plain `pgup`/`pgdn` at bottom m/, positions, and `na_entr` (tap enter / hold shift) at pinky-home. All nav **combos** (home/end/del/esc/space) already match kanata — do not touch `na_*` arrays or entries.

- [ ] **Step 1: keycodes.h — enter becomes tap-hold**

Replace:
```c
#define NA_MV_HP KC_ENT
```
with:
```c
#define NA_MV_HP LSFT_T(KC_ENT)  // kanata na_entr: tap enter, hold shift
```

- [ ] **Step 2: _nav.def — add the missing keys**

Replace the `[_NAV_L]` layer block with:

```c
    [_NAV_L] = LAYOUT_split_3x5_3(
        NA_MV_TP, NA_MV_TR, NA_MV_TM, NA_MV_TI, _______, /*||*/ _______, NA_MD_TI, NA_MD_TM, NA_MD_TR, TO(_NAV_R),
        NA_MV_HP, NA_MV_LT, NA_MV_HM, NA_MV_RT, LCTL(KC_Z), /*||*/ _______, NA_MD_HI, NA_MD_HM, NA_MD_HR, NA_MD_HP,
        _______, _______, KC_PGDN, KC_PGUP, _______, /*||*/ LCTL(KC_V), LCTL(KC_C), _______, _______, _______,
                            _______, _______, _______, /*||*/ _______, _______, _______
    ),
```

Replace the `[_NAV_R]` layer block with:

```c
    [_NAV_R] = LAYOUT_split_3x5_3(
      TO(_NAV_L), NA_MD_TR, NA_MD_TM, NA_MD_TI, _______, /*||*/ _______, NA_MV_TI, NA_MV_TM, NA_MV_TR, NA_MV_TP,
        NA_MD_HP, NA_MD_HR, NA_MD_HM, NA_MD_HI, _______, /*||*/ LCTL(KC_Z), NA_MV_LT, NA_MV_HM, NA_MV_RT, NA_MV_HP,
         _______, _______, LCTL(KC_C), LCTL(KC_V), _______, /*||*/ KC_PGUP, KC_PGDN, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),
```

Position check against kanata: NAV_R `undo` at h-position (right home col 1), `cpy`/`pst` at left bottom c/v, `pgup`/`pgdn` at right bottom m/,. NAV_L mirrored: `undo` at g-position (left home col 5), `pgdn`/`pgup` at left bottom c/v, `pst`/`cpy` at right bottom m/,. Exactly the kanata `_nav.kbd` arrangement.

Update the `_nav.def` header `Contains:` comment to mention cpy/pst/undo/pgup/pgdn.

- [ ] **Step 3: Compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success.

- [ ] **Step 4: Commit (if authorized)**

`[well1791] 11k: add cpy/pst/undo/pgup/pgdn and enter tap-hold to nav layers`

---

### Task 4: GO layer — builtin shortcuts, A-1/A-9 fix, M-A-i

**Files:**
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_go.def` (pass 3 block only)
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/keymap.c` (delete custom enum + `process_record_user` body)

**Interfaces:**
- Consumes: nothing.
- Produces: `_GO` layer using only built-in quantum keycodes. The `CTL_TAB`…`ALT_GRV` enum and their `process_record_user` cases are deleted in this task — make sure no other file references them (only `_go.def` does).

Two bugs vs kanata fixed here: (a) kanata `go_tp` = Alt+1 (top pinky) and `go_hp` = Alt+9 (home pinky) — QMK currently has them swapped; (b) kanata `go_si` = M-A-i at the side-index (g/h) position — missing in QMK.

- [ ] **Step 1: Rewrite _go.def layer**

Replace the `[_GO]` layer block with:

```c
    [_GO] = LAYOUT_split_3x5_3(
     LALT(KC_1), LALT(KC_GRV), LCTL(KC_PGUP), LCTL(LSFT(KC_T)), LAG(KC_I), /*||*/ LAG(KC_I), LCTL(LSFT(KC_T)), LCTL(KC_PGUP), LALT(KC_GRV), LALT(KC_1),
     LALT(KC_9), LCTL(KC_TAB), LCTL(KC_PGDN),          LCTL(KC_W), _______, /*||*/ _______,          LCTL(KC_W), LCTL(KC_PGDN), LCTL(KC_TAB), LALT(KC_9),
      _______,    _______,     _______,       _______,   _______, /*||*/ _______,    _______,     _______,       _______,    _______,
                                  _______,    _______,   _______, /*||*/ _______,    _______,   _______
    ),
```

Mapping (per kanata `_go.kbd`): ti = reopen-tab C-S-t, tm = C-pgup, tr = A-grv, tp = A-1, hi = C-w, hm = C-pgdn, hr = C-tab, hp = A-9, si = M-A-i (`LAG(KC_I)`).

Update the module header: remove the "Needs custom keycodes" note; state `Needs : nothing (built-in quantum keycodes only)`.

- [ ] **Step 2: keymap.c — remove the custom keycode machinery**

Delete the entire `enum custom_keycodes { ... };` block (`CTL_TAB` through `ALT_GRV`) and the entire `process_record_user` function. (Task 5 reintroduces a new, smaller `process_record_user`.)

- [ ] **Step 3: Compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success. If it errors on `process_record_user` being referenced — it isn't referenced anywhere, deletion is safe; errors mean a stray reference remains, find and remove it.

- [ ] **Step 4: Commit (if authorized)**

`[well1791] 11k: go layer parity — builtin shortcuts, alt-1/9 fix, M-A-i`

---

### Task 5: Chars layer — compose-key accents

**Files:**
- Create: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_chars.def`
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/keycodes.h` (add `CHR_*` enum)
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/keymap.c` (layer enum `_CHARS`, include, new `process_record_user`)
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_alpha.def` (wire dormant `al_bm_hr` array)

**Interfaces:**
- Consumes: dormant combo array `al_bm_hr[]` already defined in `_alpha.def` pass 1 (currently has no entry).
- Produces: layer `_CHARS`; keycodes `CHR_A, CHR_E, CHR_I, CHR_O, CHR_U, CHR_N, CHR_D`; `compose_accent()` helper + `process_record_user` in keymap.c. Task 6/7 append cases to this same `process_record_user`.

kanata `_alpha.kbd` chord `ch_bml + ch_hrl` (bottom-middle + home-ring = K + A keycodes in QMK) one-shots `L_CHARS`, which sends RALT-tap + mark + letter (host compose). Requires the host OS to have compose on RALT — same dependency as kanata, note it in the module header.

- [ ] **Step 1: keycodes.h — add the chars enum**

Add at the end of keycodes.h:

```c
// ===== CHR_ - Compose accents (chars layer) =====
enum custom_keycodes {
    CHR_A = SAFE_RANGE, // á
    CHR_E,              // é
    CHR_I,              // í
    CHR_O,              // ó
    CHR_U,              // ú
    CHR_N,              // ñ
    CHR_D,              // ü (kanata used the 'd' key for diaeresis)
};
```

- [ ] **Step 2: Create _chars.def**

```c
// ==============================================================
// Chars module  —  included by keymap.c (layer only)
// ==============================================================
// Contains : layer [_CHARS] — accented chars via host compose
//            (RALT tap + mark + letter; needs compose-on-RALT
//            on the host OS, same as kanata L_CHARS)
// Reached  : OSL(_CHARS) from the alpha K+A combo (al_bm_hr)
// Needs    : keycodes.h (CHR_*)
// ==============================================================
#if defined(KMB_LAYER)
    [_CHARS] = LAYOUT_split_3x5_3(
            _______, _______,   CHR_E, _______, _______, /*||*/ _______,   CHR_U,   CHR_I,   CHR_O, _______,
              CHR_A, _______,   CHR_D, _______, _______, /*||*/ _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, /*||*/ _______,   CHR_N, _______, _______, _______,
                              _______, _______, _______, /*||*/ _______, _______, _______
    ),
#endif
```

Position check vs kanata `L_CHARS` (bound keys a e i o u n d): CHR_A at left home-pinky (a key), CHR_E at left top-middle (e), CHR_I at right top-middle (i), CHR_O at right top-ring (o), CHR_U at right top-index (u), CHR_N at right bottom-index (m key — kanata binds `n` there), CHR_D at left home-middle (d). All other positions transparent → fall through to alpha, matching kanata.

- [ ] **Step 3: keymap.c — wire the module**

1. Add `_CHARS,` to the layer enum, after `_QWERTY`.
2. Add `#include "_chars.def"` in pass 3, after `#include "_go.def"`.
3. Reintroduce `process_record_user` (Task 4 deleted it) above `keymaps[][]`:

```c
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
```

- [ ] **Step 4: _alpha.def — wire the dormant array**

In the pass 2 entries block, add next to the other `al_bm_hr`-family entries:

```c
    COMBO(al_bm_hr, OSL(_CHARS)),
```

- [ ] **Step 5: Compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success.

- [ ] **Step 6: Commit (if authorized)**

`[well1791] 11k: add chars layer with compose accents (kanata L_CHARS)`

---

### Task 6: Alpha chords — MEH + thumb esc/shift

**Files:**
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_alpha.def` (one entry, one layer cell)

**Interfaces:**
- Consumes: dormant combo array `al_bi_bm_hr[]` (defined in pass 1, no entry).
- Produces: MEH one-shot combo and the thumb tap-hold. Nothing downstream.

- [ ] **Step 1: Wire MEH**

In `_alpha.def` pass 2 entries, add:

```c
    COMBO(al_bi_bm_hr, OSM(MOD_MEH)),
```

(J + K + A keycodes = kanata `ch_bil ch_bml ch_hrl` → `os_meh`.)

- [ ] **Step 2: Left-inner thumb = tap esc / hold shift**

In `_alpha.def` pass 3, change the thumb row from:

```c
                              _______, _______, _______, /*||*/ _______, _______, _______
```
to:
```c
                              _______, _______, LSFT_T(KC_ESC), /*||*/ _______, _______, _______
```

This is kanata's `esc_sft` (caps position) moved to the most-reachable thumb. Update the module header `Needs/Provides` comment to mention the thumb.

- [ ] **Step 3: Compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success.

- [ ] **Step 4: Commit (if authorized)**

`[well1791] 11k: wire meh chord and thumb esc/shift`

---

### Task 7: Qwerty round-trip (namespaced letters + g/h toggle both ways)

**Files:**
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/keycodes.h` (extend enum: `AL_SIR`, `QW_A…QW_Z`)
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_alpha.def` (new array + entry + layer cell)
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_qwerty.def` (full rewrite)
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/keymap.c` (include `_qwerty.def` in passes 1 & 2; add `process_record_user` cases)

**Interfaces:**
- Consumes: `enum custom_keycodes` created in Task 5 (append to it).
- Produces: `AL_SIR` keycode (right side-index; taps Z); `QW_A…QW_Z` contiguous range. Later tasks depend on nothing here.

**Why the namespace:** QMK combos match keycodes globally. The alpha layer's letter combos are on plain keycodes (`AL_TI` = `KC_G`, etc.), so a qwerty layer built from plain `KC_*` letters would fire alpha chords while gaming. Namespaced `QW_*` keycodes that tap the plain letter sidestep every combo. `KC_SEMICOLON`, `KC_COMMA`, `KC_DOT`, `KC_SLASH` are safe un-namespaced (no combo uses them as members — verified against the final combo tables of Tasks 5–8).

Both side-index keys currently emit the same keycode (`AL_SI` = `KC_Z` on g AND h positions). A combo can't pair a keycode with itself, so the right side becomes `AL_SIR` (custom, taps Z). Known tradeoff: `AL_SIR` tap uses `tap_code` — no autorepeat on hold; acceptable for the h position.

- [ ] **Step 1: keycodes.h — extend the enum**

Inside the existing `enum custom_keycodes` (after `CHR_D`), append:

```c
    // Right side-index (h position): same tap as AL_SI but a distinct
    // keycode so the g+h alpha<->qwerty combo can pair them.
    AL_SIR,
    // Namespaced qwerty letters: distinct keycodes so alpha combos
    // (plain KC_*) can't fire inside the gaming layer.
    QW_A, QW_B, QW_C, QW_D, QW_E, QW_F, QW_G, QW_H, QW_I, QW_J, QW_K, QW_L, QW_M,
    QW_N, QW_O, QW_P, QW_Q, QW_R, QW_S, QW_T, QW_U, QW_V, QW_W, QW_X, QW_Y, QW_Z,
```

- [ ] **Step 2: _alpha.def — toggle combo + right side-index**

Pass 1 (with the other 2-key arrays):

```c
//                     | | | | |       | | | | |
//                     | | | | |       | | | | |
//                     |*| | | |       | | | |*|   (g + h)
const uint16_t PROGMEM al_si_sir[] = {AL_SI, AL_SIR, COMBO_END};
```

Pass 2 entries:

```c
    COMBO(al_si_sir, TO(_QWERTY)),
```

Pass 3 layer: right half home row currently reads `AL_SI, AL_HI, ...` — change the right `AL_SI` to `AL_SIR`:

```c
             AL_HPL,   AL_HR,   AL_HM,   AL_HI,   AL_SI, /*||*/   AL_SIR,  AL_HI,   AL_HM,   AL_HR,  AL_HPR,
```

- [ ] **Step 3: Rewrite _qwerty.def**

```c
// ==============================================================
// Qwerty module  —  included 3x by keymap.c (arrays / entries / layer)
// ==============================================================
// Contains : layer [_QWERTY] (plain gaming layout, no chords)
//            + g+h combo back to alpha
// Letters are namespaced QW_* keycodes (tap the plain letter) so
// alpha-layer combos never fire here. ; , . / are safe bare.
// ==============================================================
#if defined(KMB_COMBO_ARRAYS)
const uint16_t PROGMEM qw_gh[] = {QW_G, QW_H, COMBO_END};

#elif defined(KMB_COMBO_ENTRIES)
    COMBO(qw_gh, TO(_ALPHA)),

#elif defined(KMB_LAYER)
    [_QWERTY] = LAYOUT_split_3x5_3(
                     QW_Q, QW_W, QW_E, QW_R,    QW_T, /*||*/    QW_Y, QW_U,     QW_I,   QW_O,          QW_P,
                     QW_A, QW_S, QW_D, QW_F,    QW_G, /*||*/    QW_H, QW_J,     QW_K,   QW_L, KC_SEMICOLON,
                     QW_Z, QW_X, QW_C, QW_V,    QW_B, /*||*/    QW_N, QW_M, KC_COMMA, KC_DOT,     KC_SLASH,
                                        _______, _______, _______, /*||*/ _______, _______, _______
    ),
#endif
```

- [ ] **Step 4: keymap.c — include passes + process cases**

1. Add `#include "_qwerty.def"` to pass 1 (after `_nav.def`) and pass 2 (after `_nav.def`). It already exists in pass 3 — remove the duplicate if you move it; final pass-3 order: `_alpha, _numsym, _funct, _nav, _media, _go, _chars, _mouse, _qwerty` and `_mods` (Task 9).
2. Add cases at the top of the `process_record_user` switch:

```c
        case QW_A ... QW_Z:
            if (record->event.pressed) tap_code16(KC_A + (keycode - QW_A));
            return false;
        case AL_SIR:
            if (record->event.pressed) tap_code(KC_Z);
            return false;
```

- [ ] **Step 5: Compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success.

- [ ] **Step 6: Commit (if authorized)**

`[well1791] 11k: qwerty round-trip via g+h, namespaced gaming letters`

---

### Task 8: Numsym full remap (kanata as base)

**Files:**
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/keycodes.h` (NS_* singles)
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_numsym.def` (arrays + entries)

**Interfaces:**
- Consumes: `NS_HPL`/`NS_HPR` stay `LT(_NAV_R/L, KC_QUOTE)` (QMK-only nav feature — keep).
- Produces: final NS combo table. Nothing downstream.

This is the largest task. The full truth table (shape = combo member positions; both halves share keycodes so each entry serves left and right):

| Shape | kanata output | Current QMK | Action |
|---|---|---|---|
| **singles** | | | |
| TP | ` ` `` ` `` | `*` | `NS_TP` → `KC_GRAVE` |
| SI | `~` | `@` | `NS_SI` → `KC_TILDE` |
| BI | `?` | `=` | `NS_BI` → `KC_QUESTION` |
| BM | `,` | `+` | `NS_BM` → `KC_COMMA` |
| HP (tap) | `'` | `'` via LT | keep |
| HI/HM/HR/TI/TM/TR | `1 3 5 6 8 0` | same | keep |
| **pairs** | | | |
| hi+hm / hm+hr / ti+tm / tm+tr | `2 4 7 9` | same | keep |
| hi+hr | `<` | `(` | → `KC_LABK` |
| ti+tr | `>` | `)` | → `KC_RABK` |
| hi+tr | `(` | `/` | → `KC_LPRN` |
| ti+hr | `)` | `\` | → `KC_RPRN` |
| hi+hpl/hpr | `[` | `[` | keep |
| ti+tp | `]` | `]` | keep |
| hi+tp | `{` | `-` | → `KC_LCBR` |
| ti+hpl/hpr | `}` | `_` | → `KC_RCBR` |
| hi+tm | `/` | `.` | → `KC_SLASH` |
| tm+hr | `.` | `,` | → `KC_DOT` |
| hm+tr | `_` | *(dormant array)* | add entry `KC_UNDERSCORE` |
| bi+hm | `"` | `{` | → `KC_DQT` |
| bi+hr | `-` | `<` | → `KC_MINUS` |
| bi+hpl/hpr | `*` | `>` | → `KC_ASTERISK` |
| hr+hpl/hpr | `\` | `"` | → `KC_BACKSLASH` |
| si+tr | `+` | — | **new array** → `KC_PLUS` |
| si+hr | `!` | — | **new array** → `KC_EXLM` |
| si+hpl / si+hpr | `@` | — | **2 new arrays** → `KC_AT` |
| bm+hr | `=` | `}` | → `KC_EQUAL` |
| **triples** | | | |
| hi+hm+hr (home-3) | `space` | `?` | → `KC_SPACE` |
| hi+tm+hr / hi+tm+tr / hi+hm+tr / ti+tm+hr | `; : & \|` | same | keep |
| bi+hm+hr | `$` | — | **new array** → `KC_DOLLAR` |
| bi+bm+hr | `%` | `$` | → `KC_PERCENT` |
| bm+bi | `#` | `#` | keep |
| tp+tr | `^` | `%` | → `KC_CIRCUMFLEX` |
| ti+tm+tr | *(kanata: tbd)* | `!` | **remove** entry+array |
| hm+hr+hpl / hm+hr+hpr | *(none in kanata)* | `` ` `` | **remove** entries+arrays |
| tm+tr+tp | *(none in kanata)* | `~` | **remove** entry+array |
| ti+hm | *(none in kanata)* | *(dormant)* | **remove** dormant array |

Caveat to note in the module header: `si+hpl/hpr` combos have `LT()` members; holding the pinky may add combo-term latency to its tap action — same behavior class as the existing `hi+hpl` `[` combos, which already work this way.

- [ ] **Step 1: keycodes.h — new singles**

Replace the NS block with:

```c
// ===== NS_ - Numbers and Symbols =====
#define NS_SI KC_TILDE
#define NS_HI KC_1
#define NS_HM KC_3
#define NS_HR KC_5
#define NS_HPL LT(_NAV_R, KC_QUOTE)
#define NS_HPR LT(_NAV_L, KC_QUOTE)
#define NS_TI KC_6
#define NS_TM KC_8
#define NS_TR KC_0
#define NS_TP KC_GRAVE
#define NS_BI KC_QUESTION
#define NS_BM KC_COMMA
```

- [ ] **Step 2: _numsym.def — adjust pass 1 arrays**

Add these arrays (place with the other pair arrays; keep the ASCII-art comment style):

```c
//                     | | | | |    | | | | |
//                     | | | | |    | | | | |
//                     |*| | | |    | | | |*|
const uint16_t PROGMEM ns_si_tr[] = {NS_SI, NS_TR, COMBO_END};
const uint16_t PROGMEM ns_si_hr[] = {NS_SI, NS_HR, COMBO_END};
//                     |*| | | |    | | | |*|
//                     |*| | | |    | | | |*|
const uint16_t PROGMEM ns_si_hpl[] = {NS_SI, NS_HPL, COMBO_END};
const uint16_t PROGMEM ns_si_hpr[] = {NS_SI, NS_HPR, COMBO_END};
//                     | | | | |       | | | | |
//                     | | | |*|       |*| | | |
//                         |*|         |*|
const uint16_t PROGMEM ns_bi_hm_hr[] = {NS_BI, NS_HM, NS_HR, COMBO_END};
```

Delete these now-unused arrays: `ns_ti_tm_tr`, `ns_hm_hr_hpl`, `ns_hm_hr_hpr`, `ns_tm_tr_tp`, `ns_ti_hm`.

- [ ] **Step 3: _numsym.def — replace the entire pass 2 entries block**

```c
    // ===========================================================
    // ==================  Nums N Syms  ==========================
    // ===========================================================
    // digits
    COMBO(ns_hi_hm, KC_2),
    COMBO(ns_hm_hr, KC_4),
    COMBO(ns_ti_tm, KC_7),
    COMBO(ns_tm_tr, KC_9),
    COMBO(ns_hi_hm_hr, KC_SPACE),
    // pairs <>
    COMBO(ns_hi_hr, KC_LABK),
    COMBO(ns_ti_tr, KC_RABK),
    // pairs ()
    COMBO(ns_hi_tr, KC_LPRN),
    COMBO(ns_ti_hr, KC_RPRN),
    // pairs []
    COMBO(ns_hi_hpl, KC_LBRC),
    COMBO(ns_hi_hpr, KC_LBRC),
    COMBO(ns_ti_tp, KC_RBRC),
    // pairs {}
    COMBO(ns_hi_tp, KC_LCBR),
    COMBO(ns_ti_hpl, KC_RCBR),
    COMBO(ns_ti_hpr, KC_RCBR),
    // symbols
    COMBO(ns_hi_tm, KC_SLASH),
    COMBO(ns_tm_hr, KC_DOT),
    COMBO(ns_hm_tr, KC_UNDERSCORE),
    COMBO(ns_bi_hm, KC_DQT),
    COMBO(ns_bi_hr, KC_MINUS),
    COMBO(ns_bi_hpl, KC_ASTERISK),
    COMBO(ns_bi_hpr, KC_ASTERISK),
    COMBO(ns_hr_hpl, KC_BACKSLASH),
    COMBO(ns_si_tr, KC_PLUS),
    COMBO(ns_si_hr, KC_EXLM),
    COMBO(ns_si_hpl, KC_AT),
    COMBO(ns_si_hpr, KC_AT),
    COMBO(ns_bm_hr, KC_EQUAL),
    // triples
    COMBO(ns_hi_tm_hr, KC_SEMICOLON),
    COMBO(ns_hi_tm_tr, KC_COLON),
    COMBO(ns_hi_hm_tr, KC_AMPERSAND),
    COMBO(ns_ti_tm_hr, KC_PIPE),
    COMBO(ns_bi_hm_hr, KC_DOLLAR),
    COMBO(ns_bi_bm_hr, KC_PERCENT),
    COMBO(ns_bi_bm, KC_HASH),
    COMBO(ns_tr_tp, KC_CIRCUMFLEX),
```

- [ ] **Step 4: Compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success. A "duplicate combo" warning means two entries share an identical member set — recheck the table; every shape above is distinct.

- [ ] **Step 5: Commit (if authorized)**

`[well1791] 11k: numsym remap to kanata assignments`

---

### Task 9: Mods parity module (unreachable, like kanata)

**Files:**
- Create: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/_mods.def`
- Modify: `keyboards/beekeeb/3w6hs/keymaps/well1791-11k/keymap.c` (layer enum `_MODS`, includes)

**Interfaces:**
- Consumes: nothing.
- Produces: `_MODS` layer + its combo arrays/entries. **Unreachable by design** — kanata's `_mods.kbd` is itself WIP/unreachable (its `os_mods` alias is defined in config.kbd but referenced by no chord). Port for structural parity only; the combos are inert because no reachable layer emits their member keycodes.

- [ ] **Step 1: Create _mods.def**

```c
// ==============================================================
// Mods module  —  included 3x by keymap.c (arrays / entries / layer)
// ==============================================================
// Contains : layer [_MODS] + one-shot combo-mod chords.
// PARITY-ONLY / UNREACHABLE: kanata's _mods.kbd is WIP and its
// trigger (os_mods) is wired to no chord there either. Do not
// reference _MODS from any reachable layer without adding a
// trigger chord on the kanata side first.
// Positions mirror kanata L_MODS: ti=GUI tm=TAB tr=ALT (top),
// hi=SFT hm=ESC hr=CTL (home).
// ==============================================================
#if defined(KMB_COMBO_ARRAYS)
const uint16_t PROGMEM md_ti_tr[]    = {OSM(MOD_LGUI), OSM(MOD_LALT), COMBO_END};
const uint16_t PROGMEM md_hi_hr[]    = {OSM(MOD_LSFT), OSM(MOD_LCTL), COMBO_END};
const uint16_t PROGMEM md_hi_tr[]    = {OSM(MOD_LSFT), OSM(MOD_LALT), COMBO_END};
const uint16_t PROGMEM md_ti_hr[]    = {OSM(MOD_LGUI), OSM(MOD_LCTL), COMBO_END};
const uint16_t PROGMEM md_hi_hm_hr[] = {OSM(MOD_LSFT), KC_ESC, OSM(MOD_LCTL), COMBO_END};

#elif defined(KMB_COMBO_ENTRIES)
    COMBO(md_ti_tr, OSM(MOD_LGUI | MOD_LALT)),  // sup+alt
    COMBO(md_hi_hr, OSM(MOD_LCTL | MOD_LSFT)),  // ctl+sft
    COMBO(md_hi_tr, OSM(MOD_LALT | MOD_LSFT)),  // alt+sft
    COMBO(md_ti_hr, OSM(MOD_LGUI | MOD_LCTL)),  // sup+ctl
    COMBO(md_hi_hm_hr, OSM(MOD_MEH)),           // meh

#elif defined(KMB_LAYER)
    [_MODS] = LAYOUT_split_3x5_3(
            _______, OSM(MOD_LALT),   KC_TAB, OSM(MOD_LGUI), _______, /*||*/ _______, OSM(MOD_LGUI),   KC_TAB, OSM(MOD_LALT), _______,
            _______, OSM(MOD_LCTL),   KC_ESC, OSM(MOD_LSFT), _______, /*||*/ _______, OSM(MOD_LSFT),   KC_ESC, OSM(MOD_LCTL), _______,
            _______,    _______,     _______,    _______,     _______, /*||*/ _______,    _______,     _______,    _______,     _______,
                                _______,      _______,      _______, /*||*/ _______,      _______,      _______
    ),
#endif
```

- [ ] **Step 2: keymap.c — wire it**

1. Add `_MODS,` to the layer enum after `_CHARS`.
2. Add `#include "_mods.def"` to pass 1 and pass 2 (after `_qwerty.def`), and to pass 3 (after `_qwerty.def`).

- [ ] **Step 3: Compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success.

- [ ] **Step 4: Commit (if authorized)**

`[well1791] 11k: add mods parity module (unreachable, matches kanata WIP)`

---

### Task 10: Final audit + optional flash

**Files:** none created; verification only.

- [ ] **Step 1: Clean compile**

Run: `qmk compile -kb beekeeb/3w6hs -km well1791-11k`
Expected: success, no duplicate-combo warnings.

- [ ] **Step 2.5: _media.def — doc note for the one kanata chord that can't port**

The media layer already matches kanata's positions. Add one line under the module header comment:

```c
// Note: kanata's me_si "systemctl restart kanata" chord is a host command
// and cannot run from firmware; QK_BOOT occupies the left SI position instead.
```

- [ ] **Step 3: Cross-layer combo audit**

Verify each of these holds (grep the `.def` files):

1. `QW_*` keycodes appear only in `_qwerty.def` (layer + `qw_gh` array) and `keymap.c` (enum + process case).
2. `AL_SIR` appears only in `keycodes.h`, `_alpha.def` (array/entry/layer), `keymap.c` (process case).
3. `CHR_*` appear only in `keycodes.h`, `_chars.def`, `keymap.c`.
4. The deleted customs (`CTL_TAB`, `CTL_SFT_T`, `ALT_1`, `ALT_9`, `CTL_W`, `CTL_PGUP`, `CTL_PGDN`, `ALT_GRV`) appear nowhere.
5. No two entries in any pass-2 block share the same member set (QMK would warn).
6. Removed numsym arrays (`ns_ti_tm_tr`, `ns_hm_hr_hpl`, `ns_hm_hr_hpr`, `ns_tm_tr_tp`, `ns_ti_hm`) appear nowhere.

- [ ] **Step 4: Behavior parity checklist for on-hardware testing (user)**

After flashing, spot-check: g+h toggles qwerty and back; K+A one-shots chars (á é ñ ü); J+K+A one-shots MEH; numsym: home-3 = space, `~` singles at TP/SI, hi+hr = `<`, si+hr = `!`, tp+tr = `^`; nav: m/, = pgup/pgdn (R) and pst/cpy (L), c/v = cpy/pst (R-side nav) and pgdn/pgup (L), h/g pos = undo, pinky-home tap enter/hold shift; funct: top pinky = F12, home pinky = F11; go: top pinky = A-1, home pinky = A-9, g/h = M-A-i; caps-word survives digits/arrows/`-` and dies on space; thumb inner-left = esc/shift.

- [ ] **Step 5: Flash (ONLY with explicit user confirmation — writes hardware)**

Run: `qmk flash -kb beekeeb/3w6hs -km well1791-11k`
Expected: device reboots into new keymap.

---

## Out of scope (do not do)

- Media `systemctl restart kanata` chord — host command, impossible in firmware. `_media.def` stays as-is (it already matches kanata's volume/brightness/playback positions; `QK_BOOT` on the left SI position is a deliberate QMK-only addition).
- Any trigger chord for `_MODS` — kanata hasn't wired one either.
- Editing anything under `~/.config/kanata/`.
- Renaming/reordering the existing layer enum values.
