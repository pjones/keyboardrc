#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum {
  L_BASE     = 0,
  L_RAISE    = 1,
  L_MEDIA    = 2,
  L_LOWER     = 3,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

#define NO_KEY   KC_NO // Doesn't map to a key on this board.
#define SFT_INS  LSFT(KC_INSERT)
#define MED_GRV  LT(L_MEDIA, KC_GRV)
#define ALT_A    LALT_T(KC_A)
#define GUI_S    LGUI_T(KC_S)
#define SFT_D    LSFT_T(KC_D)
#define CTL_F    LCTL_T(KC_F)
#define RSE_G    LT(L_RAISE, KC_G)
#define RSE_H    LT(L_RAISE, KC_H)
#define LWR_BS   LT(L_LOWER, KC_BSPC)
#define LWR_SP   LT(L_LOWER, KC_SPC)
#define CTL_J    RCTL_T(KC_J)
#define SFT_K    RSFT_T(KC_K)
#define GUI_L    RGUI_T(KC_L)
#define ALT_SCLN LALT_T(KC_SCLN)
#define SFT_CAP  LSFT_T(KC_CAPS)
#define CTL_MIN  LCTL(KC_MINS)
#define CTL_PLS  LCTL(KC_PLUS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_65_with_macro(
    KC_F1,   KC_F2,   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  NO_KEY,  KC_BSPC, KC_MPLY, \
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_MNXT, \
    KC_F5,   KC_F6,   MED_GRV, ALT_A,   GUI_S,   SFT_D,   CTL_F,   RSE_G,   RSE_H,   CTL_J,   SFT_K,   GUI_L,   ALT_SCLN,KC_QUOT, KC_ENT,                    KC_STOP, \
    KC_F7,   KC_F8,   SFT_CAP, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,            KC_PSCR, \
    KC_F11,  KC_F12,  KC_LCTL, KC_LALT, KC_LGUI, KC_INS,  LWR_BS,           NO_KEY,  LWR_SP,  KC_RGUI, KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [L_RAISE] = LAYOUT_65_with_macro(
    RGB_TOG, RGB_MOD, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,  LCTL(KC_BRIU), \
    RGB_M_SW,RGB_M_B, _______, KC_ESC,  _______, _______, KC_UNDS, CTL_MIN, CTL_PLS, KC_EQL,  SFT_INS, _______, KC_PIPE, _______, _______, _______,          _______, \
    RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______, _______,                   KC_POWER, \
    RGB_HUI, RGB_HUD, _______, RESET,   _______, _______, _______, KC_MINS, KC_PLUS, _______, _______, _______, KC_BSLS, _______,          KC_PGUP,          _______, \
    RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,          KC_HOME, KC_PGDN, KC_END
  ),
  
  [L_LOWER] = LAYOUT_65_with_macro(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_LCBR, _______, _______, KC_RCBR, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______,          _______, _______, \
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,          _______, _______, _______
  ),

  [L_MEDIA] = LAYOUT_65_with_macro(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_F15,  KC_F16,  _______,                   _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______, \
    _______, _______, _______, _______, _______, _______, _______,          _______, KC_MPLY, _______, _______, _______,          _______, _______, _______
  ),

/*
  [L_BLANK] = LAYOUT_65_with_macro(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,          _______, _______, _______
  )
*/
};

bool encoder_update_user(uint8_t _index, bool clockwise) {
  switch(biton32(layer_state)){
  case L_RAISE:
    if (clockwise) {
      tap_code(KC_BRIU);
    } else {
      tap_code(KC_BRID);
    }
    break;
  default:
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    break;
  }
  return true;
}

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *_record) {
  switch (keycode) {
  case GUI_S:
  case GUI_L:
    return TAPPING_TERM + 25;
  case SFT_D:
  case SFT_K:
    return TAPPING_TERM - 25;
  default:
    return TAPPING_TERM;
  }
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *_record) {
  switch (keycode) {
  case GUI_S:
  case GUI_L:
    return false;
  default:
    return true;
  }
}
#endif

// Local variables:
//   eval: (whitespace-mode -1)
//   eval: (auto-fill-mode -1)
//   eval: (flycheck-mode -1)
//   compile-command: "nix-shell --run 'make keebio/quefrency/rev3:pjones:flash'"
// End:
