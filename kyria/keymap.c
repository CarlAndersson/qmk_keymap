#include "CarlAndersson.h"
// #include "oneshot.h"

enum layers {
    BASE = 0,
    SYMBOLS,
    NAVIGATE,
    NUMBERS,
    FUNCTION,
};

enum custom_keycodes {
    REPEAT = KEYMAP_SAFE_RANGE,
    // OS_SHFT,
    // OS_ALT,
    // OS_CTRL,
    // OS_CMD,
    // OS_HOLD,
    // REPEAT,
};


#define MC_COPY LGUI(KC_C)
#define MC_PSTE LGUI(KC_V)
#define MC_CUT LGUI(KC_X)
#define MC_UNDO LGUI(KC_Z)
#define MC_CMNT LGUI(KC_SLSH)
#define MC_MOUSEWIN LALT(LGUI(LCTL(KC_Z)))
#define MC_KBRDWIN LALT(LGUI(LCTL(KC_X)))

#define SE_ARNG LALT(KC_LBRC)
#define SE_ADIA LALT(KC_QUOT)
#define SE_ODIA LALT(KC_SCLN)

#define LA_NAVIGATE MO(NAVIGATE)
#define LA_SYMBOLS MO(SYMBOLS)
#define LA_NUMBERS MO(NUMBERS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  Q   | W    | F    | P    | G    |                              |   J  |  L   |  U   |  Y   | -  _ |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  A   | R    | S    | T    | D    |                              |   H  |  N   |  E   |  I   |  O   |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |  Z   | X    | C    | V    | B    |      |      |  |      |      |   K  |  M   | ,  ; | .  : | '  / |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | Ext  | Shft |      |  |      | Spce | Sym  |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [BASE] = LAYOUT(
      _______, KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,                                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_BSPC, _______,
      _______, KC_A,   KC_R,   KC_S,   KC_T,   KC_D,                                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______,
      _______, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,      _______, _______,      _______, _______, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, _______,
                            _______, _______,  LA_NAVIGATE, REPEAT, _______,      _______, KC_SPC,  LA_SYMBOLS,  _______, _______
    ),
