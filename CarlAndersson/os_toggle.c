#include "os_toggle.h"

os_type_t os_type = MACOS;

bool process_os_toggle(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case OSTOGG_SHOW:
            switch (os_type){
                case MACOS:
                    SEND_STRING("MACOS");
                    return false;
                case WINDOWS:
                    SEND_STRING("WINDOWS");
                    return false;
                case LINUX:
                    SEND_STRING("LINUX");
                    return false;
            }
        case OSTOGG_MACOS:
            os_type = MACOS;
            return false;
        case OSTOGG_WINDOWS:
            os_type = WINDOWS;
            return false;
        case OSTOGG_LINUX:
            os_type = LINUX;
            return false;
        default:
            return true;
    }
}
