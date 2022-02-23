#include "capitalize.h"

__attribute__((weak)) bool is_capitalize_ignored(uint16_t keycode) {
    switch (keycode) {
        case KC_SPACE:
            return true;
    }
    return false;
}

__attribute__((weak)) bool is_capitalize_keycode(uint16_t keycode) { return false; }

static bool capitalize_next = false;
static bool capitalized_previous = false;
static uint16_t capsword_timer = 0;

bool process_capitalize(uint16_t keycode, keyrecord_t *record) {
    if (capitalized_previous) {
        // There's an unhandled edge-case here:
        //      "CAPITALIZE -> NON-IGNORED-KEY -> SHIFT"
        // will end up deactivating shift?
        unregister_code(KC_LSFT);
        capitalized_previous = false;
    }
    if (determine_keypress_type(keycode, record) == KEYPRESS_TAP_KEY_HELD) { return true; }

    if ((keycode == CAPITALIZE || is_capitalize_keycode(keycode)) && record->event.pressed) {
        if (capsword_timer == 0) {
            // First press for capitalize key
            capsword_timer = record->event.time;
            capitalize_next = true;
        } else if (timer_elapsed(capsword_timer) < TAPPING_TERM) {
            // Second rapid press -> deactivate capitalize and activate capsword
            capitalize_next = false;
            capsword_timer = 0;
            process_capsword(CAPSWORD, record);
        }
        // If none of the above is true, we have two slow presses.
        // This should just keep the capitalize on, so we don't need to do anything.
        return false;
    }

    if (!capitalize_next) { return true; }  // Capitalization not active
    if (!record->event.pressed) { return true; }  // Not a keypress

    if (is_capitalize_ignored(keycode)) { return true; }  // This key is ignored, don't consume state

    // We have a keypress of a non-ignored key -> activate shift and deactivate capitalize
    register_code(KC_LSFT);
    capsword_timer = 0;
    capitalized_previous = true;
    capitalize_next = false;
    return true;
}