/*
Copyright (c) 2021 lefmarna
released under the MIT license
https://opensource.org/licenses/mit-license.php
*/

#pragma once

#include "./SwitchControlLibrary/SwitchControlLibrary.h"

// 各種ボタンの設定(ABXYだけでなく、HOMEやCAPTUREまで幅広く対応)
void pushButton(uint16_t button, int delay_time = 0, int loop = 1);
void holdButton(uint16_t button, int hold_time);
// 十字キーの設定
void pushHat(uint8_t hat, int delay_time = 0, int loop = 1);
void holdHat(uint8_t hat, int hold_time);
// スティックの設定
void tiltLeftStick(uint8_t lx, uint8_t ly, int tilt_time, uint16_t button = NULL);
void tiltRightStick(uint8_t rx, uint8_t ry, int tilt_time, uint16_t button = NULL);
void tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry, int tilt_time, uint16_t button = NULL);