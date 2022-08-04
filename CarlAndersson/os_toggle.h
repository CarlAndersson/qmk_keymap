#pragma once

#include QMK_KEYBOARD_H
#include "keycodes.h"

typedef enum {
    MACOS,
    WINDOWS,
    LINUX,
} os_type_t;

bool process_os_toggle(uint16_t keycode, keyrecord_t *record);
