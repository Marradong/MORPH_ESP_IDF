// SPDX-License-Identifier: Apache-2.0
// Copyright 2019 Ricardo Quesada
// http://retro.moe/unijoysticle2

#include "sdkconfig.h"
#include <stddef.h>
#include <btstack_port_esp32.h>
#include <btstack_run_loop.h>
#include <btstack_stdio_esp32.h>
#include <arduino_platform.h>
#include <uni.h>


int app_main(void) {
    // Configure BTstack for ESP32 VHCI Controller
    btstack_init();

    // Must be called before uni_init()
    uni_platform_set_custom(get_arduino_platform());

    // Init Bluepad32.
    uni_init(0, NULL);

    // Does not return.
    btstack_run_loop_execute();
    return 0;
}
