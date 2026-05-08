/**
 * @file app_ble.h
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief BLE @ESP32-S3
 * @version 0.1
 * @date 2026-05-09
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#ifndef APP_BLE_H
#define APP_BLE_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// -----------------------------------------------------------
// [コンパイルスイッチ]
#define DEVELOP_BLE_BEACON
// #define DEVELOP_BLE_PERIPHERAL
// #define DEVELOP_BLE_CENTRAL

// -----------------------------------------------------------

typedef struct {
    bool is_use_long_range_mode; // 長距離モードを使用有無
    uint16_t tx_power_dbm;       // 送信出力レベル[dBm]
#ifdef DEVELOP_BLE_BEACON
    uint16_t adv_interval_ms;    // アドバタイズの間隔 (ms)
#endif
} app_ble_cfg_t;

// -----------------------------------------------------------
void app_ble_init(app_ble_cfg_t *p_cfg);
void app_ble_beacon_set_data(void *p_data, uint32_t data_size_byte);
void app_ble_main(void);

// -----------------------------------------------------------

#endif // APP_BLE_H