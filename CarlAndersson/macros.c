#include "macros.h"

extern os_type_t os_type;

bool process_macros(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case MC_UNDO:
            switch (os_type) {
                case MACOS:
                    tap_code16(G(KC_Z));
                    return false;
                case LINUX:
                case WINDOWS:
                    tap_code16(C(KC_Z));
                    return false;
            }
        case MC_CUT:
            switch (os_type) {
                    case MACOS:
                        tap_code16(G(KC_X));
                        return false;
                    case LINUX:
                    case WINDOWS:
                        tap_code16(C(KC_X));
                        return false;
                }
        case MC_COPY:
            switch (os_type) {
                    case MACOS:
                        tap_code16(G(KC_C));
                        return false;
                    case LINUX:
                    case WINDOWS:
                        tap_code16(C(KC_C));
                        return false;
                }
        case MC_PASTE:
            switch (os_type) {
                    case MACOS:
                        tap_code16(G(KC_V));
                        return false;
                    case LINUX:
                    case WINDOWS:
                        tap_code16(C(KC_V));
                        return false;
                }
        case MC_COMMENT:
            switch (os_type) {
                case MACOS:
                    tap_code16(G(KC_SLSH));
                    return false;
                case LINUX:
                case WINDOWS:
                    tap_code16(C(KC_SLSH));
                    return false;
            }
        case MC_WORD_LEFT:
            switch (os_type) {
                case MACOS:
                    tap_code16(A(KC_LEFT));
                    return false;
                case LINUX:
                case WINDOWS:
                    tap_code16(C(KC_LEFT));
                    return false;
            }
        case MC_WORD_RIGHT:
            switch (os_type) {
                case MACOS:
                    tap_code16(A(KC_RIGHT));
                    return false;
                case LINUX:
                case WINDOWS:
                    tap_code16(C(KC_RIGHT));
                    return false;
            }
        case MC_LINE_START:
            switch (os_type) {
                case MACOS:
                    tap_code16(G(KC_LEFT));
                    return false;
                case LINUX:
                case WINDOWS:
                    tap_code16(KC_HOME);
                    return false;
            }
        case MC_LINE_END:
            switch (os_type) {
                case MACOS:
                    tap_code16(G(KC_RIGHT));
                    return false;
                case LINUX:
                case WINDOWS:
                    tap_code16(KC_END);
                    return false;
            }
        case MC_INDENT:
            switch (os_type) {
                case MACOS:
                    tap_code16(G(KC_RBRC));
                    return false;
                case LINUX:
                case WINDOWS:
                    tap_code16(C(KC_RBRC));
                    return false;
            }
        case MC_DEDENT:
            switch (os_type) {
                case MACOS:
                    tap_code16(G(KC_LBRC));
                    return false;
                case LINUX:
                case WINDOWS:
                    tap_code16(C(KC_LBRC));
                    return false;
            }
        default:
            return true;
    }
}