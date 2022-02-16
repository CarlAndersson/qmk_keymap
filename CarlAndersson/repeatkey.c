#include "repeatkey.h"

uint16_t last_keycode = KC_NO;
uint8_t last_mod_state = 0;

void send_keycode(uint16_t keycode, uint8_t mod_state, keyrecord_t *record) {
    if (record->event.pressed) {
        register_mods(mod_state);
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
        unregister_mods(mod_state);
    }
}

void set_last_key(uint16_t keycode) {
    last_keycode = keycode;
    last_mod_state = get_mods();
}

__attribute__((weak)) bool is_repeatkey_ignored(uint16_t keycode) { return false; }
bool is_ignored(uint16_t keycode) {
    if (is_repeatkey_ignored(keycode)) { return true; }
    switch (keycode) {
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:  // normal move to layer keys, e.g. `MO(SYMBOLS)`
            return true;
    }
    return false;
}

bool process_repeatkey(uint16_t keycode, keyrecord_t *record) {
    if (keycode == REPEAT) {
        send_keycode(last_keycode, last_mod_state, record);
        return false;
    }
    if (!record->event.pressed) { return true; }
    if (is_ignored(keycode)) { return true; }

    set_last_key(keycode);
    return true;
}