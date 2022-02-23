#pragma once

#include QMK_KEYBOARD_H

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,
#ifdef USERSPACE_ONESHOTS_ENABLE
    OS_SHFT,
    OS_ALT,
    OS_CTRL,
    OS_CMD,
#endif
#ifdef USERSPACE_CAPSWORD_ENABLE
    CAPSWORD,
#endif
#ifdef USERSPACE_CAPITALIZE_ENABLE
    CAPITALIZE,
#endif
#ifdef USERSPACE_REPEATKEY_ENABLE
    REPEAT,
#endif
    KEYMAP_SAFE_RANGE
};

typedef enum {
    KEYPRESS_OTHER,
    KEYPRESS_TAP_KEY_HELD,
    KEYPRESS_TAP_KEY_TAPPED,
} keypress_t;

keypress_t determine_keypress_type(uint16_t keycode, keyrecord_t *record);
uint16_t get_tapkey_tap_keycode(uint16_t keycode);
