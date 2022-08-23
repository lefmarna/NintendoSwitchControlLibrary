/*
Copyright (c) 2021 lefmarna
released under the MIT license
https://opensource.org/licenses/mit-license.php
*/

#pragma once

#include "./SwitchControlLibrary/SwitchControlLibrary.h"

void pushButton(uint16_t button, unsigned long delay_time = 0, unsigned int loop = 1);
void holdButton(uint16_t button, unsigned long hold_time);

void pushHat(uint8_t hat, unsigned long delay_time = 0, unsigned int loop = 1);
void holdHat(uint8_t hat, unsigned long hold_time);

void tiltLeftStick(uint8_t lx, uint8_t ly, unsigned long tilt_time, uint16_t button = 0);
void tiltRightStick(uint8_t rx, uint8_t ry, unsigned long tilt_time, uint16_t button = 0);
void tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry, unsigned long tilt_time, uint16_t button = 0);

void spinLeftStick(unsigned long spin_time, uint8_t speed = 5, bool direction = 1);
void spinRightStick(unsigned long spin_time, uint8_t speed = 5, bool direction = 1);