/**
 * @file dev_ble_esp32_s3.ino
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief BLEの基礎研究 [ESP32-S3]
 * @version 0.1
 * @date 2026-05-09
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

// C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Arduino IDE Lib
#include <Arduino.h>

#if 0
// FreeRTOS Lib
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#endif

// My Lib
#include "app_ble.h"

// -----------------------------------------------------------
// 基板のGPIO
#define RGBLED_PIN        48   // YD-ESP32-S3 RGBLED @GPIO 48

static app_ble_cfg_t s_ble_cfg;

static void _gpio_init(void);
#if 0
static void _i2c_init(void);
static void _i2s_init(void);
static void _spi_init(void);
#endif
static void _uart_init(void);
// -----------------------------------------------------------
// [Static]
static void _gpio_init(void)
{
    // TODO
}

static void _uart_init(void)
{
    Serial.begin(115200);
}

// -----------------------------------------------------------
void setup()
{
    // GPIO初期化
    _gpio_init();

    // UART初期化
    _uart_init();

    // BLE初期化
    s_ble_cfg.is_use_long_range_mode = true; // BLE Long Rage Mode: 有効
    s_ble_cfg.adv_interval_ms = 1000; // アドバタイズ周期: 1秒周期
    s_ble_cfg.tx_power_dbm = 9; // 送信出力: 9dB
    app_ble_init(&s_ble_cfg);
}

void loop()
{
    // BLEメイン
    app_ble_main();
}