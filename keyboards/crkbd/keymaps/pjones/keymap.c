#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#include "ssd1306.h"

/******************************************************************************/
const char* read_logo(void);

/******************************************************************************/
extern keymap_config_t keymap_config;
extern uint8_t is_master;

/******************************************************************************/
bool g_draw_mode = false;
char g_layer_str[24];

/******************************************************************************/
// Numbered only so I remember:
enum {
  L_BASE     = 0,
  L_SYMB     = 1,
  L_NUMBERS  = 2,
  L_MVMT     = 3,
  L_SYMB_ALT = 4,
  L_MEDIA    = 6,
  L_DRAWING  = 7
};

/******************************************************************************/
enum custom_keycodes {
  KC_DRAW = SAFE_RANGE, // can always be here
};

/******************************************************************************/
#define KC______ KC_TRNS
#define KC_XXXXX KC_NO

#define KC_SESC  LSFT_T(KC_ESC)
#define KC_SQUO  RSFT_T(KC_QUOT)
#define KC_FUNC  OSL(L_FUNCKEYS)
#define KC_LGUI  OSM(MOD_LGUI)
#define KC_BSPL1 LT(L_SYMB, KC_BSPC)
#define KC_TABL4 LT(L_SYMB_ALT, KC_TAB)
#define KC_SPCL2 LT(L_NUMBERS, KC_SPC)
#define KC_ENTL6 LT(L_MEDIA, KC_ENT)
#define KC_GUIP  LGUI(KC_P)
#define KC_RESET RESET
#define KC_SINRT LSFT(KC_INSERT)
#define KC_SCRAT LGUI(KC_CIRC)
#define KC_FULLW LGUI(KC_EXLM)
#define KC_FOCUS LGUI(KC_ASTR)
#define KC_SINGW LGUI(LALT(KC_8))

#define KC_GUI_A LGUI_T(KC_A)
#define KC_CTR_F LCTL_T(KC_F)
#define KC_CTR_J RCTL_T(KC_J)
#define KC_GSCLN RGUI_T(KC_SCLN)
#define KC_ALT_G LALT_T(KC_G)
#define KC_ALT_H RALT_T(KC_H)
#define KC_CPLUS LCTL(LSFT(KC_EQL))
#define KC_CMINU LCTL(KC_MINUS)

#define KC_SCRNNXT LGUI(LSFT(KC_0))
#define KC_SCRNSWP LGUI(KC_BSLS)
#define KC_TABPRE  LCTL(KC_LBRC)
#define KC_TABNXT  LCTL(KC_RBRC)

#define KC_PEN1 KC_LSHIFT
#define KC_PEN2 KC_LCTRL
#define KC_PEN3 LSFT(KC_LCTRL)
#define KC_PEN4 KC_LALT
#define KC_PENE LALT(KC_LCTRL)
#define KC_PENC LSFT(KC_F9)

/******************************************************************************/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      FULLW,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  CAPS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       SESC, GUI_A,     S,     D, CTR_F, ALT_G,                  ALT_H, CTR_J,     K,     L, GSCLN,  SQUO, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH, SCRAT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                SCRNNXT, TABL4, BSPL1,    SPCL2, ENTL6, TABNXT \
                              //`--------------------'  `--------------------'
  ),

  [L_SYMB] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      SINGW,  BSLS, XXXXX,  PIPE, PLUS,  EQUAL,                   UNDS, MINUS,  TILD,  LBRC,  RBRC, SINRT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN, GRAVE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       DRAW, RESET, XXXXX, XXXXX,  PLUS, EQUAL,                   UNDS, MINUS, XXXXX,  LABK,  RABK, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, TABPRE \
                              //`--------------------'  `--------------------'
  ),

  [L_NUMBERS] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        F11,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,   F12,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       DRAW, XXXXX, XXXXX, XXXXX,  PLUS, EQUAL,                   UNDS, MINUS,  COMM,   DOT,  SLSH, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                SCRNSWP, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [L_MVMT] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX, XXXXX, CPLUS,  PGDN,                   PGUP, CMINU, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   LEFT,  DOWN,    UP, RIGHT, XXXXX, XXXXX, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [L_SYMB_ALT] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX,  LBRC,  RBRC, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX,  LCBR,  RCBR, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX,  LABK,  RABK, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),


  [L_MEDIA] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,  VOLD,  VOLU,  MPRV,  MPLY,  MNXT,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  XXXXX, XXXXX,   DEL,    XXXXX, XXXXX, XXXXX \
                              //`--------------------'  `--------------------'
  ),

  [L_DRAWING] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       PENE,  PEN1,  PEN2,  PEN3,  PEN4,  PENC,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  DRAW,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  XXXXX, XXXXX, XXXXX,    XXXXX, XXXXX, XXXXX \
                              //`--------------------'  `--------------------'
  )
};

/******************************************************************************/
const char* read_layer_state(void) {
  switch(biton32(layer_state)) {
  case L_BASE:
    snprintf(g_layer_str, sizeof(g_layer_str), " ");
    break;

  case L_MVMT:
    snprintf(g_layer_str, sizeof(g_layer_str), "Layer: Movement");
    break;

  case L_SYMB_ALT:
    snprintf(g_layer_str, sizeof(g_layer_str), "Layer: AltSyms");
    break;

  case L_MEDIA:
    snprintf(g_layer_str, sizeof(g_layer_str), "Layer: Media");
    break;

  case L_DRAWING:
    snprintf(g_layer_str, sizeof(g_layer_str), "Layer: Drawing");
    break;

  // These come last because they trigger other layers.
  case L_SYMB:
    snprintf(g_layer_str, sizeof(g_layer_str), "Layer: Symbols");
    break;

  case L_NUMBERS:
    snprintf(g_layer_str, sizeof(g_layer_str), "Layer: Numbers");
    break;

  default:
    snprintf(g_layer_str, sizeof(g_layer_str), "Layer: Unk");
  }

  return g_layer_str;
}

/******************************************************************************/
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

/******************************************************************************/
void matrix_init_user(void) {
  g_draw_mode = false;
  iota_gfx_init(!has_usb());   // turns on the display
}

/******************************************************************************/
void matrix_scan_user(void) {
   iota_gfx_task();
}

/******************************************************************************/
void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    uint8_t leds = host_keyboard_leds();

    if (leds & (1<<USB_LED_CAPS_LOCK)) {
      snprintf(g_layer_str, sizeof(g_layer_str), "C A P S L O C K");
      matrix_write_ln(matrix, g_layer_str);
    } else {
      matrix_write_ln(matrix, read_layer_state());
    }
  } else {
    matrix_write(matrix, read_logo());
  }
}

/******************************************************************************/
void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

/******************************************************************************/
void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

/******************************************************************************/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /*
     * Toggle drawing mode.
     */
  case KC_DRAW:
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
    break;
  }

  return true;
}

/******************************************************************************/
uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, L_SYMB, L_NUMBERS, L_MVMT);
}
