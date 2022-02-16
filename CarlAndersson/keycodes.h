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
#ifdef USERSPACE_CAPSWORD_ENABLE
    CAPSWORD,
#endif
#ifdef USERSPACE_REPEATKEY_ENABLE
    REPEAT,
#endif
    KEYMAP_SAFE_RANGE
};
#endif