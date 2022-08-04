#pragma once

#include QMK_KEYBOARD_H

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,
    OSTOGG_MACOS,
    OSTOGG_WINDOWS,
    OSTOGG_LINUX,
    OSTOGG_SHOW,
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
#ifdef USERSPACE_MACROS_ENABLE
    MC_UNDO,
    MC_CUT,
    MC_COPY,
    MC_PASTE,
    MC_COMMENT,
    MC_WORD_LEFT,
    MC_WORD_RIGHT,
    MC_LINE_START,
    MC_LINE_END,
    MC_INDENT,
    MC_DEDENT,
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
