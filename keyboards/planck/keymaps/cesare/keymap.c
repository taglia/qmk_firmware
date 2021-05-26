/* Copyright 2018 Cesare Tagliaferri */

#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MACROS
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  MACROS,
  LB,
  BACKLIT,
  SCR_LOCK,
  EJCT_TM,
  NXT_TAB,
  PRV_TAB,
  OF_VIEW,
  OF_REVIEW,
  OF_INBOX,
  GUI_W,
  SSHOT,
  SPOTLIGHT,
  WEB_SEARCH,
  WINDOW_MANIPULATION,
  MAIL_ARCHIVE
};

/////////////////////////////////////////////////////////////////////
// Tap Dance section START
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Tap dance enums
enum {
    MACROS_LB,
    SOME_OTHER_DANCE
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);
// Tap Dance section END
////////////////////////////////////////////////////////////////////////

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid( \
  KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,\
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,\
  KC_ESC, KC_LCTL, KC_LALT, KC_LGUI,  LOWER,  KC_LCTL,  KC_SPC,  RAISE,    KC_RGUI, KC_RALT, KC_RCTL, TD(MACROS_LB)\
),

[_COLEMAK] = LAYOUT_planck_grid( \
  KC_GRV,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,  \
  KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  KC_ESC,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,  KC_LCTL,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, TD(MACROS_LB)\
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
),
[_MACROS] = LAYOUT_planck_grid( \
  SCR_LOCK, PRV_TAB, NXT_TAB, GUI_W,   SSHOT,   WINDOW_MANIPULATION,   WEB_SEARCH,    SPOTLIGHT,    KC_8,  GUI_W, MAIL_ARCHIVE, OF_VIEW,\
  KC_TAB,   KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20, KC_PSCREEN,\
  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,  QWERTY, COLEMAK, XXXXXXX, BACKLIT, XXXXXXX,\
  KC_SLCK, KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX\
),


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
        case MACROS:
          if (record->event.pressed) layer_on(_MACROS);
          else layer_off(_MACROS);
          return FALSE;
        case LB:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT)SS_DOWN(X_SPACE));
          } else {
            SEND_STRING(SS_UP(X_LALT)SS_DOWN(X_SPACE));
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
            SEND_STRING(SS_UP(X_TAB)SS_UP(X_LCTRL)SS_UP(X_LSHIFT));
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
        case SPOTLIGHT:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_SPACE));
          } else {
            SEND_STRING(SS_UP(X_SPACE)SS_UP(X_LGUI));
          }
          return FALSE;
        case WEB_SEARCH:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LALT)SS_DOWN(X_LCTRL)SS_DOWN(X_L));
          } else {
            SEND_STRING(SS_UP(X_L)SS_UP(X_LCTRL)SS_UP(X_LALT)SS_UP(X_LGUI));
          }
          return FALSE;
        case WINDOW_MANIPULATION:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LALT)SS_DOWN(X_LCTRL)SS_DOWN(X_W));
          } else {
            SEND_STRING(SS_UP(X_W)SS_UP(X_LCTRL)SS_UP(X_LALT)SS_UP(X_LGUI));
          }
          return FALSE;
        case MAIL_ARCHIVE:
          if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LCTRL)SS_DOWN(X_A));
          } else {
            SEND_STRING(SS_UP(X_A)SS_UP(X_LCTRL)SS_UP(X_LGUI));
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


/////////////////////////////////////////////////////////////////////
// Tap Dance section START
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

void macros_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_HOLD:
          layer_on(_MACROS);
          break;
        case SINGLE_TAP:
          SEND_STRING(SS_DOWN(X_LALT)SS_DOWN(X_SPACE));
          wait_ms(100);
          SEND_STRING(SS_UP(X_SPACE)SS_UP(X_LALT));
          break;
    }
}

void macros_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
      case SINGLE_TAP:
          SEND_STRING(SS_UP(X_SPACE)SS_UP(X_LALT));
          break;
      case SINGLE_HOLD:
          layer_off(_MACROS);
          break;
    }
    xtap_state.state = 0;
}
qk_tap_dance_action_t tap_dance_actions[] = {
    [MACROS_LB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, macros_finished, macros_reset)
};
// Tap Dance section END
////////////////////////////////////////////////////////////////////////
