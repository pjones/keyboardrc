#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/******************************************************************************/
bool g_keystatus_sym = false;
bool g_keystatus_num = false;
bool g_draw_mode = false;

/******************************************************************************/
enum {
  L_BASE = 0,
  L_SYMB,
  L_NUMBERS,
  L_FKEYS,
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
  M_CX_TICK,
  M_SCREEN_PREV,
  M_SCREEN_NEXT
};

/******************************************************************************/
#define FONT_PLUS      LCTL(KC_PLUS)
#define FONT_MINUS     LCTL(KC_MINUS)

/******************************************************************************/
enum custom_keycodes {
  K_SYMB = SAFE_RANGE, // can always be here
  K_NUMB,
  K_DRAW
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |S-s h |           | S-s l|   6  |   7  |   8  |   9  |   0  |   CAPS |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    "   |   Q  |   W  |   E  |   R  |   T  | Play |           | Next |   Y  |   U  |   I  |   O  |   P  |    '   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Tab/Sft |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   | Ent/Sft|
 * |--------+------+------+------+------+------| Super|           |Super |------+------+------+------+------+--------|
 * |    (   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  /   |    )   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | DRAW |      |      |      | CALC |                                       | PASS |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |C-x b |      |       |C-x ` | C-c r|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 | Bspc |      | F+   |       | PgUp |        | Spc  |
 *                                 |      | Syms |------|       |------|  Nums  |      |
 *                                 | Ctrl |      | F-   |       | PgDn |        | Alt  |
 *                                 `--------------------'       `----------------------'
 */
[L_BASE] = LAYOUT_ergodox(
  // Left Hand:
  KC_ESC,         KC_1,  KC_2,   KC_3,   KC_4,      KC_5,    M(M_SCREEN_PREV),
  KC_DQUO,        KC_Q,  KC_W,   KC_E,   KC_R,      KC_T,    KC_MPLY,
  SFT_T(KC_TAB),  KC_A,  KC_S,   KC_D,   KC_F,      KC_G,    /* 2U */
  KC_LPRN,        KC_Z,  KC_X,   KC_C,   KC_V,      KC_B,    OSM(MOD_LGUI),
  K_DRAW,         KC_NO, KC_NO,  KC_NO,  M(M_CALC), /* NA */ /* NA */

  // Left Thumb Cluster:
  /* NA */        M(M_CXB),   KC_NO,
  /* 2U */        /* 2U */    FONT_PLUS,
  CTL_T(KC_BSPC), K_SYMB, FONT_MINUS,

  // Right Hand:
  M(M_SCREEN_NEXT), KC_6,      KC_7,        KC_8,     KC_9,   KC_0,     KC_CAPS,
  KC_MNXT,          KC_Y,      KC_U,        KC_I,     KC_O,   KC_P,     KC_QUOT,
  /* 2U */          KC_H,      KC_J,        KC_K,     KC_L,   KC_SCLN,  SFT_T(KC_ENT),
  OSM(MOD_RGUI),    KC_N,      KC_M,        KC_COMM,  KC_DOT, KC_SLSH,  KC_RPRN,
  /* NA */          /* NA */   M(M_PASSWD), KC_NO,    KC_NO,  KC_NO,    KC_NO,

  // Right Thumb Cluster:
  M(M_CX_TICK), M(M_CCR), /* NA */
  KC_PGUP,      /* 2U */  /* 2U */
  KC_PGDN,      K_NUMB,   ALT_T(KC_SPC)
),

/* Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | RESET   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   \  |   `  |   |  |   +  |   =  | V-DN |           | V-UP |   _  |   -  |   ~  |   [  |   ]  |   `    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    (    |   !  |   @  |   #  |   $  |   %  |------|           |------|   ^  |   &  |   *  |   {  |   }  |   )    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |   <  |   >  |        |
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
  RESET,   KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,
  KC_TRNS, KC_BSLASH,  KC_GRAVE, KC_PIPE,  KC_PLUS,  KC_EQUAL,   KC_VOLD,
  KC_LPRN, KC_EXLM,    KC_AT,    KC_HASH,  KC_DLR,   KC_PERCENT, /* 2U */
  KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_DQUO,
  KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  /* NA */  /* NA */

