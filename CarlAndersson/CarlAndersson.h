#pragma once
#include QMK_KEYBOARD_H
#include "keycodes.h"

#ifdef USERSPACE_ONESHOTS_ENABLE
    #include "oneshot.h"
#endif

#ifdef USERSPACE_CAPITALIZE_ENABLE
    #include "capitalize.h"
#endif

#ifdef USERSPACE_CAPSWORD_ENABLE
    #include "capsword.h"
#endif

#ifdef USERSPACE_REPEATKEY_ENABLE
    #include "repeatkey.h"
#endif

#ifdef USERSPACE_MACROS_ENABLE
    #include "macros.h"
#endif
#include "os_toggle.h"

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
