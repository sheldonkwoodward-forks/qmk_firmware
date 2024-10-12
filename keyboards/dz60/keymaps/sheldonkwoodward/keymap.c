#include QMK_KEYBOARD_H

enum layers {
    LYR_BASE = 0,
    LYR_ARRW,
    LYR_NUMS,
    LYR_MCRO,
    LYR_SPCL,
};

enum my_keycodes {
    MT_ALT_BSPC = SAFE_RANGE,
    SW_4_SPC, 
    SW_SPOT,
};

uint16_t alt_bspc_timer;
bool space_held = false;
uint16_t spot_timer;
bool spot_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // left shift when held, alt + backspace when tapped
        // this emulates mod-tap functionality because mod-tap does not support modifiers combined with keycodes
        case MT_ALT_BSPC:
            if (record->event.pressed) {
                alt_bspc_timer = timer_read();
                register_mods(MOD_BIT(KC_LSFT));
            } else {
                unregister_mods(MOD_BIT(KC_LSFT));
                if (timer_elapsed(alt_bspc_timer) < TAPPING_TERM) {
                    tap_code16(LALT(KC_BSPC));
                }
            }
            return false;

        // left shift when held, left curly brace when tapped
        // this emulates mod-tap functionality because mod-tap does not support modifiers combined with keycodes
        case LSFT_T(KC_LCBR):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LCBR);
                return false;
            }
            return true;

        // right shift when held, right curly brace when tapped
        // this emulates mod-tap functionality because mod-tap does not support modifiers combined with keycodes
        case RSFT_T(KC_RCBR):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_RCBR);
                return false;
            }
            return true;

        // four spaces when pressed
        case SW_4_SPC:
            if (record->event.pressed) {
                SEND_STRING("    ");
            }
            return true;

        // tap for space, hold for arrow layer, hold with second function key for macro layer
        case LT(LYR_ARRW, KC_SPC):
            if (record->event.pressed) {
                space_held = true;
                if (spot_held) {
                    layer_on(LYR_MCRO);
					return false;
                }
            } else {
                space_held = false;
                layer_off(LYR_ARRW);
                layer_off(LYR_MCRO);
            }
            return true;

        // tap for spotlight, hold for number layer, hold with first function key for macro layer
        case LT(LYR_NUMS, SW_SPOT):  // Change this to use SW_SPOT
            if (record->event.pressed) {
                spot_held = true;
                spot_timer = timer_read();  // Start timer for tap detection
                if (space_held) {
                    layer_on(LYR_MCRO);  // Switch to Macro layer if Space is held
					return false;
                }
            } else {
                spot_held = false;
                layer_off(LYR_NUMS);  // Turn off Numbers layer when released
                if (timer_elapsed(spot_timer) < TAPPING_TERM) {
                    // Tap SW_SPOT to perform the Spotlight action
                    register_code(KC_LGUI);  // Hold down GUI (Command)
                    tap_code(KC_SPC);        // Tap Space while GUI is held
                    unregister_code(KC_LGUI);  // Release GUI (Command)
					return false;
                }
            }
            return true;  // Prevent further processing
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // base layer
    [LYR_BASE] = LAYOUT(
        QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        LCTL_T(KC_MINS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        LSFT_T(KC_LCBR), SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SC_RSPC, RSFT_T(KC_RCBR),
        KC_LCTL, KC_LALT, KC_LGUI, LT(LYR_ARRW,KC_SPC), LT(LYR_NUMS,SW_SPOT), LSFT_T(KC_BSPC), LT(LYR_SPCL,KC_DEL), KC_MUTE, KC_NO, KC_VOLD, KC_VOLU
    ),

    // arrow keys layer
    [LYR_ARRW] = LAYOUT(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, LALT(KC_DEL),
        SW_4_SPC, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO, LALT(KC_BSPC),
        KC_CAPS, LGUI(KC_LEFT), LALT(KC_LEFT), KC_PGDN, LALT(KC_RGHT), LGUI(KC_RIGHT), KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_TRNS,
        KC_LSFT, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS, KC_TRNS, MT_ALT_BSPC, LALT(KC_DEL), KC_MPLY, KC_NO, KC_MRWD, KC_MFFD
    ),

    // numbers layer
    [LYR_NUMS] = LAYOUT(
        KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSLS, KC_DEL,
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSPC,
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_COLN, KC_EQL,
        KC_PIPE, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_DOT, KC_SLSH, KC_UNDS, KC_PLUS,
        KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS, KC_TRNS, LSFT_T(KC_BSPC), KC_NO, KC_MPLY, KC_NO, KC_MRWD, KC_MFFD
    ),

    // macro layer
    [LYR_MCRO] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, LAG(KC_F), KC_NO, KC_NO, KC_NO, KC_NO, LAG(KC_UP), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, LCAG(KC_LEFT), LGUI(KC_M), LCAG(KC_RIGHT), KC_NO, KC_NO, LAG(KC_LEFT), LAG(KC_DOWN), LAG(KC_RIGHT), KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),

    // special keys layer
    [LYR_SPCL] = LAYOUT(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_VOLU, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_MRWD, KC_VOLD, KC_MFFD, KC_NO, KC_NO, KC_MRWD, KC_VOLD, KC_MFFD, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, NK_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_MPLY, KC_MUTE, KC_MPLY, KC_TRNS, KC_MPLY, KC_NO, KC_MRWD, KC_MFFD
    )

    // empty layer example
    // [X] = LAYOUT(
    //    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    // ),
};
