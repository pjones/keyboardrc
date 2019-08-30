/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

enum custom_keycodes {
  KC_LOCK = SAFE_RANGE, // can always be here
  KC_PREV_WS,
  KC_SWAP_SCR,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_MPLY,    KC_MNXT,     KC_LOCK, \
    MO(1),      KC_UP,       RGB_MOD, \
    KC_PREV_WS, KC_SWAP_SCR, KC_RGHT \
  ),

  [1] = LAYOUT(
    RESET,   BL_STEP, KC_STOP, \
    _______, KC_HOME, RGB_MOD, \
    KC_MPRV, KC_END,  KC_MNXT \
  ),
};

void encoder_update_user(uint8_t _, bool anticlockwise) {
  if (anticlockwise) {
    tap_code(KC_VOLD);
  } else {
    tap_code(KC_VOLU);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_LOCK:
    if (!record->event.pressed) {
      SEND_STRING(SS_DOWN(X_LCTRL));
      SEND_STRING(SS_DOWN(X_LALT));
      SEND_STRING(SS_TAP(X_L));
      SEND_STRING(SS_UP(X_LALT));
      SEND_STRING(SS_UP(X_LCTRL));
    }
    break;
  case KC_PREV_WS:
    if (record->event.pressed) {
      SEND_STRING(SS_DOWN(X_LGUI));
      SEND_STRING(SS_TAP(X_QUOTE));
      SEND_STRING(SS_UP(X_LGUI));
    }
    break;
  case KC_SWAP_SCR:
    if (record->event.pressed) {
      SEND_STRING(SS_DOWN(X_LGUI));
      SEND_STRING(SS_TAP(X_BSLASH));
      SEND_STRING(SS_UP(X_LGUI));
    }
    break;
  }
  return true;
}
