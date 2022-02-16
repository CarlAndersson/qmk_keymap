#ifndef USER_KEYCODES
#define USER_KEYCODES
enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,
#ifdef USERSPACE_ONESHOTS_ENABLE
    OS_SHFT,
    OS_ALT,
    OS_CTRL,
    OS_CMD,
    OS_HOLD,
#endif
    KEYMAP_SAFE_RANGE
};
#endif