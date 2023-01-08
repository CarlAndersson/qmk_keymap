#include "CarlAndersson.h"

enum layers {
    BASE = 0,
    SYMBOLS,
    NAVIGATE,
    NUMBERS,
    FUNCTIONS,
    SYSTEM,
};

#define SE_ARNG RALT(KC_W)
#define SE_ADIA RALT(KC_A)
#define SE_ODIA RALT(KC_O)

#define LA_NAVIGATE MO(NAVIGATE)
#define LA_SYMBOLS MO(SYMBOLS)
#define LA_FUNCTIONS MO(FUNCTIONS)
#define LA_SYSTEM MO(SYSTEM)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,                                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_MINS, SE_ARNG,
      KC_BSPC, KC_A,   KC_R,   KC_S,   KC_T,   KC_D,                                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    SE_ADIA,
      KC_TAB,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,      _______, _______,      _______, _______, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, SE_ODIA,
                            _______, _______,  LA_NAVIGATE, KC_LSFT, _______,      _______,  KC_SPACE,   LA_SYMBOLS,  _______, _______
    ),
    [NAVIGATE] = LAYOUT(
      _______, KC_ENT,  KC_TAB,  KC_SPC,  KC_DEL,   KC_NO,                                              KC_NO,  MC_WORD_LEFT, KC_NO,    MC_WORD_RIGHT, KC_NO,       _______,
      _______, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,   KC_NO,                                      MC_LINE_START,  KC_LEFT,      KC_UP,    KC_RGHT,       KC_NO,   MC_LINE_END,
      _______, MC_UNDO, MC_CUT,  MC_COPY, MC_PASTE, MC_COMMENT, _______, _______,     _______, _______, KC_NO,  MC_DEDENT,    KC_DOWN,  MC_INDENT,     KC_NO,       _______,
                                     _______, _______, _______, _______, _______,     _______, _______,  _______,  _______, _______
    ),
    [SYMBOLS] = LAYOUT(
      _______, KC_QUES,  KC_EXLM, KC_CIRC, KC_PERC, KC_TILD,                                         _______, KC_LCBR, KC_BSLS, KC_SLSH, KC_MINS,   KC_NO,
      _______, KC_AT,    KC_PIPE, KC_AMPR, KC_HASH, KC_DLR,                                          _______, KC_LPRN, KC_EQL,  KC_ASTR, KC_PLUS,   LA_FUNCTIONS,
      _______, _______,  _______, _______, _______, _______, _______, _______,     _______, _______, _______, KC_LBRC, KC_LT,   KC_GT,   KC_GRAVE,  LA_SYSTEM,
                                  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),
    [NUMBERS] = LAYOUT(
      _______, _______, KC_4,    KC_5,    KC_6,    _______,                                                KC_J,  _______, _______, _______, _______, _______,
      _______, KC_0,    KC_1,    KC_2,    KC_3,    _______,                                                KC_E,  _______, _______, _______, _______, _______,
      _______, _______, KC_7,    KC_8,    KC_9,    _______,  _______, _______,         _______, _______, _______, _______, KC_COMM, KC_DOT,  _______, _______,
                                 _______, _______, _______,  _______,  _______,        _______, _______, _______, _______, _______
    ),
    [FUNCTIONS] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                                         _______, KC_VOLU, _______, _______, _______, _______,
      _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,                                         _______, KC_VOLD, KC_MPLY, _______, _______, _______,
      _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,     _______, _______, _______, KC_MUTE, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),
   [SYSTEM] = LAYOUT(
      _______, OSTOGG_SHOW, OSTOGG_WINDOWS, OSTOGG_MACOS, OSTOGG_LINUX,   _______,                     _______,  _______,  _______,  _______,  _______,  _______,
      _______, _______,   _______, _______, _______, _______,                                         _______,  _______,  _______,  _______,  _______,  _______,
      _______, _______,   _______, _______, _______, _______, _______, _______,     _______, _______, _______,  _______,  _______,  _______,  _______,  _______,
                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),
    // [_LAYERINDEX] = LAYOUT(
    //   _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
    //   _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
    //   _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
    //                              _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    // ),
};


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, SYMBOLS, NAVIGATE, NUMBERS);

    return state;
}

const key_override_t shift_comma_2_semicolon = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t shift_dot_2_colon = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t shift_quote_2_doublequote = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_DQUO);
const key_override_t shift_lparen_2_rparen = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_RPRN);
const key_override_t shift_lbracket_2_rbracket = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RBRC);
const key_override_t shift_lbrace_2_rbrace = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR);

const key_override_t **key_overrides = (const key_override_t *[]){
    &shift_comma_2_semicolon,
    &shift_dot_2_colon,
    &shift_quote_2_doublequote,
    &shift_lparen_2_rparen,
    &shift_lbracket_2_rbracket,
    &shift_lbrace_2_rbrace,
    NULL // Null terminate the array of overrides!

};

// const uint16_t PROGMEM combo_upright[] = {KC_U, KC_Y, COMBO_END};
// const uint16_t PROGMEM combo_downright[] = {KC_COMM, KC_DOT, COMBO_END};
// const uint16_t PROGMEM combo_upleft[] = {KC_W, KC_F, COMBO_END};
// const uint16_t PROGMEM combo_downleft[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_center[] = {KC_D, KC_H, COMBO_END};
// const uint16_t PROGMEM combo_leftthumb[] = {LA_NAVIGATE, KC_SPACE, COMBO_END};
// const uint16_t PROGMEM combo_rightthumb[] = {KC_SPC, LA_SYMBOLS, COMBO_END};
// const uint16_t PROGMEM combo_dualthumb[] = {KC_SPACE, KC_BSPC, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
    // COMBO(combo_upright, KC_TAB),
    // COMBO(combo_downright, CAPITALIZE),
    // COMBO(combo_upleft, KC_ESC),
    // COMBO(combo_downleft, KC_NO),
    COMBO(combo_center, CAPSWORD),
    // COMBO(combo_leftthumb, LA_NUMBERS),
    // COMBO(combo_rightthumb, KC_NO),
    // COMBO(combo_dualthumb, KC_ENTER),
};


// bool is_capitalize_ignored(uint16_t keycode) {
//     switch (keycode) {
//         case SPACE_NUMBERS:
//             return true;
//         default:
//             return false;
//     }
// }

// bool is_capitalize_keycode(uint16_t keycode) {
//     if (keycode == CAPITALIZE_SYMBOLS) {
//         return true;
//     }
//     return false;
// }

bool is_capsword_shifted(uint16_t keycode) {
    switch (keycode) {
        case KC_MINS:
            return true;
        default:
            return false;
    }
}

bool isnt_capsword_continue(uint16_t keycode) {
    switch (keycode) {
        case KC_ESC:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_cancel(uint16_t keycode) {
    switch (keycode) {
        case LA_NAVIGATE:
            return true;
        default:
            return false;
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}
