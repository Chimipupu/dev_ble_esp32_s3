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
// DeepSleep周期
#define DEEPSLEEP_PERIOD_MS    1000 // 1秒周期でDeepSleep
// 基板のGPIO
#define RGBLED_PIN              48   // YD-ESP32-S3 RGBLED @GPIO 48

RTC_DATA_ATTR uint32_t g_boot_cnt = 0;

static app_ble_cfg_t s_ble_cfg;
static void _gpio_init(void);
#if 0
static void _i2c_init(void);
static void _i2s_init(void);
static void _spi_init(void);
#endif
static void _uart_init(void);
static void _deepsleep_init(void);

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

static void _deepsleep_init(void)
{
#ifdef DEBUG_NO_SLEEP
    g_boot_cnt++;
#else
    // 起床要因がDeepSleep
    if(esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
        g_boot_cnt++;
        Serial.printf("Wakeup from DeepSleep!\r\n");
    }
#endif
    Serial.printf("Boot Count: %lu\n", (unsigned long)g_boot_cnt);

    // DeepSleepの周期に設定
    esp_sleep_enable_timer_wakeup(DEEPSLEEP_PERIOD_MS * 1000); // ms -> us
    Serial.printf("Set DeepSleep Period: %lu ms\r\n", (unsigned long)DEEPSLEEP_PERIOD_MS);
}

// -----------------------------------------------------------
void setup()
{
    // DeepSleep初期化
    _deepsleep_init();

    // GPIO初期化
    _gpio_init();

    // UART初期化
    _uart_init();

    // BLE初期化
    s_ble_cfg.is_use_long_range_mode = true; // BLE Long Rage Mode: 有効
    s_ble_cfg.adv_interval_ms = 1000;        // アドバタイズ周期: 1秒周期
    s_ble_cfg.tx_power_dbm = 9;              // 送信出力: 9dB
    app_ble_init(&s_ble_cfg);
}

void loop()
{
#ifdef DEBUG_NO_SLEEP
    // (DEBUG) DeepSleepから起床を擬似的に処理
    Serial.printf("[DEBUG] DeepSleep Wake Up");
    _deepsleep_init();
#endif

    // BLEのメイン処理
    Serial.printf("BLE Advertis\r\n");
    app_ble_main();

   // DeepSleep開始
    Serial.printf("DeepSleeping...zzz\r\n");
#ifdef DEBUG_NO_SLEEP
    // (DEBUG) デバッグ時はDeepSleepしない
    delay(DEEPSLEEP_PERIOD_MS);
#else
    esp_deep_sleep_start();
#endif
}