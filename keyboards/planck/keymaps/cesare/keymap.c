/* Copyright 2018 Cesare Tagliaferri */

#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  BACKLIT,
  SCR_LOCK,
  EJCT_TM,
  NXT_TAB,
  PRV_TAB,
  OF_VIEW,
  OF_REVIEW,
  OF_INBOX,
  GUI_W,
  SSHOT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid( \
  KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,\
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,\
  KC_ESC, KC_LCTL, KC_LALT, KC_LGUI, LOWER,  KC_LCTL,  KC_SPC,  RAISE,    KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT\
),

[_COLEMAK] = LAYOUT_planck_grid( \
  KC_GRV,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,  \
  KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  KC_ESC,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,  KC_LCTL,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT  \
),

[_RAISE] = LAYOUT_planck_grid( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN, KC_DEL,\
  KC_CAPS, KC_MUTE, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, KC_PLUS, KC_MINS, KC_ASTR, KC_LCBR, KC_RCBR, KC_BSLS,\
  KC_LSFT, KC_MPLY,  KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX, KC_EQL,  KC_UNDS, XXXXXXX, KC_LBRC, KC_RBRC, KC_ENT,\
  KC_ESC, KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______,  _______, _______,   _______, _______\
  ),

[_LOWER] = LAYOUT_planck_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,\
  KC_TAB,   KC_DEL,  KC_INS, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT, XXXXXXX, KC_PIPE,\
  KC_LSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,   KC_END, XXXXXXX, KC_ENT,\
  KC_ESC, KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______,  _______,  _______,   _______, _______\
),

[_ADJUST] = LAYOUT_planck_grid( \
  RESET,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_PAUSE ,\
  KC_TAB,   KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20, KC_PSCREEN,\
  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,  QWERTY, COLEMAK, XXXXXXX, BACKLIT, XXXXXXX,\
  KC_SLCK, KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX\
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return FALSE;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return FALSE;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return FALSE;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            PORTE &= ~(1<<6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            PORTE |= (1<<6);
            #endif
          }
          return FALSE;
        case EJCT_TM:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI)SS_DOWN(X_LSHIFT));
            wait_ms(200);
            SEND_STRING("0");
            wait_ms(200);
            SEND_STRING("0");
          } else {
            SEND_STRING(SS_UP(X_LCTRL)SS_UP(X_LALT)SS_UP(X_LGUI)SS_UP(X_LSHIFT));
          }
          return FALSE;
        case SCR_LOCK:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT));
            wait_ms(200);
            SEND_STRING(SS_DOWN(X_MEDIA_EJECT));
          } else {
            SEND_STRING(SS_UP(X_MEDIA_EJECT));
            wait_ms(200);
            SEND_STRING(SS_UP(X_LCTRL)SS_UP(X_LSHIFT));
          }
          return FALSE;
        case NXT_TAB:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_TAB));
          } else {
            SEND_STRING(SS_UP(X_TAB)SS_UP(X_LCTRL));
          }
          return FALSE;
        case PRV_TAB:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT)SS_DOWN(X_TAB));
          } else {
            SEND_STRING(SS_TAP(X_TAB)SS_UP(X_LCTRL)SS_UP(X_LSHIFT));
          }
          return FALSE;
        case GUI_W:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_W));
          } else {
            SEND_STRING(SS_UP(X_W)SS_UP(X_LGUI));
          }
          return FALSE;
        case OF_VIEW:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LALT)SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT));
            wait_ms(200);
            SEND_STRING(SS_DOWN(X_T));
          } else {
            SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTRL)SS_UP(X_LSHIFT)SS_UP(X_T));
          }
          return FALSE;
        case OF_INBOX:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LALT)SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT));
            wait_ms(200);
            SEND_STRING(SS_DOWN(X_Y));
          } else {
            SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTRL)SS_UP(X_LSHIFT)SS_UP(X_Y));
          }
          return FALSE;
        case OF_REVIEW:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LALT)SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT));
            wait_ms(200);
            SEND_STRING(SS_DOWN(X_R));
          } else {
            SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTRL)SS_UP(X_LSHIFT)SS_UP(X_R));
          }
          return FALSE;
        case SSHOT:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LSHIFT));
            wait_ms(200);
            SEND_STRING(SS_DOWN(X_4));
          } else {
            SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LSHIFT)SS_UP(X_4));
          }
          return FALSE;
      }
    return true;
};

// Standard code
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
