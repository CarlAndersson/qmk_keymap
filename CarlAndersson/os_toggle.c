#include "os_toggle.h"

typedef union {
    uint32_t raw;
    struct {
        bool is_macos :1;
        bool is_windows :1;
    };
} user_config_t;
user_config_t user_config;

os_type_t get_os_type(void) {
    if (user_config.is_macos) {
        return MACOS;
    } else if (user_config.is_windows) {
        return WINDOWS;
    } else {
        return LINUX;
    }
}

void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    user_config.raw = 0;
    user_config.is_macos = false;
    user_config.is_windows = false;
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
}


bool process_os_toggle(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case OSTOGG_SHOW:
            switch (get_os_type()){
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
            user_config.is_macos = true;
            user_config.is_windows = false;
            eeconfig_update_user(user_config.raw);
            return false;
        case OSTOGG_WINDOWS:
            user_config.is_macos = false;
            user_config.is_windows = true;
            eeconfig_update_user(user_config.raw);
            return false;
        case OSTOGG_LINUX:
            user_config.is_macos = false;
            user_config.is_windows = false;
            eeconfig_update_user(user_config.raw);
            return false;
        default:
            return true;
    }
}
