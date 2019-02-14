/* Copyright 2018 Cesare Tagliaferri */

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | Ctrl | Alt  | GUI  |Lower | Ctrl |Space |Raise | Left | Right| RGUI |RShift|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {KC_ESC, KC_LCTL, KC_LALT, KC_LGUI, LOWER,  KC_LCTL,  KC_SPC,  RAISE,    KC_LEFT, KC_RGHT, KC_RGUI, KC_RSFT}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps | Play |  Ins | Vol- | Mute | Vol+ |   +  |   -  |   *  |   {  |   }  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LShift| Next |      |      |      |      |   =  |   _  |      |   [  |   ]  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Esc | Ctrl |  Alt |  GUI | xxxx |             |      | Down |  Up  | RGUI |RShift|
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN, KC_DEL },
  {KC_CAPS,  KC_MPLY,  KC_INS, KC_VOLD, KC_MUTE, KC_VOLU, KC_PLUS, KC_MINS, KC_ASTR, KC_LCBR, KC_RCBR, KC_BSLS},
  {KC_LSFT, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL,  KC_UNDS, XXXXXXX, KC_LBRC, KC_RBRC, KC_ENT},
  {KC_ESC, KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______,  KC_DOWN, KC_UP,   KC_RGUI, KC_RSFT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |  Del |  Ins |      |      |      |  <-  | Down |  Up  |  ->  |      |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LShift|RCtrl | RAlt | RGUI |      |      | Home | PgDn | PgUp | End  |      | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |LCtrl | LAlt | LGUI |      |             | xxxx | Down |  Up  | RGUI |RShift|
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
  {KC_TAB,   KC_DEL,  KC_INS, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT, XXXXXXX, KC_PIPE},
  {KC_LSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,   KC_END, XXXXXXX, KC_ENT},
  {KC_ESC, KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______,  KC_DOWN,  KC_UP,   KC_RGUI, KC_RSFT}
},

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = {
  {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
  {XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | Pause|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Tab | F11  | F12  | F13  | F14  | F15  | F16  | F17  | F18  | F19  | F20  |PrtScr|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |PLOVER|      |      |QWERTY|      |      | Brite|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ScrLck| Ctrl | Alt  |  GUI | xxxx |             | xxxx |MsLClk|WhlUp |WhlDwn|MsRClk|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {RESET,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_PAUSE },
  {KC_TAB,   KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20, KC_PSCREEN},
  {KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX,  PLOVER, XXXXXXX, XXXXXXX,  QWERTY, XXXXXXX, XXXXXXX, BACKLIT, _______},
  {KC_SLCK, KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______,  KC_MS_BTN1, KC_MS_WH_DOWN, KC_MS_WH_UP,  KC_MS_BTN2}
}


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
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
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        PORTE &= ~(1<<6);
      } else {
        unregister_code(KC_RSFT);
        PORTE |= (1<<6);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}
