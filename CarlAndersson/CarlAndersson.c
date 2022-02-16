#include "CarlAndersson.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

#ifdef USERSPACE_ONESHOTS_ENABLE
    oneshot_state os_ctrl_state = os_up_unqueued;
    oneshot_state os_shft_state = os_up_unqueued;
    oneshot_state os_alt_state = os_up_unqueued;
    oneshot_state os_cmd_state = os_up_unqueued;
    bool oneshot_hold = false;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    #ifdef USERSPACE_ONESHOTS_ENABLE
    case OS_HOLD:
        oneshot_hold = !oneshot_hold;
        return false;
    #endif
    }
#ifdef USERSPACE_ONESHOTS_ENABLE
    update_single_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT, OS_HOLD,
        keycode, record
    );
    update_single_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL, OS_HOLD,
        keycode, record
    );
    update_single_oneshot(
        &os_alt_state, KC_LALT, OS_ALT, OS_HOLD,
        keycode, record
    );
    update_single_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD, OS_HOLD,
        keycode, record
    );
#endif
return process_record_keymap(keycode, record);
}