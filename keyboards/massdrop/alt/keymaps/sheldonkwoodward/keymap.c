#include QMK_KEYBOARD_H

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                        rgb_matrix_set_color_all(0, 0, 0);
                        break;
                    case LED_FLAG_KEYLIGHT:
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                        break;
                    case LED_FLAG_UNDERGLOW:
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                        break;
                    default:
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                        break;
                }
            }
            return false;
        default:
            return true;
    }
}

// key layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_65_ansi_blocker(
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_VOLU,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_VOLD,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_MUTE,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, MO(1), MO(2), KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[1] = LAYOUT_65_ansi_blocker(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LALT(KC_BSPC), LALT(KC_DEL),
        KC_TRNS, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MFFD,
        KC_TRNS, KC_HOME, LALT(KC_LEFT), KC_PGDN, LALT(KC_RGHT), KC_END, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, LGUI(KC_ENT), KC_MRWD,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_RSFT, KC_MPLY,
        KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[2] = LAYOUT_65_ansi_blocker(
        RESET, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, BL_TOGG, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        RGB_TOG, BL_STEP, RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, BL_BRTG, KC_NO, KC_NO, KC_NO, KC_NO, NK_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, BL_INC, KC_NO,
        KC_NO, LAG_SWP, LAG_NRM, KC_NO, KC_NO, KC_TRNS, KC_NO, BL_DEC, KC_NO
    )
};
