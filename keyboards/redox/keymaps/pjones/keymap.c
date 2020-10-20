#include QMK_KEYBOARD_H

/******************************************************************************/
static uint8_t sysrq_state = 0;

/******************************************************************************/
enum custom_keycodes {
  PJ_LOCK = SAFE_RANGE, // can always be here
  PJ_SYSRQ,
};

/******************************************************************************/
// Numbered only so I remember:
enum {
  L_BASE     = 0,
  L_RAISE    = 1,
  L_LOWER    = 2,
  L_ADJUST   = 3,
  L_MEDIA    = 4,
  L_BLANK    = 5
};

/******************************************************************************/
#define PJ_SINRT  LSFT(KC_INSERT)  // Shift insert.

// Home Row Modifiers:
#define PJ_A    LALT_T(KC_A)    // A or Alt
#define PJ_F    LCTL_T(KC_F)    // F or Control
#define PJ_J    RCTL_T(KC_J)    // J or Control
#define PJ_SCLN RALT_T(KC_SCLN) // Semicolon or Alt

// Left Thumbs:
#define PJ_LGUI   LGUI_T(KC_LBRC)      // Left square bracket or left GUI
#define PJ_LSFT   LSFT_T(KC_BSPC)      // Left shift or backspace.
#define PJ_MEDIA  LT(L_MEDIA, KC_MPLY) // Media play or go to media layer
#define PJ_RAISE  LT(L_RAISE, KC_TAB)  // Tab or go to "raise" layer

// Right Thumbs:
#define PJ_LOWER  LT(L_LOWER, KC_ENT) // Enter or go to "lower" layer
#define PJ_RSFT   RSFT_T(KC_SPC)      // Space or right shift
#define PJ_RGUI   RGUI_T(KC_RBRC)     // Right square bracket or right GUI

// High function keys:
#define PJ_APP7 KC_F16

// Window manager keys:
#define PJ_XM1 LGUI(KC_LCBR)
#define PJ_XM2 LGUI(KC_RCBR)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L_BASE] = LAYOUT(
     KC_TILD , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_MINUS,
     KC_BSLS , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , _______ ,                     _______ , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_EQL  ,
     KC_ESC  , PJ_A    , KC_S    , KC_D    , PJ_F    , KC_G    , _______ ,                     _______ , KC_H    , PJ_J    , KC_K    , KC_L    , PJ_SCLN , KC_QUOT ,
     PJ_XM1  , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , PJ_MEDIA, PJ_LGUI , PJ_RGUI , _______ , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , PJ_XM2  ,
     _______ , _______ , _______ , _______ ,     _______       , PJ_RAISE, PJ_LSFT , PJ_RSFT , PJ_LOWER ,     _______       , _______ , _______ , _______ , _______
  ),

  [L_RAISE] = LAYOUT(
     _______ , _______ , _______ , _______ , _______ , _______ ,                                         _______ , _______ , _______ , KC_LPRN , KC_RPRN , KC_BSLS ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , PJ_SINRT, KC_LBRC , KC_RBRC , KC_PIPE ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT, _______ , KC_GRAVE,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_LT   , KC_GT   , _______ ,
     _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______
  ),

  [L_LOWER] = LAYOUT(
     _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                         KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______ ,
     _______ , KC_F11  , KC_F12  , KC_F13  , KC_F14  , KC_F15  , _______ ,                     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     KC_CAPS , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , KC_DEL  , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ ,     _______     , _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______
  ),

  [L_ADJUST] = LAYOUT(
     _______ , _______ , _______ , _______ , _______ , _______ ,                                         _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , RESET   , _______ , _______ ,                     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , PJ_SYSRQ, _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , _______ , PJ_LOCK , _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______
  ),

  [L_MEDIA] = LAYOUT(
     _______ , _______ , _______ , _______ , _______ , _______ ,                                         _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , KC_MPRV , KC_VOLD , KC_VOLU , KC_MNXT , KC_MSEL , PJ_APP7 ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______
  ),

  [L_BLANK] = LAYOUT(
     _______ , _______ , _______ , _______ , _______ , _______ ,                                         _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, L_LOWER, L_RAISE, L_ADJUST);
}

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
  case PJ_SYSRQ:
    if (!record->event.pressed) {
      if (sysrq_state == 0) {
        sysrq_state = 1;
        clear_mods();
        add_mods(MOD_LALT);
        add_key(KC_PSCREEN);
      } else {
        sysrq_state = 0;
        clear_mods();
        del_key(KC_PSCREEN);
      }
      send_keyboard_report();
    }
    return false;
  }
  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case PJ_A:
  case PJ_F:
  case PJ_J:
  case PJ_SCLN:
    return 200;
  default:
    return TAPPING_TERM;
  }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case PJ_LSFT:
  case PJ_RSFT:
    return false;
  default:
    return false;
  }
}

// Local variables:
//   eval: (whitespace-mode -1)
//   eval: (auto-fill-mode -1)
//   eval: (flycheck-mode -1)
//   projectile-project-compilation-cmd: "nix-shell --run 'sudo make redox:pjones:dfu'"
// End:
