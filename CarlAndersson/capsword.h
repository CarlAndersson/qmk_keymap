#pragma once

#include QMK_KEYBOARD_H
#include "keycodes.h"

bool process_capsword(uint16_t keycode, keyrecord_t* record);

bool is_capsword_shifted(uint16_t keycode);
bool isnt_capsword_shifted(uint16_t keycode);
bool is_capsword_continue(uint16_t keycode);
bool isnt_capsword_continue(uint16_t keycode);