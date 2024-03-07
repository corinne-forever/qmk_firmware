/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define SEMICLN LT(LOWER, KC_SCLN)
#define M_KEY LT(RAISE, KC_M)
#define Z_KEY LCTL_T(KC_Z)
#define SLSH_KY RCTL_T(KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_6x7_right(
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                      KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,
        _______, KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL,
        _______, KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                      KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC,
        _______, _______, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                      KC_H   , KC_J   , KC_K   , KC_L   , SEMICLN, KC_QUOT, KC_BACKSLASH,
        _______, KC_LSPO, Z_KEY  , KC_X   , KC_C   , KC_V   , KC_B   ,                      KC_N   , M_KEY  , KC_COMM, KC_DOT , SLSH_KY, KC_RSPC, _______,
                                   KC_LGUI, KC_LALT,                                                          KC_RALT, KC_RGUI,
                                                     KC_BTN1, KC_SPC ,                               _______,
                                                     KC_ENT , KC_TAB ,                               KC_BSPC,
                                                     _______, KC_BTN2,                      KC_DEL , KC_ESC
    ),

    [_LOWER] = LAYOUT_6x7_right(
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      KC_HOME, KC_PGUP, KC_PGDN, KC_END , _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______,                                                          _______, _______,
                                                     _______, _______,                               _______,
                                                     _______, _______,                               _______,
                                                     _______, _______,                      _______, _______
    ),

    [_RAISE] = LAYOUT_6x7_right(
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______ , _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,
                                   _______, _______,                                                          _______, _______,
                                                     _______, _______,                               _______,
                                                     _______, _______,                               _______,
                                                     _______, _______,                      _______, _______
    )
};

bool set_scrolling = false;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
        mouse_report.x = mouse_report.y = 0;
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_F) {
        set_scrolling = record->event.pressed;
    }
    return true;
}
