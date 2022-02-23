#pragma once

#include QMK_KEYBOARD_H
#include "keycodes.h"

bool process_oneshots(uint16_t keycode, keyrecord_t *record);

// To be implemented by the consumer. Defines keys to cancel oneshot mods.
bool is_oneshot_cancel(uint16_t keycode);

// To be implemented by the consumer. Defines keys to ignore when determining
// whether a oneshot mod has been used. Setting this to modifiers and layer
// change keys allows stacking multiple oneshot modifiers, and carrying them
// between layers.
bool is_oneshot_ignored(uint16_t keycode);
bool isnt_oneshot_ignored(uint16_t keycode);
