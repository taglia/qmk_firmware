#include QMK_KEYBOARD_H
#include "xulkal.h"

#define EXPAND_LAYOUT(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty Layout
     * ,-----------------------------------------------------------------------------------.
     * | GESC |   1  |   2  |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   | BkSp |
     * |------+------+------+------+------+------|------+------+------+------+------+------+--------------------.
     * | Tab  |   Q  |   W  |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |   \  |  7   |  8   |  9   |
     * |------+------+------+------+------+------|------+------+------+------+------+------+------+------+------|
     * |FN(CAPS)| A  |   S  |   D  |  F   |  G   |  H   |  J   |  K   |  L   |  ;   | Enter|  4   |  5   |  6   |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * | Sft[ |   Z  |   X  |   C  |  V   |  B   |  N   |  M   |  ,   |  .   |  /   | Sft] |  1   |  2   |  3   |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctl- |  Win | LOWER| RAISE| Alt  | Space| Space| Left |  Up  | Down | Right| Ctl= |  0   |  .   |  =   |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------'
     */
    [_QWERTY] = EXPAND_LAYOUT( \
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,\
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_P7,   KC_P8,   KC_P9, \
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_P4,   KC_P5,   KC_P6, \
        _________________QWERTY_L4_________________, _________________QWERTY_R4_________________, KC_P1,   KC_P2,   KC_P3, \
        _________________QWERTY_L5_________________, _________________QWERTY_R5_________________, KC_P0,   KC_DOT,  KC_EQL \
    ),

#ifndef GAMELAYER_DISABLE
    [_GAME] = EXPAND_LAYOUT( \
        ___________________GAME_L1_________________, ___________________GAME_R1_________________, \
        ___________________GAME_L2_________________, ___________________GAME_R2_________________, _______, _______, _______, \
        ___________________GAME_L3_________________, ___________________GAME_R3_________________, _______, _______, _______, \
        ___________________GAME_L4_________________, ___________________GAME_R4_________________, _______, _______, _______, \
        ___________________GAME_L5_________________, ___________________GAME_R5_________________, _______, _______, _______ \
    ),
#endif

    [_LOWER] =  EXPAND_LAYOUT( \
        __________________LOWER_L1_________________, __________________LOWER_R1_________________, \
        __________________LOWER_L2_________________, __________________LOWER_R2_________________, _______, _______, _______, \
        __________________LOWER_L3_________________, __________________LOWER_R3_________________, _______, _______, _______, \
        __________________LOWER_L4_________________, __________________LOWER_R4_________________, _______, _______, _______, \
        __________________LOWER_L5_________________, __________________LOWER_R5_________________, _______, _______, _______ \
    ),

    [_RAISE] = EXPAND_LAYOUT( \
        __________________RAISE_L1_________________, __________________RAISE_R1_________________, \
        __________________RAISE_L2_________________, __________________RAISE_R2_________________, _______, _______, _______, \
        __________________RAISE_L3_________________, __________________RAISE_R3_________________, _______, _______, _______, \
        __________________RAISE_L4_________________, __________________RAISE_R4_________________, _______, _______, _______, \
        __________________RAISE_L5_________________, __________________RAISE_R5_________________, _______, _______, _______ \
    ),

#ifdef TRILAYER_ENABLED
    [_ADJUST] = EXPAND_LAYOUT( \
        _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, \
        _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, _______, _______, _______, \
        _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, _______, _______, _______, \
        _________________ADJUST_L4_________________, _________________ADJUST_R4_________________, _______, _______, _______, \
        _________________ADJUST_L5_________________, _________________ADJUST_R5_________________, _______, _______, _______ \
    ),
#endif
};

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
