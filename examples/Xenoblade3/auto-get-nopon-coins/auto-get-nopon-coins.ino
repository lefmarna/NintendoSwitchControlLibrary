/**
 * ゼノブレイド3の熾天神獣セラティニア討伐を自動化し、ノポンコイン金・銀と金策を自動化するスケッチ
 *
 * 初期条件は以下の通り
 * 1. 熾天神獣セラティニアを討伐済であること
 * 2. 難易度設定が「イージー」であること
 * 3. インタリンク操作タイプを「パーティ」にしておくこと
 * 4. 大剣上層部のユニークモンスターをすべて討伐済であること（全3種）
 * 5. 操作キャラにマスタースキル「いつでもやれる」を設定していないこと
 * 6. 操作キャラ以外にバーストコンボを盛り込みつつ、かつ、全滅しない程度の回復アーツも積んだ編成であること（参考: https://www.youtube.com/watch?v=VsUHX7SLwsU）
 */

// ライブラリを読み込むためのコード（詳細: https://github.com/lefmarna/NintendoSwitchControlLibrary）
#include <NintendoSwitchControlLibrary.h>

// スキップトラベル → 名を冠する者の墓 にて 「熾天神獣セラティニア」が上から何番目にあるかを指定する
const int SKIP_TRAVEL_INDEX = 2;

// 1戦闘にかかる時間を指定する（分指定）
const int BATTLE_TIME_MINUS = 29;

// 何回ループさせるか？（銀コインが3セットで90枚近く取得できるため、3推奨）
const int BATTLE_COUNT = 3;

// パケ版・DL版の差やSwitch本体の個体差などにより、ボタン間隔が短いと動かない方は以下の数値を調節してください
const int BUTTON_INTERVAL = 1000;  // ボタンを押す間隔
const int HAT_INTERVAL = 500;      // カーソルキーを押す間隔

// マップを開く
void openMap() {
    SwitchControlLibrary().pressButton(Button::ZL);
    SwitchControlLibrary().sendReport();
    delay(BUTTON_INTERVAL);
    SwitchControlLibrary().pressButton(Button::X);
    SwitchControlLibrary().sendReport();
    delay(BUTTON_INTERVAL);
    SwitchControlLibrary().releaseButton(Button::ZL);
    SwitchControlLibrary().releaseButton(Button::X);
    SwitchControlLibrary().sendReport();
    delay(5000);
}

// 位置をリセットする
void resetPosition() {
    openMap();
    // 「熾天神獣セラティニアの墓」へスキップトラベル
    pushButton(Button::PLUS, BUTTON_INTERVAL);
    pushHat(Hat::DOWN, HAT_INTERVAL, 2);
    pushButton(Button::A, BUTTON_INTERVAL);
    pushHat(Hat::DOWN, HAT_INTERVAL, SKIP_TRAVEL_INDEX - 1);
    pushButton(Button::A, BUTTON_INTERVAL, 2);
    // ロード時間
    delay(5000);
}

// 「使いたいコントローラーのL+Rを押してください」を閉じる
void selectController() {
    pushButton(Button::L, 100);
    pushButton(Button::R, 100);
    pushButton(Button::A, 3000);
}

// バトル開始位置に移動
void moveToGravePosition() {
    tiltLeftStick(Stick::MAX, Stick::NEUTRAL, 500);
}

// バトルを行う
void startBattle() {
    pushButton(Button::A, 3000, 3);
    // 離れた場所に移動しておく
    tiltLeftStick(Stick::NEUTRAL, Stick::MAX, 7000);
    // 指定の時間（デフォルトは29分)待機する
    const unsigned long battle_time_ms = (1000UL * BATTLE_TIME_MINUS * 60) - 7000;
    delay(battle_time_ms);
}

// Switchをスリープさせる
void sleepGame() {
    holdButton(Button::HOME, 1500);
    pushButton(Button::A, BUTTON_INTERVAL);
}

// マイコンのセット時に1度だけ行われる処理
void setup() {
    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushButton(Button::B, 500, 5);
    // 「使いたいコントローラーのL+Rを押してください」の画面が出るまで待機する
    delay(3000);
    // 「使いたいコントローラーのL+Rを押してください」を突破する
    selectController();
}

int loopCount = 0;

// ここに記述した内容がループされ続ける
void loop() {
    // 指定の回数（デフォルトでは3回）バトルを行った後、スリープ状態にして処理を終了する
    if (loopCount == BATTLE_COUNT) {
        sleepGame();
        exit(0);
    }

    resetPosition();
    moveToGravePosition();
    startBattle();
    loopCount++;
}
