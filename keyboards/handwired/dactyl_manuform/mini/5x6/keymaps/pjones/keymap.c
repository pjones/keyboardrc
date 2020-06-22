#include QMK_KEYBOARD_H

/******************************************************************************/
static uint8_t caps_state = 0;

/******************************************************************************/
// Numbered only so I remember:
enum {
  L_BASE     = 0,
  L_RAISE    = 1,
  L_LOWER    = 2,
  L_BLANK    = 3
};

/******************************************************************************/
#define PJ_FULLW  LGUI(KC_EXLM)
#define PJ_SINGW  LGUI(LALT(KC_8))
#define PJ_SCRAT  LGUI(KC_CIRC)
#define PJ_SINRT  LSFT(KC_INSERT)
#define PJ_TABPRE LCTL(KC_LBRC)     // Previous tab.
#define PJ_TABNXT LCTL(KC_RBRC)     // Next tab.
#define PJ_SCRN   LGUI(LSFT(KC_0))  // Screen next.
#define PJ_SCRS   LGUI(KC_BSLS)     // Swap screens.
#define PJ_C_PLUS LCTL(LSFT(KC_EQL))
#define PJ_C_MIN  LCTL(KC_MINUS)

// Left Thumbs:
#define PJ_LALT   LALT_T(KC_MPLY)
#define PJ_LCTL   LCTL_T(KC_TAB)
#define PJ_LSFT   LSFT_T(KC_BSPC)
#define PJ_RAISE  OSL(L_RAISE)
#define PJ_LGUI   LGUI_T(KC_LBRC)

// Right Thumbs:
#define PJ_RALT   RALT_T(KC_MNXT)
#define PJ_RCTL   RCTL_T(KC_ENT)
#define PJ_RSFT   RSFT_T(KC_SPC)
#define PJ_LOWER  OSL(L_LOWER)
#define PJ_RGUI   RGUI_T(KC_RBRC)

/******************************************************************************/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L_BASE] = LAYOUT_5x6(
     KC_GRAVE , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,       KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINUS ,
     KC_BSLASH, KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,       KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_EQL  ,
     KC_ESC   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,       KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
     KC_LCBR  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,       KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RCBR  ,
                KC_END   , KC_HOME  , PJ_RAISE , PJ_LCTL  , PJ_LSFT  ,       PJ_RSFT  , PJ_RCTL  , PJ_LOWER , KC_PGDN  , KC_PGUP  ,
                                                 PJ_LALT  , PJ_LGUI  ,       PJ_RGUI  , PJ_RALT
  ),

  [L_RAISE] = LAYOUT_5x6(
     _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,       KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , _______  ,
     _______  , _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , PJ_SINRT , _______  ,
     _______  , KC_VOLD  , KC_VOLU  , KC_MPRV  , KC_MPLY  , KC_MNXT  ,       KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , _______  , _______  ,
     RESET    , _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  , _______  ,
                _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  ,
                                                 _______  , _______  ,       _______  , _______
  ),

  [L_LOWER] = LAYOUT_5x6(
     PJ_FULLW , KC_F11   , KC_F12   , KC_F13   , KC_F14   , KC_F15   ,       _______  , _______  , _______  , _______  , _______  , _______  ,
     PJ_SINGW , _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  , _______  ,
     KC_CAPS  , _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  , _______  ,
     PJ_SCRN  , _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  , _______  ,
                _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  ,
                                                 _______  , _______  ,       _______  , _______
  ),

  [L_BLANK] = LAYOUT_5x6(
     _______  , _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  , _______  ,
     _______  , _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  , _______  ,
     _______  , _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  , _______  ,
     _______  , _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  , _______  ,
                _______  , _______  , _______  , _______  , _______  ,       _______  , _______  , _______  , _______  , _______  ,
                                                 _______  , _______  ,       _______  , _______
  ),
};

/******************************************************************************/
void pjones_set_rgb_led(uint8_t r, uint8_t g, uint8_t b) {
  writePin(C6, 255 - r);
  writePin(B5, 255 - g);
  writePin(D7, 255 - b);
}

/******************************************************************************/
void keyboard_pre_init_user(void) {
  // Configure the LED:
  setPinOutput(C6); // Red
  setPinOutput(B5); // Green
  setPinOutput(D7); // Blue
  pjones_set_rgb_led(0, 0, 0);
}

bool led_update_user(led_t led_state) {
  if (caps_state != led_state.caps_lock) {
    caps_state = led_state.caps_lock;
    pjones_set_rgb_led((caps_state ? 255 : 0), 0, 0);
  }

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t r=0, g=0, b=0;

  switch (get_highest_layer(state)) {
  case L_RAISE:
  case L_LOWER:
    r=255; g=0; b=255;
    break;
  }

  // LED processing:
  if (!caps_state) {
    pjones_set_rgb_led(r, g, b);
  }

  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// Local variables:
//   eval: (whitespace-mode -1)
//   eval: (auto-fill-mode -1)
//   projectile-project-compilation-cmd: "nix-shell --run 'make handwired/dactyl_manuform/mini/5x6:pjones:avrdude'"
// End:
