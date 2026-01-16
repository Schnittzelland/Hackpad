// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include oled_driver.h
#include timer.h

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_PNO,   KC_PNO,   KC_PNO,   KC_PNO,   KC_PNO,
        KC_PNO,   KC_PNO,   KC_PNO,   KC_PNO,   KC_PNO,
        KC_PNO,   KC_PNO,   KC_PNO,   KC_PNO,   KC_PNO,
    )
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    static uint32_t last_update = 0;

    if (timer_elapsed32(last_update) < 100) {
        return false;
    }
    last_update = timer_read32();

    uint32_t uptime_s = timer_read32() / 1000;

    uint8_t hours   = uptime_s / 3600;
    uint8_t minutes = (uptime_s % 3600) / 60;
    uint8_t seconds = uptime_s % 60;

    oled_clear();

    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Hackclub Pad"), false);

    oled_set_cursor(0, 2);
    oled_write_P(PSTR("Uptime"), false);

    oled_set_cursor(0, 3);
    oled_write_fmt("%02u:%02u:%02u", hours, minutes, seconds);

    return false;
}
#endif