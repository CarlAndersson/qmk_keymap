#pragma once

#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "capsword.h"

bool process_capitalize(uint16_t keycode, keyrecord_t *record);

bool is_capitalize_ignored(uint16_t keycode);
