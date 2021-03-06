#include "CarlAndersson.h"

enum layers {
    BASE = 0,
    SYMBOLS,
    NAVIGATE,
    NUMBERS,
    FUNCTION,
};

#define MC_COPY LGUI(KC_C)
#define MC_PSTE LGUI(KC_V)
#define MC_CUT LGUI(KC_X)
#define MC_UNDO LGUI(KC_Z)
#define MC_CMNT LGUI(KC_SLSH)

#define SE_ARNG LALT(KC_W)
#define SE_ADIA LALT(KC_A)
#define SE_ODIA LALT(KC_O)

#define LA_NAVIGATE MO(NAVIGATE)
#define LA_SYMBOLS MO(SYMBOLS)
#define LA_NUMBERS MO(NUMBERS)

#define SPACE_NUMBERS LT(NUMBERS, KC_SPACE)
#define BACKSPACE_SYMBOLS LT(SYMBOLS, KC_BSPC)
#define CAPITALIZE_FUNCTIONS LT(FUNCTION, CAPITALIZE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
      _______, KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,                                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_MINS, _______,
      _______, KC_A,   KC_R,   KC_S,   KC_T,   KC_D,                                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______,
      _______, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,      _______, _______,      _______, _______, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, _______,
                            _______, _______,  LA_NAVIGATE, SPACE_NUMBERS, _______,      _______, BACKSPACE_SYMBOLS, CAPITALIZE_FUNCTIONS,  _______, _______
    ),

    [NUMBERS] = LAYOUT(
      _______, KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO,                                                KC_J,    KC_SLSH, KC_BSLS, KC_ASTR, KC_NO,   _______,
      _______, KC_0,    KC_4,    KC_5,    KC_6,    KC_LABK,                                              KC_RABK, KC_MINS, KC_EQL,  KC_PLUS, KC_CIRC, _______,
      _______, KC_NO,   KC_1,    KC_2,    KC_3,    KC_NO,    _______, _______,         _______, _______, KC_NO,   KC_NO,   KC_COMM, KC_DOT,  KC_GRAVE,   _______,
                                 _______, _______, _______,  _______,  _______,         _______, _______, _______, _______, _______
    ),
    [NAVIGATE] = LAYOUT(
      _______, KC_ENT,  KC_TAB,  KC_SPC,  KC_BSPC, KC_DEL,                                          KC_NO,   KC_NO,       KC_NO,    KC_NO,    KC_BSPC, _______,
      _______, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_NO,                                           KC_NO,   KC_LEFT,     KC_UP,  KC_RGHT,    KC_NO, _______,
      _______, MC_UNDO, MC_CUT,  MC_COPY, MC_PSTE, MC_CMNT, _______, _______,     _______, _______, KC_NO,   G(KC_LBRC),  KC_DOWN,  G(KC_RBRC),KC_NO, _______,
                                 _______, _______, _______, _______, _______,     _______, _______,  _______,  _______, _______
    ),
    [SYMBOLS] = LAYOUT(
      _______, KC_NO,   KC_LCBR, KC_RCBR, KC_PERC, KC_NO,                                           KC_NO,   KC_PIPE, KC_AMPR, SE_ARNG, SE_ADIA, _______,
      _______, KC_AT,   KC_LPRN, KC_RPRN, KC_HASH, KC_DLR,                                          KC_NO,   KC_TILD, KC_QUES, KC_EXLM, SE_ODIA, _______,
      _______, KC_NO,   KC_LBRC, KC_RBRC, KC_NO,   KC_NO,   _______, _______,     _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______,
                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),
   [FUNCTION] = LAYOUT(
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______,                                         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
      _______, KC_NO,   KC_VOLD, KC_MUTE, KC_VOLU, _______,                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______,     _______, _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______,
                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),

    // [_LAYERINDEX] = LAYOUT(
    //   _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
    //   _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
    //   _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
    //                              _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    // ),
};

// layer_state_t layer_state_set_user(layer_state_t state) {
    // state = update_tri_layer_state(state, SYMBOLS, NUMBERS, FUNCTION);
    // return state;
// }

const key_override_t shift_comma_2_semicolon_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t shift_dot_2_colon_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
// const key_override_t shift_quote_2_slash_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_SLSH);

const key_override_t **key_overrides = (const key_override_t *[]){
    &shift_comma_2_semicolon_override,
    &shift_dot_2_colon_override,
    // &shift_quote_2_slash_override,
    NULL // Null terminate the array of overrides!
};

const uint16_t PROGMEM combo_upright[] = {KC_U, KC_Y, COMBO_END};
// const uint16_t PROGMEM combo_downright[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_upleft[] = {KC_W, KC_F, COMBO_END};
// const uint16_t PROGMEM combo_downleft[] = {KC_X, KC_C, COMBO_END};
// const uint16_t PROGMEM combo_center[] = {KC_D, KC_H, COMBO_END};
// const uint16_t PROGMEM combo_leftthumb[] = {LA_NAVIGATE, REPEAT, COMBO_END};
// const uint16_t PROGMEM combo_rightthumb[] = {KC_SPC, LA_SYMBOLS, COMBO_END};
const uint16_t PROGMEM combo_dualthumb[] = {SPACE_NUMBERS, BACKSPACE_SYMBOLS, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_upright, KC_TAB),
    // COMBO(combo_downright, KC_NO),
    COMBO(combo_upleft, KC_ESC),
    // COMBO(combo_downleft, KC_NO),
    // COMBO(combo_center, KC_NO),
    // COMBO(combo_leftthumb, KC_NO),
    // COMBO(combo_rightthumb, KC_NO),
    COMBO(combo_dualthumb, KC_ENTER),
};

bool is_capitalize_ignored(uint16_t keycode) {
    switch (keycode) {
        case SPACE_NUMBERS:
            return true;
        default:
            return false;
    }
}

bool is_capitalize_keycode(uint16_t keycode) {
    if (keycode == CAPITALIZE_FUNCTIONS) {
        return true;
    }
    return false;
}

bool is_capsword_shifted(uint16_t keycode) {
    switch (keycode) {
        case KC_MINS:
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