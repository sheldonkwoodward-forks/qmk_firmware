#include QMK_KEYBOARD_H

enum my_keycodes {
    MT_ALT_BSPC = SAFE_RANGE,
};

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  	switch (keycode) {
		// left shift when held, alt + backspace when tapped
		// this emulates mod-tap functionality because mod-tap does not support modifiers combined with keycodes
    	case MT_ALT_BSPC:
      		if (record->event.pressed) {
				key_timer = timer_read();
				register_mods(MOD_BIT(KC_LSFT));
      		} else {
				unregister_mods(MOD_BIT(KC_LSFT));
				if (timer_elapsed(key_timer) < TAPPING_TERM) {
          			tap_code16(LALT(KC_BSPC));
        		}
	  		}
      		return false;
		default:
			return true;
	}
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_DEL,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
		KC_MINS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		LSFT_T(KC_LBRC), KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, RSFT_T(KC_RBRC),
		KC_LCTL, KC_LALT, KC_LGUI, LT(1,KC_SPC), LT(2,KC_ENT), LSFT_T(KC_BSPC), LT(3,KC_DEL), KC_VOLD, KC_NO, KC_VOLU, KC_MUTE
	),
	[1] = LAYOUT(
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, LALT(KC_DEL),
		KC_TRNS, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO, LALT(KC_BSPC),
		KC_CAPS, KC_HOME, LALT(KC_LEFT), KC_PGDN, LALT(KC_RGHT), KC_END, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_TRNS,
		KC_LSFT, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_RSFT,
		KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS, LGUI(KC_ENT), MT_ALT_BSPC, LALT(KC_DEL), KC_MRWD, KC_NO, KC_MFFD, KC_MPLY
	),
	[2] = LAYOUT(
		KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSLS, KC_DEL,
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSPC,
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,
		KC_PIPE, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS,
		KC_LCTL, KC_LALT, KC_LGUI, LGUI(KC_SPC), KC_TRNS, LSFT_T(KC_BSPC), KC_NO, KC_MRWD, KC_NO, KC_MFFD, KC_MPLY
	),
	[3] = LAYOUT(
		RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_VOLU, RESET, KC_NO, KC_NO, KC_NO, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_MRWD, KC_VOLD, KC_MFFD, KC_NO, KC_NO, KC_MRWD, KC_VOLD, KC_MFFD, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, NK_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, LAG_SWP, LAG_NRM, KC_MPLY, KC_MUTE, KC_MPLY, KC_TRNS, KC_MRWD, KC_NO, KC_MFFD, KC_MPLY
	)
};
