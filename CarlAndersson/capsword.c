#include "capsword.h"

__attribute__((weak)) bool is_capsword_shifted(uint16_t keycode) { return false; }
__attribute__((weak)) bool isnt_capsword_shifted(uint16_t keycode) { return false; }
__attribute__((weak)) bool is_capsword_continue(uint16_t keycode) { return false; }
__attribute__((weak)) bool isnt_capsword_continue(uint16_t keycode) { return false; }
__attribute__((weak)) bool is_capsword_keycode(uint16_t keycode) { return false; }

static bool is_shifted(uint16_t keycode) {
    if (is_capsword_shifted(keycode)) { return true; }
    if (isnt_capsword_shifted(keycode)) { return false; }
    switch (keycode) {
        case KC_A ... KC_Z:
            return true;
        default:
            return false;
    }
}

static bool is_continue(uint16_t keycode) {
    if (is_capsword_continue(keycode)) { return true; }
    if (isnt_capsword_continue(keycode)) { return false; }
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
static keypress_t keypress_type;

bool process_capsword(uint16_t keycode, keyrecord_t *record) {
    keypress_type = determine_keypress_type(keycode, record);
    if (keypress_type == KEYPRESS_TAP_KEY_HELD) { return true; }

    if (!capsword_enabled) {
        if ((keycode == CAPSWORD || is_capsword_keycode(keycode)) && record->event.pressed) {
            capsword_enabled = true;
            return false;
        }
        return true;
    }

    if (!record->event.pressed) {
        return true;
    }

    if (keypress_type == KEYPRESS_TAP_KEY_TAPPED) { keycode = get_tapkey_tap_keycode(keycode); }

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
