#pragma once
#include QMK_KEYBOARD_H
#include "keycodes.h"

#ifdef USERSPACE_ONESHOTS_ENABLE
    #include "oneshot.h"
#endif



bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
