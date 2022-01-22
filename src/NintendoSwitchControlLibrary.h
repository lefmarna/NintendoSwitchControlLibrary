/*
Copyright (c) 2021 lefmarna
released under the MIT license
https://opensource.org/licenses/mit-license.php
*/

#pragma once

#include "./SwitchControlLibrary/SwitchControlLibrary.h"

void pushButton(uint16_t button, int delay_time = 0, int loop = 1);
void holdButton(uint16_t button, int hold_time);

void pushHat(uint8_t hat, int delay_time = 0, int loop = 1);
void holdHat(uint8_t hat, int hold_time);

void tiltLeftStick(uint8_t lx, uint8_t ly, int tilt_time, uint16_t button = NULL);
void tiltRightStick(uint8_t rx, uint8_t ry, int tilt_time, uint16_t button = NULL);
void tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry, int tilt_time, uint16_t button = NULL);

void spinLeftStick(int spin_time, uint8_t speed = 5, bool direction = 1);
void spinRightStick(int spin_time, uint8_t speed = 5, bool direction = 1);