  // Left Thumb Cluster:
  /* NA */ KC_TRNS, KC_TRNS,
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_VOLU, KC_UNDS, KC_MINUS, KC_TILD, KC_LBRC, KC_RBRC, KC_GRAVE,
  /* 2U */ KC_CIRC, KC_AMPR,  KC_ASTR, KC_LCBR, KC_RCBR, KC_RPRN,
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

/* Function Keys Layer:
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | F11    |  F1  |  F2  |  F3  |  F4  |  F5  |------|           |------|  F6  |   F7 |  F8  |  F9  | F10  |    F12 |
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
[L_FKEYS] = LAYOUT_ergodox(
  // Left Hand:
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* NA */ /* NA */

  // Left Thumb Cluster:
  /* NA */ KC_TRNS, KC_TRNS,
  /* 2U */ /* 2U */ KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  /* 2U */  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  /* NA */  /* NA */ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

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
 * |        |      |      |      |      |      |      |           |      | Home | PgDn | PgUp | End  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      | B-1  |  B-2 |------|           |------| Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | M-L  | M-D  | M-U  | M-R  | B-3  |        |
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
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* NA */ /* NA */

  // Left Thumb Cluster:
  /* NA */ KC_TRNS, KC_TRNS,
  /* 2U */ /* 2U */ KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,

  // Right Hand:
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_TRNS, KC_TRNS,
  /* 2U */  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  KC_BTN3, KC_TRNS,
  /* NA */  /* NA */ KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,

  // Right Thumb Cluster:
  KC_TRNS, KC_TRNS, /* NA */
  KC_TRNS, /* 2U */ /* 2U */
  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Drawing
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Pen 1  |      |      |      |      |      |Erase |           |      |      |      |      |      |      | Clear  |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Pen 2  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Pen 3  |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Pen 4  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
  KC_LSHIFT,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   LALT(KC_LCTRL),
  KC_LCTRL,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
  LSFT(KC_LCTRL), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   /* 2U */
  KC_LALT,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
  K_DRAW,         KC_NO, KC_NO, KC_NO, KC_NO, /* NA */ /* NA */

  // Left Thumb Cluster:
  KC_NO, KC_NO,     /* NA */
  /* 2U */ /* 2U */ KC_NO,
  KC_NO, KC_NO,     KC_NO,

  // Right Hand:
  KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, LSFT(KC_F9),
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
  case M_CX_TICK:
    return MACRODOWN(D(LCTL), T(X), U(LCTL), T(GRAVE), END);
  case M_SCREEN_PREV:
    return MACRODOWN(D(LGUI), T(S), U(LGUI), T(H), END);
  case M_SCREEN_NEXT:
    return MACRODOWN(D(LGUI), T(S), U(LGUI), T(L), END);
  };

  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /*
     * Symbols key and Numbers key.
     *
     * If the Numbers key is held down first and then the Symbols key is
     * held down, use the Function Keys layer.
     *
     * If the Symbols key is held down first and then the Numbers key is
     * held down, use the Movement Keys layer.
     *
     */
  case K_SYMB:
    if (record->event.pressed) {
      g_keystatus_sym = true;
      layer_on(L_SYMB);
      if (g_keystatus_num) layer_on(L_FKEYS);
    } else {
      g_keystatus_sym = false;
      layer_off(L_FKEYS);
      layer_off(L_MOVEMENT);
      if (!g_keystatus_num) layer_off(L_SYMB);
    }
    return false;

  case K_NUMB:
    if (record->event.pressed) {
      g_keystatus_num = true;
      layer_on(L_SYMB);
      layer_on(L_NUMBERS);
      if (g_keystatus_sym) layer_on(L_MOVEMENT);
    } else {
      g_keystatus_num = false;
      if (!g_keystatus_sym) layer_off(L_SYMB);
      layer_off(L_NUMBERS);
      layer_off(L_FKEYS);
      layer_off(L_MOVEMENT);
    }
    return false;

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
  g_keystatus_sym = false;
  g_keystatus_num = false;
  g_draw_mode     = false;
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  switch (layer) {
  case 3:
    ergodox_right_led_1_on();
    break;
  case 4:
    ergodox_right_led_2_on();
    break;
  case 5:
    ergodox_right_led_3_on();
    break;
  case 6:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
  default:
    // none
    break;
  }
};
