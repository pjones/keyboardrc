#include QMK_KEYBOARD_H

/******************************************************************************/
static uint8_t sysrq_state = 0;

/******************************************************************************/
enum custom_keycodes {
  PJ_LOCK = SAFE_RANGE, // can always be here
  PJ_SYSRQ,
  PJ_LT,
  PJ_GT,
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
#define PJ_A    LALT_T(KC_A)    // A or ALT
#define PJ_F    LCTL_T(KC_F)    // F or Control
#define PJ_J    RCTL_T(KC_J)    // J or Control
#define PJ_SCLN RALT_T(KC_SCLN) // Semicolon or Alt
#define PJ_GRV  LGUI_T(KC_GRV)  // Grave or GUI
#define PJ_QUOT RGUI_T(KC_QUOT) // Quote or GUI

// Left Thumbs:
#define PJ_BSPC   LT(L_RAISE, KC_BSPC) // Backspace or switch to raise layer
#define PJ_TAB    LSFT_T(KC_TAB)       // Tab or shift

#define PJ_LGUI   LGUI_T(KC_LBRC)      // Left square bracket or left GUI
#define PJ_MEDIA  LT(L_MEDIA, KC_MPLY) // Media play or go to media layer

// Right Thumbs:
#define PJ_SPC    LT(L_LOWER, KC_SPC) // Space or switch to lower layer
#define PJ_ENT    RSFT_T(KC_ENT)      // Enter or shift

#define PJ_RGUI   RGUI_T(KC_RBRC)     // Right square bracket or right GUI

// High function keys:
#define PJ_APP7 KC_F16

// Window manager keys:
#define PJ_XM1 LGUI(KC_LCBR)
#define PJ_XM2 LGUI(KC_RCBR)
#define PJ_XM3 LGUI(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L_BASE] = LAYOUT(
     KC_ESC  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSLS ,
     KC_CAPS , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_F11  ,                     KC_F12  , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_PIPE ,
     PJ_GRV  , PJ_A    , KC_S    , KC_D    , PJ_F    , KC_G    , PJ_MEDIA,                     KC_MNXT , KC_H    , PJ_J    , KC_K    , KC_L    , PJ_SCLN , PJ_QUOT ,
     PJ_XM1  , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_UNDS , KC_MINS , KC_EQL  , KC_PLUS , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , PJ_XM2  ,
     _______ , _______ , _______ , _______ ,     KC_LT         , PJ_TAB  , PJ_BSPC , PJ_SPC  , PJ_ENT  ,     KC_GT         , _______ , _______ , _______ , _______
  ),

  [L_RAISE] = LAYOUT(
     _______ , _______ , _______ , _______ , _______ , _______ ,                                         _______ , _______ , _______ , KC_LPRN , KC_RPRN , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , PJ_SINRT, KC_LBRC , KC_RBRC , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT, _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______ ,     PJ_GT         , _______ , _______ , _______ , _______
  ),

  [L_LOWER] = LAYOUT(
     _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                         KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , KC_DEL  , _______ , _______ , _______ ,                     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ ,     PJ_LT         , _______ , _______ , _______ , _______ ,     _______       , _______ , _______ , _______ , _______
  ),

  [L_ADJUST] = LAYOUT(
     _______ , _______ , _______ , _______ , _______ , _______ ,                                         _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , RESET   , _______ , _______ ,                     _______ , _______ , _______ , _______ , KC_LCBR , KC_RCBR , _______ ,
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
  case PJ_LT:
    if (!record->event.pressed) {
      SEND_STRING("<-");
    }
    break;
  case PJ_GT:
    if (!record->event.pressed) {
      SEND_STRING("->");
    }
    break;
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
  case PJ_TAB:
  case PJ_ENT:
    return 150;
  default:
    return TAPPING_TERM;
  }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  return false;
}

// Local variables:
//   eval: (whitespace-mode -1)
//   eval: (auto-fill-mode -1)
//   eval: (flycheck-mode -1)
//   projectile-project-compilation-cmd: "nix-shell --run 'make redox:pjones:avrdude'"
// End:
