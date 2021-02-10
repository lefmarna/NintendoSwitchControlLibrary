/*
Copyright (c) 2021 lefmarna
released under the MIT license
https://opensource.org/licenses/mit-license.php
*/

#include "./NintendoSwitchControlLibrary.h"

// ボタンを押してから離すまでの時間（ミリ秒）
const uint16_t INPUT_TIME = 100;

void pushButton(uint16_t button, int delay_time, int loop) {
    /*
    Switchコントローラーのボタンを押す関数

    Parameters
    -------------------
        button: 押すボタン
        delay_time: ボタンを押した後の待ち時間（1秒 = 1000）
        loop: ボタンを押す回数（省略可、デフォルトは1）
    */
    for (int i = 0; i < loop; i++) {
        SwitchControlLibrary().pressButton(button);
        SwitchControlLibrary().sendReport();
        delay(INPUT_TIME);
        SwitchControlLibrary().releaseButton(button);
        SwitchControlLibrary().sendReport();
        delay(delay_time);
    }
    delay(INPUT_TIME);
}

void holdButton(uint16_t button, int hold_time) {
    /*
    Switchコントローラーのボタンを指定の時間押し続ける関数

    Parameters
    -------------------
        button: 押し続けるボタン
        hold_time: ボタンを押す時間の長さ（1秒 = 1000）
    */
    SwitchControlLibrary().pressButton(button);
    SwitchControlLibrary().sendReport();
    delay(hold_time);
    SwitchControlLibrary().releaseButton(button);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

void pushHat(uint8_t hat, int delay_time, int loop) {
    /*
    Switchコントローラーの十字キーを押す関数

    Parameters
    -------------------
        hat: 押す十字キーのボタン
        delay_time: ボタンを押した後の待ち時間（1秒 = 1000）
        loop: ボタンを押す回数（省略可、デフォルトは1）
    */
    for (int i = 0; i < loop; i++) {
        SwitchControlLibrary().pressHatButton(hat);
        SwitchControlLibrary().sendReport();
        delay(INPUT_TIME);
        SwitchControlLibrary().releaseHatButton();
        SwitchControlLibrary().sendReport();
        delay(delay_time);
    }
    delay(INPUT_TIME);
}

void holdHat(uint8_t hat, int hold_time) {
    /*
    Switchコントローラーの十字キーを指定の時間押し続ける関数

    Parameters
    -------------------
        hat: 押し続ける十字キーのボタン
        hold_time: ボタンを押す時間の長さ（1秒 = 1000）
    */
    SwitchControlLibrary().pressHatButton(hat);
    SwitchControlLibrary().sendReport();
    delay(hold_time);
    SwitchControlLibrary().releaseHatButton();
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

void tiltLeftStick(uint8_t lx, uint8_t ly, int tilt_time) {
    /*
    Switchコントローラーの左スティックを指定の時間傾け続ける関数
    128を基準とし、0~255の値を指定する

    Parameters
    -------------------
        lx: 左スティックのx軸
        ly: 左スティックのy軸
        tilt_time: スティックを傾ける時間の長さ

    Options
    -------------------
          0: Stick::MIN
        128: Stick::NEUTRAL
        255: Stick::MAX
    */
    SwitchControlLibrary().moveLeftStick(lx, ly);
    SwitchControlLibrary().sendReport();
    delay(tilt_time);
    SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

void tiltRightStick(uint8_t rx, uint8_t ry, int tilt_time) {
    /*
    Switchコントローラーの右スティックを指定の時間傾け続ける関数
    128を基準とし、0~255の値を指定する

    Parameters
    -------------------
        rx: 右スティックのx軸
        ry: 右スティックのy軸
        tilt_time: スティックを傾ける時間の長さ

    Options
    -------------------
          0: Stick::MIN
        128: Stick::NEUTRAL
        255: Stick::MAX
    */
    SwitchControlLibrary().moveRightStick(rx, ry);
    SwitchControlLibrary().sendReport();
    delay(tilt_time);
    SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

void tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry,
                           int tilt_time) {
    /*
    Switchコントローラーの左スティックと右スティックを同時に指定の時間傾け続ける関数
    128を基準とし、0~255の値を指定する

    Parameters
    -------------------
        lx: 左スティックのx軸
        ly: 左スティックのy軸
        rx: 右スティックのx軸
        ry: 右スティックのy軸
        tilt_time: スティックを傾ける時間の長さ

    Options
    -------------------
          0: Stick::MIN
        128: Stick::NEUTRAL
        255: Stick::MAX
    */
    SwitchControlLibrary().moveLeftStick(lx, ly);
    SwitchControlLibrary().moveRightStick(rx, ry);
    SwitchControlLibrary().sendReport();
    delay(tilt_time);
    SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}
