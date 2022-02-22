#pragma once

#include QMK_KEYBOARD_H
#include "keycodes.h"

// Represents the states a oneshot key can be in
typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_up_used,
    os_down_unused,
    os_down_used,
    os_locked,
} oneshot_state;

bool process_oneshots(uint16_t keycode, keyrecord_t *record);


// To be implemented by the consumer. Defines keys to cancel oneshot mods.
bool is_oneshot_cancel(uint16_t keycode);

// To be implemented by the consumer. Defines keys to ignore when determining
// whether a oneshot mod has been used. Setting this to modifiers and layer
// change keys allows stacking multiple oneshot modifiers, and carrying them
// between layers.
bool is_oneshot_ignored(uint16_t keycode);
bool isnt_oneshot_ignored(uint16_t keycode);
