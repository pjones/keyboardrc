#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum {
  L_BASE     = 0,
  L_RAISE    = 1,
  L_MEDIA    = 2,
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
#define CTL_J    RCTL_T(KC_J)
#define SFT_K    RSFT_T(KC_K)
#define GUI_L    RGUI_T(KC_L)
#define ALT_SCLN LALT_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_65_with_macro(
    KC_F1,   KC_F2,   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  NO_KEY,  KC_BSPC, KC_MPLY, \
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_MNXT, \
    KC_F5,   KC_F6,   MED_GRV, ALT_A,   GUI_S,   SFT_D,   CTL_F,   RSE_G,   RSE_H,   CTL_J,   SFT_K,   GUI_L,   ALT_SCLN,KC_QUOT, KC_ENT,                    KC_STOP, \
    KC_F7,   KC_F8,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,            KC_PSCR, \
    KC_F11,  KC_F12,  KC_LCTL, KC_LALT, KC_LGUI, KC_INS,  KC_BSPC,          NO_KEY,  KC_SPC,  KC_RGUI, KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [L_RAISE] = LAYOUT_65_with_macro(
    RGB_TOG, RGB_MOD, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,  _______, \
    RGB_M_SW,RGB_M_B, _______, KC_ESC,  _______, _______, RESET,   _______, _______, _______, SFT_INS, _______, _______, KC_PIPE, KC_BSLS, _______,          _______, \
    RGB_SAI, RGB_SAD, _______, _______, _______, KC_CAPS, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______, _______,                   KC_POWER, \
    RGB_HUI, RGB_HUD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______, \
    RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,          _______, _______, _______
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

// Local variables:
//   eval: (whitespace-mode -1)
//   eval: (auto-fill-mode -1)
//   eval: (flycheck-mode -1)
//   projectile-project-compilation-cmd: "nix-shell --run 'make keebio/quefrency/rev3:pjones:flash'"
// End:
