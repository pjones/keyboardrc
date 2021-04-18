#include QMK_KEYBOARD_H

#define PJ_FN LT(L_RAISE, KC_MPLY)

// Numbered only so I remember:
enum {
  L_BASE     = 0,
  L_RAISE    = 1,
};

enum custom_keycodes {
  PJ_LOCK = SAFE_RANGE // can always be here
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_ortho_4x4(
    KC_7, KC_8,   KC_9,   KC_PLUS,
    KC_4, KC_5,   KC_6,   KC_MINS,
    KC_1, KC_2,   KC_3,   PJ_LOCK,
    KC_0, KC_DOT, PJ_FN,  KC_ENT
  ),

  [L_RAISE] = LAYOUT_ortho_4x4(
    KC_7, KC_8,   KC_9,   KC_PLUS,
    KC_4, KC_5,   KC_6,   KC_MINS,
    KC_1, KC_2,   KC_3,   KC_MINS,
    KC_0, KC_DOT, KC_ENT, KC_ENT
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case PJ_LOCK:
    if (!record->event.pressed) {
      SEND_STRING(SS_DOWN(X_LCTRL));
      SEND_STRING(SS_DOWN(X_LALT));
      SEND_STRING(SS_TAP(X_L));
      SEND_STRING(SS_UP(X_LALT));
      SEND_STRING(SS_UP(X_LCTRL));
    }
    break;
  }

  return true;
}

// Local variables:
//   eval: (whitespace-mode -1)
//   eval: (auto-fill-mode -1)
//   eval: (flycheck-mode -1)
//   projectile-project-compilation-cmd: "nix-shell --run 'make 1upkeyboards/sweet16:pjones:avrdude'"
// End:
