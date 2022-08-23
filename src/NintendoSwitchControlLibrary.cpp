/*
Copyright (c) 2021 lefmarna
released under the MIT license
https://opensource.org/licenses/mit-license.php
*/

#include "./NintendoSwitchControlLibrary.h"

// ボタンを押してから離すまでの時間（ミリ秒）
const uint16_t INPUT_TIME = 100;

// ボタンを連打する際に、押して認識後、離して認識するまでの合計時間（ミリ秒）
const uint16_t INPUT_TIME_TWICE = INPUT_TIME * 2;

/**
 * ボタンを押す
 *
 * @param uint16_t      button     押すボタン
 * @param unsigned long delay_time ボタンを押した後の待ち時間（1秒 = 1000）
 * @param unsigned int  loop       ボタンを押す回数（省略可、デフォルトは1）
 */
void pushButton(uint16_t button, unsigned long delay_time, unsigned int loop) {
    for (unsigned int i = 0; i < loop; i++) {
        SwitchControlLibrary().pressButton(button);
        SwitchControlLibrary().sendReport();
        delay(INPUT_TIME);
        SwitchControlLibrary().releaseButton(button);
        SwitchControlLibrary().sendReport();
        delay(delay_time);
    }
    delay(INPUT_TIME);
}

/**
 * ボタンを指定の時間押し続ける
 *
 * @param uint16_t      button    押し続けるボタン
 * @param unsigned long hold_time ボタンを押す時間の長さ（1秒 = 1000）
 */
void holdButton(uint16_t button, unsigned long hold_time) {
    SwitchControlLibrary().pressButton(button);
    SwitchControlLibrary().sendReport();
    delay(hold_time);
    SwitchControlLibrary().releaseButton(button);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

/**
 * 十字キーを押す
 *
 * @param uint8_t       hat        押す十字キーのボタン
 * @param unsigned long delay_time ボタンを押した後の待ち時間（1秒 = 1000）
 * @param unsigned int  loop       ボタンを押す回数（省略可、デフォルトは1）
 */
void pushHat(uint8_t hat, unsigned long delay_time, unsigned int loop) {
    for (unsigned int i = 0; i < loop; i++) {
        SwitchControlLibrary().pressHatButton(hat);
        SwitchControlLibrary().sendReport();
        delay(INPUT_TIME);
        SwitchControlLibrary().releaseHatButton();
        SwitchControlLibrary().sendReport();
        delay(delay_time);
    }
    delay(INPUT_TIME);
}

/**
 * 十字キーを指定の時間押し続ける
 *
 * @param uint8_t       hat:       押し続ける十字キーのボタン
 * @param unsigned long hold_time: ボタンを押す時間の長さ（1秒 = 1000）
 */
void holdHat(uint8_t hat, unsigned long hold_time) {
    SwitchControlLibrary().pressHatButton(hat);
    SwitchControlLibrary().sendReport();
    delay(hold_time);
    SwitchControlLibrary().releaseHatButton();
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

/**
 * 左スティックを指定の時間傾け続ける
 * 128を基準とし、0~255の値を指定する
 *
 * @param uint8_t       lx:        左スティックのx軸
 * @param uint8_t       ly:        左スティックのy軸
 * @param unsigned long tilt_time: スティックを傾ける時間の長さ
 * @param uint16_t      button:    連打するボタン
 *
 * @see Stick::MIN       0
 * @see Stick::NEUTRAL 128
 * @see Stick::MAX     255
 */
void tiltLeftStick(uint8_t lx, uint8_t ly, unsigned long tilt_time, uint16_t button) {
    SwitchControlLibrary().moveLeftStick(lx, ly);
    SwitchControlLibrary().sendReport();
    if (button) {
        while (INPUT_TIME_TWICE <= tilt_time) {
            SwitchControlLibrary().pressButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            SwitchControlLibrary().releaseButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            tilt_time -= INPUT_TIME_TWICE;
        }
    }
    delay(tilt_time);
    SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

/**
 * 右スティックを指定の時間傾け続ける
 * 128を基準とし、0~255の値を指定する
 *
 * @param uint8_t       rx:        右スティックのx軸
 * @param uint8_t       ry:        右スティックのy軸
 * @param unsigned long tilt_time: スティックを傾ける時間の長さ
 * @param uint16_t      button:    連打するボタン
 *
 * @see Stick::MIN       0
 * @see Stick::NEUTRAL 128
 * @see Stick::MAX     255
 */
void tiltRightStick(uint8_t rx, uint8_t ry, unsigned long tilt_time, uint16_t button) {
    SwitchControlLibrary().moveRightStick(rx, ry);
    SwitchControlLibrary().sendReport();
    if (button) {
        while (INPUT_TIME_TWICE <= tilt_time) {
            SwitchControlLibrary().pressButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            SwitchControlLibrary().releaseButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            tilt_time -= INPUT_TIME_TWICE;
        }
    }
    delay(tilt_time);
    SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

/**
 * 左スティックと右スティックを同時に指定の時間傾け続ける
 * 128を基準とし、0~255の値を指定する
 *
 * @param uint8_t       lx:        左スティックのx軸
 * @param uint8_t       ly:        左スティックのy軸
 * @param uint8_t       rx:        右スティックのx軸
 * @param uint8_t       ry:        右スティックのy軸
 * @param unsigned long tilt_time: スティックを傾ける時間の長さ
 * @param uint16_t      button:    連打するボタン
 *
 * @see Stick::MIN       0
 * @see Stick::NEUTRAL 128
 * @see Stick::MAX     255
 */
void tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry,
                           unsigned long tilt_time, uint16_t button) {
    SwitchControlLibrary().moveLeftStick(lx, ly);
    SwitchControlLibrary().moveRightStick(rx, ry);
    SwitchControlLibrary().sendReport();
    if (button) {
        while (INPUT_TIME_TWICE <= tilt_time) {
            SwitchControlLibrary().pressButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            SwitchControlLibrary().releaseButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            tilt_time -= INPUT_TIME_TWICE;
        }
    }
    delay(tilt_time);
    SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

/**
 * 左スティックをぐるぐると回す
 *
 * @param unsigned long spin_time:  ぐるぐるさせる時間（1回転に満たない端数の時間が生じた場合は切り捨てとなります）
 * @param uint8_t       speed:      1秒あたりの回転数
 * @param bool          direction:  方向（1: 時計回り, 0：反時計回り）
 */
void spinLeftStick(unsigned long spin_time, uint8_t speed, bool direction) {
    // 1秒あたりの回転数から1回転にかかる時間を求める
    float spin_count_per_second = 1000 / speed;

    // 1回転で8箇所のチェックポイントを回ることになるため、その通過タイムを求める
    float spin_delay = spin_count_per_second / 8;

    // 回転方向の制御を担う変数を用意する（スティックのx座標をdirectionの値によって左右逆転させる）
    int x_max;
    int x_min;
    if (direction) {
        x_max = Stick::MAX;
        x_min = Stick::MIN;
    } else {
        x_max = Stick::MIN;
        x_min = Stick::MAX;
    }

    // 指定された時間の間、左スティックをぐるぐると回す
    while (spin_time >= spin_count_per_second) {
        SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::MAX);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveLeftStick(x_min, Stick::MAX);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveLeftStick(x_min, Stick::NEUTRAL);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveLeftStick(x_min, Stick::MIN);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::MIN);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveLeftStick(x_max, Stick::MIN);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveLeftStick(x_max, Stick::NEUTRAL);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveLeftStick(x_max, Stick::MAX);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        spin_time = spin_time - spin_count_per_second;
    }

    // 処理が終了したら、スティックを倒していない状態に戻す
    SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
}

/**
 * 右スティックをぐるぐると回す
 *
 * @param unsigned long spin_time: ぐるぐるさせる時間（1回転に満たない端数の時間が生じた場合は切り捨てとなります）
 * @param uint8_t       speed:     1秒あたりの回転数
 * @param bool          direction: 方向（1: 左, 0：右）
 */
void spinRightStick(unsigned long spin_time, uint8_t speed, bool direction) {
    // 1秒あたりの回転数から1回転にかかる時間を求める
    float spin_count_per_second = 1000 / speed;

    // 1回転で8箇所のチェックポイントを回ることになるため、その通過タイムを求める
    float spin_delay = spin_count_per_second / 8;

    // 回転方向の制御を担う変数を用意する（スティックのx座標をdirectionの値によって左右逆転させる）
    int x_max;
    int x_min;
    if (direction) {
        x_max = Stick::MAX;
        x_min = Stick::MIN;
    } else {
        x_max = Stick::MIN;
        x_min = Stick::MAX;
    }

    // 指定された時間の間、右スティックをぐるぐると回す
    while (spin_time >= spin_count_per_second) {
        SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::MAX);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveRightStick(x_min, Stick::MAX);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveRightStick(x_min, Stick::NEUTRAL);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveRightStick(x_min, Stick::MIN);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::MIN);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveRightStick(x_max, Stick::MIN);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveRightStick(x_max, Stick::NEUTRAL);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        SwitchControlLibrary().moveRightStick(x_max, Stick::MAX);
        SwitchControlLibrary().sendReport();
        delay(spin_delay);
        spin_time = spin_time - spin_count_per_second;
    }

    // 処理が終了したら、スティックを倒していない状態に戻す
    SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
}