#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/******************************************************************************/
enum {
  L_BASE = 0,
  L_NUMBERS,
  L_SYMB,
  L_MOVEMENT,
  L_DRAWING
};

/******************************************************************************/
enum {
  M_PASSWD = 0,
  M_TODO,
  M_CALC,
  M_CXB,
  M_CCR,
  M_SCREEN_PREV,
  M_SCREEN_NEXT
};

/******************************************************************************/
#define FONT_PLUS      LCTL(KC_PLUS)
#define FONT_MINUS     LCTL(KC_MINUS)

/******************************************************************************/
enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |S-s h |           | S-s l|   6  |   7  |   8  |   9  |   0  |   CAPS |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Super  |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |  Super |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Tab/Sf |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   | Ent/Sf |
 * |--------+------+------+------+------+------| Symb |           | Symb |------+------+------+------+------+--------|
 * | Numbers|   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  /   |Numbers |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | CALC |                                       | PASS |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |C-x b | MOVE |       | DRAW | C-c r|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 | Back |      | F+   |       | PgUp |        |      |
 *                                 | Spc  | Ctrl |------|       |------|  Alt   | Space|
 *                                 |      |      | F-   |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[L_BASE] = LAYOUT_ergodox(
  // Left Hand:
  KC_ESC,         KC_1,  KC_2,   KC_3,   KC_4,      KC_5,    M(M_SCREEN_PREV),
  OSM(MOD_LGUI),  KC_Q,  KC_W,   KC_E,   KC_R,      KC_T,    TT(L_NUMBERS),
  SFT_T(KC_TAB),  KC_A,  KC_S,   KC_D,   KC_F,      KC_G,    /* 2U */
  TT(L_NUMBERS),  KC_Z,  KC_X,   KC_C,   KC_V,      KC_B,    OSL(L_SYMB),
  KC_NO,          KC_NO, KC_NO,  KC_NO,  M(M_CALC), /* NA */ /* NA */

  // Left Thumb Cluster:
  /* NA */ M(M_CXB),  TT(L_MOVEMENT),
  /* 2U */ /* 2U */   FONT_PLUS,
  KC_BSPC, KC_LCTRL,  FONT_MINUS,

  // Right Hand:
  M(M_SCREEN_NEXT), KC_6,      KC_7,        KC_8,     KC_9,   KC_0,     KC_CAPS,
  TT(L_NUMBERS),    KC_Y,      KC_U,        KC_I,     KC_O,   KC_P,     OSM(MOD_LGUI),
  /* 2U */          KC_H,      KC_J,        KC_K,     KC_L,   KC_SCLN,  SFT_T(KC_ENT),
  OSL(L_SYMB),      KC_N,      KC_M,        KC_COMM,  KC_DOT, KC_SLSH,  TT(L_NUMBERS),
  /* NA */          /* NA */   M(M_PASSWD), KC_NO,    KC_NO,  KC_NO,    KC_NO,

  // Right Thumb Cluster:
  TT(L_DRAWING), M(M_CCR),  /* NA */
  KC_PGUP,       /* 2U */   /* 2U */
  KC_PGDN,       KC_LALT,   KC_SPC
),