/*
 * Symbols layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |   ?  | 7    | 8    |  9   |      |                              |  J   |  *   |  /   |  +   |  -   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |   0  | 4    | 5    |  6   |      |                              |  <   |  (   |  [   |  {   |  =   |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |   e  | 1    | 2    |  3   |      |      |      |  |      |      |  >   |  )   |  ]   |  }   | "    |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | Sym2 | Spce |      |  |      |      | ---- |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

    [NUMBERS] = LAYOUT(
      _______, KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO,                                                KC_NO,   KC_SLSH, KC_BSLS, KC_ASTR, KC_BSPC, _______,
      _______, KC_0,    KC_4,    KC_5,    KC_6,    KC_LABK,                                              KC_RABK, KC_MINS, KC_EQL,  KC_PLUS, KC_CIRC, _______,
      _______, KC_NO,   KC_1,    KC_2,    KC_3,    KC_NO,    _______, _______,         _______, _______, KC_NO,   KC_TILD, KC_COMM, KC_DOT,  KC_NO,   _______,
                                 _______, _______, _______,  _______,  _______,         _______, _______, _______, _______, _______
    ),
/*
 * Extend layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |OsHold|      |      |      |      |                              |      |   ~  |  ↑   |   å  |  ä   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | Shft | Ctrl | Alt  | Cmd  |MseWin|                              |KeyWin|   ←  |      |  →   |  ö   |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Pste |Coment|      |      |  |      |      |      |Dedent|  ↓   |Indent|  \   |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | ---- |      |      |  |      | Spce | Sym2 |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

    [NAVIGATE] = LAYOUT(
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                           KC_NO,   KC_NO,       KC_NO,    KC_NO,    KC_BSPC, _______,
      _______, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_NO,                                           KC_NO,   KC_LEFT,     KC_UP,  KC_RGHT,    KC_NO, _______,
      _______, MC_UNDO, MC_CUT,  MC_COPY, MC_PSTE, MC_CMNT, _______, _______,     _______, _______, KC_NO,   G(KC_LBRC),  KC_DOWN,  G(KC_RBRC),KC_NO, _______,
                                 _______, _______, _______, _______, _______,     _______, KC_SPC,  _______,  _______, _______
    ),

/*
 * Meta layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  !   |      |      |  %   |      |                              |   F1 |  F2  |  F3  |  F4  |  F5  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  @   | $    |  &   |  ^   |  |   |                              |   F6 |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |  #   |      |      |      |  |      |      |  F11 |  F12 |      |      |  `   |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | ---- |      |      |  |      |      | ---- |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

    [SYMBOLS] = LAYOUT(
      _______, KC_NO,   KC_QUES, KC_EXLM, KC_PERC, KC_NO,                                           KC_NO,   KC_PIPE, KC_LCBR, KC_RCBR, SE_ARNG, _______,
      _______, KC_AT,   KC_LPRN, KC_RPRN, KC_HASH, KC_LABK,                                         KC_RABK, KC_UNDS, KC_DLR,  SE_ADIA, SE_ODIA, _______,
      _______, KC_AMPR, KC_LBRC, KC_RBRC, KC_NO,   KC_NO,   _______, _______,     _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_GRV,  _______,
                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),


/*
 * NumLock layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      | Exit |  7   |  8   |  9   |      |                              |  F1  |  F2  |  F3  |  F4  |  F5  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  0   |  4   |  5   |  6   |      |                              |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |  e   |  1   |  2   |  3   |      |      |      |  |      |      |  F11 |  F12 |  F13 |  F14 |  F15 |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      |  -   |  +   |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

   [FUNCTION] = LAYOUT(
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______,                                         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______,                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, _______, _______,     _______, _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______,
                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      |      |      |      |      |      |                              |      |      |      |      |      |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      |      |      |      |      |      |                              |      |      |      |      |      |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      |      |      |      |  |      |      |      |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  *
//  *    .-----------------------------.        .-----------------------------.
//  *    |     |     |     |     |     |        |     |     |     |     |     |
//  *    |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
//  *    |     |     |     |     |     |        |     |     |     |     |     |
//  *    |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
//  *    |     |     |     |     |     |        |     |     |     |     |     |
//  *    .-----------------+-----+-----|        |-----+-----+-----------------.
//  *                      |     |     |        |     |     |
//  *                      .-----+-----.        .-----+-----.
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
//     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, SYMBOLS, NAVIGATE, FUNCTION);
    return state;
}

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
const uint16_t PROGMEM combo_downright[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_upleft[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_downleft[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_center[] = {KC_D, KC_H, COMBO_END};
const uint16_t PROGMEM combo_leftthumb[] = {LA_NAVIGATE, REPEAT, COMBO_END};
const uint16_t PROGMEM combo_rightthumb[] = {KC_SPC, LA_SYMBOLS, COMBO_END};
const uint16_t PROGMEM combo_dualthumb[] = {KC_SPC, REPEAT, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_upright, KC_TAB),
    COMBO(combo_downright, KC_NO),
    COMBO(combo_upleft, KC_ESC),
    COMBO(combo_downleft, KC_NO),
    COMBO(combo_center, CAPSWORD),
    COMBO(combo_leftthumb, LA_NUMBERS),
    COMBO(combo_rightthumb, KC_LSFT),
    COMBO(combo_dualthumb, KC_ENTER),
};



bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_NAVIGATE:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {

    switch (keycode) {
    case LA_SYMBOLS:
    case LA_NUMBERS:
    case LA_NAVIGATE:
    case OS_SHFT:
    case OS_ALT:
    case OS_CTRL:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

// bool oneshot_hold = false;
// oneshot_state os_ctrl_state = os_up_unqueued;
// oneshot_state os_shft_state = os_up_unqueued;
// oneshot_state os_alt_state = os_up_unqueued;
// oneshot_state os_cmd_state = os_up_unqueued;


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    // switch (keycode) {
//     case OS_HOLD:
//         oneshot_hold = !oneshot_hold;
//         break;

//     update_single_oneshot(
//         &os_shft_state, KC_LSFT, OS_SHFT, OS_HOLD,
//         keycode, record
//     );
//     update_single_oneshot(
//         &os_ctrl_state, KC_LCTL, OS_CTRL, OS_HOLD,
//         keycode, record
//     );
//     update_single_oneshot(
//         &os_alt_state, KC_LALT, OS_ALT, OS_HOLD,
//         keycode, record
//     );
//     update_single_oneshot(
//         &os_cmd_state, KC_LCMD, OS_CMD, OS_HOLD,
//         keycode, record
//     );

    return true;
}