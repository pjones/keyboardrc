#include "5x6.h"

void led_set_kb(uint8_t usb_led) {
  led_set_user(usb_led);
}

void keyboard_pre_init_kb(void) {
  keyboard_pre_init_user();
};

void matrix_init_kb(void) {
  matrix_init_user();
};
