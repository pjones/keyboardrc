#ifndef KEYBOARDS_ERGODOX_PJONES_CONFIG_H
#define KEYBOARDS_ERGODOX_PJONES_CONFIG_H

#include "../../config.h"
#undef TAPPING_TERM

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY    0

#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TOGGLE          1
#define TAPPING_TERM            100

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 1000

#endif
