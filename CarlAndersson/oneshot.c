#include "oneshot.h"

void update_single_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t lock,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (*state == os_up_used) {
        // we end up here after a one-shot was used, before the keyup event
        unregister_code(mod);
        *state = os_up_unqueued;
    }
    if (keycode == trigger) {
        if (record->event.pressed) {
            // OS key was pressed
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
        } else {
            // OS key was released
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else if (keycode == lock) {
        if (record->event.pressed) {
            // The lock key was pressed
            switch (*state) {
            case os_down_used:
            case os_down_unused:
            case os_up_queued:
                // states which have the mod active should lock it in place
                *state = os_locked;
                break;
            case os_locked:
                // if it was locked, unlock now
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state == os_up_queued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            } else if (!is_oneshot_ignored_key(keycode)) {
                // "normal" key was  pressed, using the one-shot. dont clear here since we need to keep it for this keypress
                switch (*state) {
                case os_up_queued:
                    *state = os_up_used;
                    break;
                case os_down_unused:
                    *state = os_down_used;
                    break;
                }
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    // still holding the mod, dont go into one-shot after
                    *state = os_down_used;
                    break;
                case os_up_queued:
                    // We end up here if the os key was tapped while another key was held and then released
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
