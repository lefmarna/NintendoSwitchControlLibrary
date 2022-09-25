/**
 * スプラトゥーン3のヒーローモードでイクラ集めを自動化するスケッチ
 *
 * ※ 当プログラムはスプラトゥーン3のVer1.1.1で動作確認を行っております。アップデートにより正常に動作しなくなる可能性がありますのでご了承ください。
 *
 * 初期条件は以下の通り
 * 1. ヒーローモードで「宇宙の中心が、ここにある。」のヤカン上にいること
 * 2. Rスティックの操作感度が「0」であること
 * 3. Rスティックの上下操作が「ノーマル」であること
 * 3. ジャイロ操作が「OFF」であること
 */

// ヤカンに潜る際のロード時間
const int START_LOADING_TIME_MS = 10000;

// ミッションをクリアした後、自由行動できるようになるまでの時間
const int CLEAR_LOADING_TIME_MS = 30000;

// リッターを構えるまでの時間
const int ADJUST_TIME_MS = 6000;

// ライブラリを読み込むためのコード（詳細: https://github.com/lefmarna/NintendoSwitchControlLibrary）
#include <NintendoSwitchControlLibrary.h>

// 「使いたいコントローラーのL+Rを押してください」を閉じる
void selectController() {
    pushButton(Button::L, 100);
    pushButton(Button::R, 100);
    pushButton(Button::A, 3000);
}

// ミッションを開始する
void startMission() {
    holdButton(Button::ZL, START_LOADING_TIME_MS);
    pushButton(Button::A, 2000);
    tiltLeftStick(Stick::NEUTRAL, Stick::MIN, 2000);
    pushButton(Button::A, 3000);
}

// インクを発射する
void shootInk() {
    tiltRightStick(Stick::NEUTRAL, Stick::MIN, 50);
    holdButton(Button::ZR, 2000);
}

// マイコンのセット時に1度だけ行われる処理
void setup() {
    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushButton(Button::B, 500, 5);
    // 「使いたいコントローラーのL+Rを押してください」の画面が出るまで待機する
    delay(5000);
    // 「使いたいコントローラーのL+Rを押してください」を突破する
    selectController();
}

// ここに記述した内容がループされ続ける
void loop() {
    startMission();
    delay(ADJUST_TIME_MS);
    shootInk();
    delay(CLEAR_LOADING_TIME_MS);
}
