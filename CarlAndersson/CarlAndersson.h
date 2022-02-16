#pragma once
#include QMK_KEYBOARD_H

#ifdef USERSPACE_ONESHOTS_ENABLE
    #include "oneshot.h"
#endif

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,
#ifdef USERSPACE_ONESHOTS_ENABLE
    OS_SHFT,
    OS_ALT,
    OS_CTRL,
    OS_CMD,
    OS_HOLD,
#endif
    KEYMAP_SAFE_RANGE
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