/* Numbers Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  1   |  2   |  3   |  4   |  5   |------|           |------|  6   |   7  |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |       |     |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_NUMBERS] = LAYOUT_ergodox(
  // Left Hand:
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5, /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* NA */ /* NA */

  // Left Thumb Cluster:
  /* NA */ KC_TRNS, KC_TRNS,
  /* 2U */ /* 2U */ KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  /* 2U */  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  /* NA */  /* NA */ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | RESET   |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |    ~    |   \  |   `  |   |  |   +  |   =  |      |           |      |   _  |   -  |   ~  |   [  |   ]  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    "    |   !  |   @  |   #  |   $  |   %  |------|           |------|   ^  |   &  |   *  |   (  |   )  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |   {  |   }  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |   <  |  >   |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_SYMB] = LAYOUT_ergodox(
  // Left Hand:
  RESET,   KC_F1,      KC_F2,    KC_F3,    KC_F4,    KC_F5,      KC_TRNS,
  KC_TILD, KC_BSLASH,  KC_GRAVE, KC_PIPE,  KC_PLUS,  KC_EQUAL,   KC_NO,
  KC_DQUO, KC_EXLM,    KC_AT,    KC_HASH,  KC_DLR,   KC_PERCENT, /* 2U */
  KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,
  KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  /* NA */  /* NA */

  // Left Thumb Cluster:
  /* NA */ KC_TRNS, KC_TRNS,
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS, KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_NO,   KC_UNDS, KC_MINUS, KC_TILD, KC_LBRC, KC_RBRC, KC_F12,
  /* 2U */ KC_CIRC, KC_AMPR,  KC_ASTR, KC_LPRN, KC_RPRN, KC_QUOT,
  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_LCBR, KC_RCBR, KC_TRNS,
  /* NA */ /* NA */ KC_TRNS,  KC_TRNS, KC_LABK, KC_RABK, KC_TRNS,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Movement
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | Home | PgDn | PgUp | End  |      | Btn 2  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| Left | Down | Up   | Right|      | Btn 3  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | M-L  | M-D  | M-U  | M-R  |      | Btn 1  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |       |     |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_MOVEMENT] = LAYOUT_ergodox(
  // Left Hand:
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* NA */ /* NA */

  // Left Thumb Cluster:
  /* NA */ KC_TRNS, KC_TRNS,
  /* 2U */ /* 2U */ KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_TRNS, KC_BTN2,
  /* 2U */  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS, KC_BTN3,
  KC_TRNS,  KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  KC_TRNS, KC_BTN1,
  /* NA */  /* NA */ KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Drawing
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Pen 1  |      |      |      |      |      |Erase |           |      |      |      |      |      |      | On/Off |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Pen 2  |      |      |      |      |      |      |           |      |      |      |      |      |      | Clear  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Pen 3  |      |      |      |      |      |------|           |------|      |      |      |      |      | Toggle |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Pen 4  |      |      |      |      |      |      |           |      |      |      |      |      |      | Undo   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Pen 5|      |      |      |      |                                       |       |     |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------+------+------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_DRAWING] = LAYOUT_ergodox(
  // Left Hand:
  KC_LSHIFT,      KC_A,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LALT(KC_LCTRL),
  KC_LCTRL,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  LSFT(KC_LCTRL), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* 2U */
  KC_LALT,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  LSFT(KC_LALT),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* NA */ /* NA */

  // Left Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  /* 2U */ /* 2U */ KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F9,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_F9),
  /* 2U */ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_F9),
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F10,
  /* NA */ /* NA */ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
  case M_PASSWD:
    return MACRODOWN(D(LGUI), T(SCLN), T(P), U(LGUI), END);
  case M_TODO:
    return MACRODOWN(D(LGUI), T(SCLN), T(T), U(LGUI), END);
  case M_CALC:
    return MACRODOWN(D(LGUI), T(SCLN), T(C), U(LGUI), END);
  case M_CXB:
    return MACRODOWN(D(LCTL), T(X), U(LCTL), T(B), END);
  case M_CCR:
    return MACRODOWN(D(LCTL), T(C), U(LCTL), T(R), END);
  case M_SCREEN_PREV:
    return MACRODOWN(D(LGUI), T(S), U(LGUI), T(H), END);
  case M_SCREEN_NEXT:
    return MACRODOWN(D(LGUI), T(S), U(LGUI), T(L), END);
  };

  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
  case 1:
    ergodox_right_led_1_on();
    break;
  case 2:
    ergodox_right_led_2_on();
    break;
  case 3:
    ergodox_right_led_3_on();
    break;
  case 4:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
  default:
    // none
    break;
  }
};
