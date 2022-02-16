#include "CarlAndersson.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_record_keymap(keycode, record)
#ifdef USERSPACE_ONESHOTS_ENABLE
        && process_oneshots(keycode, record)
#endif
#ifdef USERSPACE_CAPSWORD_ENABLE
        && process_capsword(keycode, record)
#endif
#ifdef USERSPACE_REPEATKEY_ENABLE
        && process_repeatkey(keycode, record)
#endif
        && true)) {
            return false;
        }
    return true;
}