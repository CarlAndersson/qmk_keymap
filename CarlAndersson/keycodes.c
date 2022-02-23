#include "keycodes.h"

uint16_t get_tapkey_tap_keycode(uint16_t keycode) { return keycode & 0xff; }

keypress_t determine_keypress_type(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->tap.count > 0) {
                return KEYPRESS_TAP_KEY_TAPPED;
            } else {
                return KEYPRESS_TAP_KEY_HELD;
            }
        default:
            return KEYPRESS_OTHER;
    }
}
