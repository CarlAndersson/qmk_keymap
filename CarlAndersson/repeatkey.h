#pragma once

#include QMK_KEYBOARD_H
#include "keycodes.h"

bool is_repeatkey_ignored(uint16_t keycode);
bool process_repeatkey(uint16_t keycode, keyrecord_t* record);