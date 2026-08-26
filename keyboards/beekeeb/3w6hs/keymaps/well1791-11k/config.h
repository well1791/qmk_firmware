#pragma once

// Timing parity with kanata config.kbd (defvar block):
//   chord_timeout 35 / hold_timeout 150 / one_shot_timeout 500 / caps-word 1500
#undef COMBO_TERM // keyboard-level config.h defines 75; kanata chord_timeout is 35
#define COMBO_TERM 35 // overrides keyboard-level 75 (keyboards/beekeeb/3w6hs/config.h)
#define TAPPING_TERM 150
#define ONESHOT_TIMEOUT 500
#define CAPS_WORD_IDLE_TIMEOUT 1500
