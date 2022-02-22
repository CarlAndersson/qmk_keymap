#include "capsword.h"

__attribute__((weak)) bool is_capsword_shifted(uint16_t keycode) { return false; }
__attribute__((weak)) bool isnt_capsword_shifted(uint16_t keycode) { return false; }
__attribute__((weak)) bool is_capsword_continue(uint16_t keycode) { return false; }
__attribute__((weak)) bool isnt_capsword_continue(uint16_t keycode) { return false; }

static bool is_shifted(uint16_t keycode) {
    if (is_capsword_shifted(keycode)) {return true;}
    if (isnt_capsword_shifted(keycode)) {return false;}
    switch (keycode) {
        case KC_A ... KC_Z:
            return true;
        default:
            return false;
    }
}

static bool is_continue(uint16_t keycode) {
    if (is_capsword_continue(keycode)) {return true;}
    if (isnt_capsword_continue(keycode)) {return false;}
    switch (keycode) {
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:  // normal move to layer keys, e.g. `MO(SYMBOLS)`
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:  // layer taps, e.g. `LT(SYMBOLS, KC_SPACE)`
            return true;
        default:
            return false;
    }
}

static bool capsword_enabled = false;
static bool capsword_shifted = false;

bool process_capsword(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            // Earlier return if this has not been considered tapped yet.
            if (record->tap.count == 0) {
                return true;
            }
            // Get the base tapping keycode of a mod- or layer-tap key.
            keycode &= 0xff;
    }

    if (!capsword_enabled) {
        if (keycode == CAPSWORD && record->event.pressed) {
            capsword_enabled = true;
            return false;
        }
        return true;
    }

    if (!record->event.pressed) {
        return true;
    }

    // caps word is on, and we have a keypress
    if (is_shifted(keycode)) {
        capsword_shifted = true;
        register_code(KC_LSFT);
        return true;
    }
    if (is_continue(keycode)) {
        capsword_shifted = false;
        unregister_code(KC_LSFT);
        return true;
    }
    // all keys which are not shifted or continues are breaking
    capsword_enabled = false;
    if (capsword_shifted) {
        capsword_shifted = false;
        unregister_code(KC_LSFT);
    }
    return true;
}

