#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/******************************************************************************/
bool g_draw_mode = false;
bool g_caps_lock_on = false;

/******************************************************************************/
enum {
  L_BASE = 0,
  L_SYMB,
  L_NUMBERS,
  L_MVMT,
  L_SYMB_ALT,
  L_FUNCKEYS,
  L_DRAWING
};

/******************************************************************************/
enum {
  M_SCREEN_PREV = 0
};

/******************************************************************************/
enum custom_keycodes {
  K_DRAW = SAFE_RANGE, // can always be here
};

/******************************************************************************/
#define KC_GUID LGUI_T(KC_D)
#define KC_CTRF LCTL_T(KC_F)
#define KC_CTRJ RCTL_T(KC_J)
#define KC_GUIK RGUI_T(KC_K)
#define KC_ALTG LALT_T(KC_G)
#define KC_ALTH RALT_T(KC_H)

#define KC_PEN1 KC_LSHIFT
#define KC_PEN2 KC_LCTRL
#define KC_PEN3 LSFT(KC_LCTRL)
#define KC_PEN4 KC_LALT
#define KC_PENE LALT(KC_LCTRL)
#define KC_PENC LSFT(KC_F9)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |  CAPS  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |ESC/SHFT|   A  |   S  | G/D  | C/F  | A/G  |------|           |------| A/H  | C/J  | G/K  |   L  |  ;   | '/SHFT |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | F-KEYS |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  /   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | GUI  |                                       | GUI-P|      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Bspc | TAB  |      |       |      | ENT  | Spc  |
 *                                 |      |      |------|       |------|      |      |
 *                                 | Syms |Altsym|      |       |      |      | Nums |
 *                                 `--------------------'       `--------------------'
 */
[L_BASE] = LAYOUT_ergodox(
  // Left Hand:
  KC_NO,          KC_NO, KC_NO,  KC_NO,   KC_NO,         KC_NO,   KC_NO,
  KC_TAB,         KC_Q,  KC_W,   KC_E,    KC_R,          KC_T,    KC_NO,
  LSFT_T(KC_ESC), KC_A,  KC_S,   KC_GUID, KC_CTRF,       KC_ALTG, /* 2U */
  MO(L_FUNCKEYS), KC_Z,  KC_X,   KC_C,    KC_V,          KC_B,    KC_NO,
  KC_NO,          KC_NO, KC_NO,  KC_NO,   OSM(MOD_LGUI), /* NA */ /* NA */

  // Left Thumb Cluster:
  /* NA */  KC_NO,      KC_NO,
  /* 2U */  /* 2U */    KC_NO,
  LT(L_SYMB, KC_BSPC),  LT(L_SYMB_ALT, KC_TAB), KC_NO,

  // Right Hand:
  KC_NO,   KC_NO,   KC_NO,            KC_NO,    KC_NO,  KC_NO,    KC_NO,
  KC_NO,   KC_Y,    KC_U,             KC_I,     KC_O,   KC_P,     KC_CAPS,
  /* 2U */ KC_ALTH, KC_CTRJ,          KC_GUIK,  KC_L,   KC_SCLN,  RSFT_T(KC_QUOT),
  KC_NO,   KC_N,    KC_M,             KC_COMM,  KC_DOT, KC_SLSH,  KC_NO,
  /* NA */ /* NA */ M(M_SCREEN_PREV), KC_NO,    KC_NO,  KC_NO,    KC_NO,

  // Right Thumb Cluster:
  KC_NO,   KC_NO,                  /* NA */
  KC_NO,   /* 2U */                /* 2U */
  KC_NO,   LT(L_NUMBERS, KC_ENT), LT(L_NUMBERS, KC_SPC)
),

/* Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   \  |   `  |   |  |   +  |   =  |      |           |      |   _  |   -  |   ~  |   [  |   ]  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   !  |   @  |   #  |   $  |   %  |------|           |------|   ^  |   &  |   *  |   (  |   )  |   "    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         | RESET|      |      |      | DRAW |      |           |      |      |      |      |   <  |   >  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
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
  KC_NO,    KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,
  KC_TRNS,  KC_BSLASH,  KC_GRAVE, KC_PIPE,  KC_PLUS,  KC_EQUAL,   KC_TRNS,
  KC_TRNS,  KC_EXLM,    KC_AT,    KC_HASH,  KC_DLR,   KC_PERCENT, /* 2U */
  KC_TRNS,  RESET,      KC_TRNS,  KC_TRNS,  KC_TRNS,  K_DRAW,     KC_TRNS,
  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  /* NA */    /* NA */

  // Left Thumb Cluster:
  /* NA */ KC_TRNS, KC_TRNS,
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_UNDS, KC_MINUS, KC_TILD, KC_LBRC, KC_RBRC, KC_TRNS,
  /* 2U */ KC_CIRC, KC_AMPR,  KC_ASTR, KC_LPRN, KC_RPRN, KC_GRAVE,
  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_LABK, KC_RABK, KC_TRNS,
  /* NA */ /* NA */ KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Numbers Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        | V_DN | V_UP |A_PREV|A_PLAY|A_NEXT|      |           |      |      |  -   |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  TAB   |  1   |  2   |  3   |  4   |  5   |------|           |------|  6   |   7  |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |  ,   |  .   |  /   |        |
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
  KC_TRNS, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS,
  KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* NA */ /* NA */

  // Left Thumb Cluster:
  /* NA */ KC_TRNS, KC_TRNS,
  /* 2U */ /* 2U */ KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_MINUS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  /* 2U */  KC_6,    KC_7,     KC_8,    KC_9,     KC_0,    KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_COMM, KC_DOT,   KC_SLSH, KC_TRNS,
  /* NA */  /* NA */ KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Movement Keys;
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| LEFT | DOWN |  UP  |RIGHT |      |        |
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
[L_MVMT] = LAYOUT_ergodox(
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
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  /* 2U */  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  /* NA */  /* NA */ KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Alternate Symbols:
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |  [   |  ]   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |  {   |  }   |   `    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |  <   |  >   |        |
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
[L_SYMB_ALT] = LAYOUT_ergodox(
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
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS,
  /* 2U */  KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_GRAVE,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_LABK, KC_RABK, KC_TRNS,
  /* NA */  /* NA */ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),


/* Function Keys Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F11 |  F12 | F13  |  F14 |  F15 |      |           |      |  F16 |  F17 |  F18 |  F19 |  F20 |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |------|           |------|  F6  |  F7  |  F8  |  F9  |  F10 |        |
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
[L_FUNCKEYS] = LAYOUT_ergodox(
  // Left Hand:
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_TRNS,
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* NA */ /* NA */

  // Left Thumb Cluster:
  /* NA */ KC_TRNS, KC_TRNS,
  /* 2U */ /* 2U */ KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_F16,  KC_F17,  KC_F18,  KC_F19,   KC_F20,  KC_TRNS,
  /* 2U */  KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  /* NA */  /* NA */ KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),


/* Drawing
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ERASE  | PEN1 | PEN2 | PEN3 | PEN4 | CLR  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      | EXIT |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |       |     |      |      |      |
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
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_PENE, KC_PEN1, KC_PEN2, KC_PEN3, KC_PEN4, KC_PENC, /* 2U */
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   K_DRAW,  KC_NO,
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   /* NA */ /* NA */

  // Left Thumb Cluster:
  KC_NO, KC_NO,     /* NA */
  /* 2U */ /* 2U */ KC_NO,
  KC_NO, KC_NO,     KC_NO,

  // Right Hand:
  KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  /* 2U */ KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_F10,
  /* NA */ /* NA */ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

  // Right Thumb Cluster:
  KC_NO, KC_NO,   /* NA */
  KC_NO, /* 2U */ /* 2U */
  KC_NO, KC_NO,   KC_NO
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
  case M_SCREEN_PREV:
    return MACRODOWN(D(LGUI), T(P), U(LGUI), END);
  };

  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /*
     * Toggle drawing mode.
     */
  case K_DRAW:
    if (!record->event.pressed) {
      if (g_draw_mode) {
        g_draw_mode = false;
        layer_off(L_DRAWING);
        SEND_STRING(SS_DOWN(X_LCTRL));
        SEND_STRING(SS_TAP(X_F9));
        SEND_STRING(SS_UP(X_LCTRL));
      } else {
        g_draw_mode = true;
        layer_on(L_DRAWING);
        SEND_STRING(SS_TAP(X_F9));
      }
    }
  }

  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  g_draw_mode = false;

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
};

void led_set_user(uint8_t usb_led) {
  g_caps_lock_on = (usb_led & (1<<USB_LED_CAPS_LOCK));
}

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, L_SYMB, L_NUMBERS, L_MVMT);
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  switch (layer) {
  case L_MVMT:
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
    break;
  case L_SYMB:
    ergodox_right_led_2_on();
    break;
  case L_NUMBERS:
    ergodox_right_led_3_on();
    break;
  case L_FUNCKEYS:
    ergodox_right_led_1_on();
    ergodox_right_led_3_on();
    break;
  case L_DRAWING:
    ergodox_right_led_1_on();
    break;
  }

  if (g_caps_lock_on) {
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
  }
};
