#include "oneshot.h"

__attribute__((weak)) bool is_oneshot_ignored(uint16_t keycode) { return false; }
__attribute__((weak)) bool isnt_oneshot_ignored(uint16_t keycode) { return false; }

static bool is_ignored(uint16_t keycode) {
    if (is_oneshot_ignored(keycode)) { return true; }
    if (isnt_oneshot_ignored(keycode)) {return false;}

    switch (keycode) {
        case OS_SHFT:
        case OS_ALT:
        case OS_CTRL:
        case OS_CMD:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:  // normal move to layer keys, e.g. `MO(SYMBOLS)`
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:  // layer taps, e.g. `LT(SYMBOLS, KC_SPACE)`
            return true;
        default:
            return false;
    }
}

static keypress_t keypress_type;

static bool update_single_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t lock,
    uint16_t keycode,
    keyrecord_t *record
) {
    keypress_type = determine_keypress_type(keycode, record);
    if (*state == os_up_used) {
        // we end up here after a one-shot was used, before the keyup event
        unregister_code(mod);
        *state = os_up_unqueued;
    }
    if (keypress_type == KEYPRESS_TAP_KEY_HELD) { return true; }

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
        return false;
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
        return false;
    } else {
        if (record->event.pressed) {
            if (keypress_type == KEYPRESS_TAP_KEY_TAPPED) { keycode = get_tapkey_tap_keycode(keycode); }
            if (is_oneshot_cancel(keycode) && *state == os_up_queued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            } else if (!is_ignored(keycode)) {
                // "normal" key was  pressed, using the one-shot. dont clear here since we need to keep it for this keypress
                switch (*state) {
                case os_up_queued:
                    *state = os_up_used;
                    break;
                case os_down_unused:
                    *state = os_down_used;
                    break;
                default:
                    break;
                }
            }
        } else {
            if (!is_ignored(keycode)) {
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
    return true;
}

static oneshot_state os_ctrl_state = os_up_unqueued;
static oneshot_state os_shft_state = os_up_unqueued;
static oneshot_state os_alt_state = os_up_unqueued;
static oneshot_state os_cmd_state = os_up_unqueued;

bool process_oneshots(uint16_t keycode, keyrecord_t *record) {
    if (!(
        update_single_oneshot(
            &os_shft_state, KC_LSFT, OS_SHFT, OS_HOLD,
            keycode, record
        ) &&
        update_single_oneshot(
            &os_ctrl_state, KC_LCTL, OS_CTRL, OS_HOLD,
            keycode, record
        ) &&
        update_single_oneshot(
            &os_alt_state, KC_LALT, OS_ALT, OS_HOLD,
            keycode, record
        ) &&
        update_single_oneshot(
            &os_cmd_state, KC_LCMD, OS_CMD, OS_HOLD,
            keycode, record
        ) && true)) {
            return false;
        }
    return true;
}