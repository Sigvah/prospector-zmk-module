#pragma once

#include <lvgl.h>
#include <zephyr/kernel.h>

#if IS_ENABLED(CONFIG_ZMK_BLE)
#include <zmk/ble.h>
#else
/* The output widget is only built with Bluetooth, but this header is still
 * included by status_screen.c. Provide a fallback so it compiles without BLE. */
#define ZMK_BLE_PROFILE_COUNT 1
#endif

struct zmk_widget_output {
    sys_snode_t node;
    lv_obj_t *obj;
    lv_obj_t *usb_btn;
    lv_obj_t *ble_btn;
    lv_obj_t *slots[ZMK_BLE_PROFILE_COUNT];
};

int zmk_widget_output_init(struct zmk_widget_output *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_output_obj(struct zmk_widget_output *widget);
