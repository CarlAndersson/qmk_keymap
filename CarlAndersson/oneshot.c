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

// The states a oneshot key can be in
typedef enum {
    ONESHOT_STATE_INACTIVE,
    ONESHOT_STATE_UP_UNUSED,
    ONESHOT_STATE_UP_USED,
    ONESHOT_STATE_DOWN_UNUSED,
    ONESHOT_STATE_DOWN_USED,
    ONESHOT_STATE_LOCKED,
} oneshot_state_t;

// Represents a one-shot key
typedef struct {
    oneshot_state_t state;
    uint16_t modifier;
    uint16_t trigger;
    uint16_t timer;
} oneshot_record_t;

// The events that are of interest for the one-shots
typedef enum {
    ONESHOT_EVENT_TRIGGER_DOWN,
    ONESHOT_EVENT_TRIGGER_UP,
    ONESHOT_EVENT_OTHER_DOWN,
    ONESHOT_EVENT_OTHER_UP,
    ONESHOT_EVENT_CANCEL,
    ONESHOT_EVENT_IGNORE,
} oneshot_event_t;

static oneshot_event_t event_type;

static oneshot_event_t determine_event_type(uint16_t keycode, keyrecord_t *record, oneshot_record_t *oneshot) {
    if (keycode == oneshot->trigger) {
        if (record->event.pressed) { return ONESHOT_EVENT_TRIGGER_DOWN; }
        else { return ONESHOT_EVENT_TRIGGER_UP; }
    }
    // It seems like the most natural experience is to check cancel keys on "original" keycodes but
    // ignore keys on detapped keys. This makes sense since layer keys will often be cancel keys,
    // but tapped layer-taps should not be ignored.
    if (is_oneshot_cancel(keycode) && record->event.pressed) { return ONESHOT_EVENT_CANCEL; }

    if (determine_keypress_type(keycode, record) == KEYPRESS_TAP_KEY_TAPPED) {
        keycode = get_tapkey_tap_keycode(keycode);
    }

    if (is_ignored(keycode)) { return ONESHOT_EVENT_IGNORE; }
    if (record->event.pressed) { return ONESHOT_EVENT_OTHER_DOWN; }
    else { return ONESHOT_EVENT_OTHER_UP; }
}

static bool update_oneshot(uint16_t keycode, keyrecord_t *record, oneshot_record_t *oneshot) {
    switch (oneshot->state) {
        case ONESHOT_STATE_UP_USED:
            // This means the oneshot was consumed in the previous event
            unregister_code(oneshot->modifier);
            oneshot->state = ONESHOT_STATE_INACTIVE;
            break;
        case ONESHOT_STATE_UP_UNUSED:
        // case ONESHOT_STATE_LOCKED:
            // Oneshot been on for too long without interaction
            if (timer_elapsed(oneshot->timer) > ONESHOT_TIMEOUT) {
                oneshot->state = ONESHOT_STATE_INACTIVE;
                unregister_code(oneshot->modifier);
            }
        default:;
    }

    event_type = determine_event_type(keycode, record, oneshot);
    switch (event_type) {
        case ONESHOT_EVENT_TRIGGER_DOWN:
            switch (oneshot->state) {
                case ONESHOT_STATE_INACTIVE:
                    // First press of one-shot trigger
                    oneshot->state = ONESHOT_STATE_DOWN_UNUSED;
                    oneshot->timer = record->event.time;
                    register_code(oneshot->modifier);
                    break;
                case ONESHOT_STATE_UP_UNUSED:
                    // Multiple repeated trigger presses
                    if (timer_elapsed(oneshot->timer) < TAPPING_TERM) {
                        oneshot->state = ONESHOT_STATE_LOCKED;
                    }
                    oneshot->timer = record->event.time;
                    break;
                default:;
            }
            return false;  // case ONESHOT_EVENT_TRIGGER_DOWN
        case ONESHOT_EVENT_TRIGGER_UP:
            switch (oneshot->state) {
                case ONESHOT_STATE_DOWN_UNUSED:
                    // Pressed and realeased trigger without other keys
                    oneshot->state = ONESHOT_STATE_UP_UNUSED;
                    oneshot->timer = record->event.time;
                    break;
                case ONESHOT_STATE_DOWN_USED:
                    // Pressed and released trigger after using other keys
                    oneshot->timer = 0;
                    oneshot->state = ONESHOT_STATE_INACTIVE;
                    unregister_code(oneshot->modifier);
                    break;
                default:;
            }
            return false;  // case ONESHOT_EVENT_TRIGGER_UP
        case ONESHOT_EVENT_OTHER_DOWN:
            switch (oneshot->state) {
                case ONESHOT_STATE_DOWN_UNUSED:
                    // Other key pressed while holding trigger
                    oneshot->state = ONESHOT_STATE_DOWN_USED;
                    oneshot->timer = 0;
                    break;
                case ONESHOT_STATE_UP_UNUSED:
                    // Other key pressed in one-shot mode. Prepare consume at next event.
                    oneshot->state = ONESHOT_STATE_UP_USED;
                    oneshot->timer = 0;
                    break;
                case ONESHOT_STATE_LOCKED:
                    // Update use time stamp for locked modifier
                    oneshot->timer = record->event.time;
                    break;
                default:;
            }
            return true;  // case ONESHOT_EVENT_OTHER_DOWN
        case ONESHOT_EVENT_CANCEL:
            switch (oneshot->state) {
                case ONESHOT_STATE_UP_UNUSED:
                case ONESHOT_STATE_LOCKED:
                    unregister_code(oneshot->modifier);
                    oneshot->state = ONESHOT_STATE_INACTIVE;
                    oneshot->timer = 0;
                    break;
                default:;
            }
            return true;  // case ONESHOT_EVENT_CANCEL
        case ONESHOT_EVENT_OTHER_UP:
        case ONESHOT_EVENT_IGNORE:
            oneshot->timer = record->event.time;
            return true;  // case ONESHOT_EVENT_OTHER_UP, ONESHOT_EVENT_IGNORED
    }
    return true;  // Satisfying the compiler
}


static oneshot_record_t os_shift_record = {
    .state = ONESHOT_STATE_INACTIVE,
    .modifier = KC_LSFT,
    .trigger = OS_SHFT,
    .timer = 0
};
static oneshot_record_t os_ctrl_record = {
    .state = ONESHOT_STATE_INACTIVE,
    .modifier = KC_LCTL,
    .trigger = OS_CTRL,
    .timer = 0
};
static oneshot_record_t os_alt_record = {
    .state = ONESHOT_STATE_INACTIVE,
    .modifier = KC_LALT,
    .trigger = OS_ALT,
    .timer = 0
};
static oneshot_record_t os_cmd_record = {
    .state = ONESHOT_STATE_INACTIVE,
    .modifier = KC_LCMD,
    .trigger = OS_CMD,
    .timer = 0
};

bool process_oneshots(uint16_t keycode, keyrecord_t *record) {
    if (!(update_oneshot(keycode, record, &os_shift_record)
        && update_oneshot(keycode, record, &os_ctrl_record)
        && update_oneshot(keycode, record, &os_alt_record)
        && update_oneshot(keycode, record, &os_cmd_record)
        && true)) {
            return false;
        }
    return true;
}
