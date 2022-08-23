/**
 * ゼノブレイド3の亜人煉獄でクラスのレベル上げを自動化するスケッチ
 *
 * いくつか定数を用意しています。
 * これらは動作させるために必要不可欠な値であり、必ず設定してもらう必要があります。
 * 28行目・39行目の値はご自身で設定いただくようお願いいたします。
 *
 *
 * 初期条件は以下の通り
 * 1. カデンシア地方にいること
 * 2. 近くに敵が存在しないこと
 * 3. 操作キャラがノアであること
 * 4. ノアのフラッシュフェンサーがLv20まで育っていること
 * 5. タレントアーツが「アンリミテッドソード」に設定してあること
 * 6. マスタースキル「いつでもやれる」を設定してあること
 * 7. 亜人煉獄をスキップトラベル開放済であること
 * 8. 戦闘に負けない編成であること
 */

// ライブラリを読み込むためのコード（詳細: https://github.com/lefmarna/NintendoSwitchControlLibrary）
#include <NintendoSwitchControlLibrary.h>

/**
 * スキップトラベル → ランドマーク にて 「亜人煉獄」が上から何番目にあるかを指定する
 * （上から10番目の場合は10となります）
 *
 * ランドマーク開放数で順番が変わるため人によって値が違います。
 * 要設定
 */
const int DEMI_HUMAN_PURGATORY_INDEX = 12;

/**
 * 1戦闘にかかる時間を指定する（秒指定）
 *
 * ※ チェインアタックの有無で大きく時間が変わります。
 * 1チェインしても戦闘が終了することが期待できる時間が300でしたので初期値を300としていますが、必要に応じて変更してください。
 * 要設定
 */
const int BATTLE_TIME = 300;

/**
 * パケ版・DL版の差やSwitch本体の個体差などにより、ボタン間隔が短いと動かない方は以下の数値を調節してください
 */
const int BUTTON_INTERVAL = 1000;  // ボタンを押す間隔
const int HAT_INTERVAL = 200;      // カーソルキーを押す間隔

// 位置をリセットする
void resetPosition() {
    // メニュー → マップ
    pushButton(Button::X, BUTTON_INTERVAL);
    pushHat(Hat::DOWN, HAT_INTERVAL, 2);
    // 亜人煉獄へスキップトラベル
    pushButton(Button::A, BUTTON_INTERVAL, 2);
    pushButton(Button::PLUS, BUTTON_INTERVAL);
    pushButton(Button::A, BUTTON_INTERVAL);
    pushHat(Hat::DOWN, HAT_INTERVAL * 2, DEMI_HUMAN_PURGATORY_INDEX - 1);
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
void moveBattlePosition() {
    tiltLeftStick(Stick::NEUTRAL, Stick::MAX, 4000);
}

// バトルを行う
void startBattle() {
    // 抜刀 → アンリミテッドソード
    pushButton(Button::R, BUTTON_INTERVAL);
    pushButton(Button::A, 2000);
    pushButton(Button::A, 6000);
    // オートバトル
    pushButton(Button::MINUS, BUTTON_INTERVAL);
    for (int i = 0; i < BATTLE_TIME / 30; i++) {
        delay(30000);
    }
    delay((BATTLE_TIME % 30) * 1000);
}

// 敵をリポップさせる
void repopMonsters() {
    pushButton(Button::R, BUTTON_INTERVAL);
    pushButton(Button::A, 2000);
    holdButton(Button::MINUS, 2000);
    pushHat(Hat::DOWN, HAT_INTERVAL);
    pushButton(Button::A, BUTTON_INTERVAL);
    pushHat(Hat::UP, HAT_INTERVAL);
    pushButton(Button::A, BUTTON_INTERVAL);
    delay(5000);
}

// マイコンのセット時に1度だけ行われる処理
void setup() {
    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushButton(Button::B, 500, 5);
    // 「使いたいコントローラーのL+Rを押してください」の画面が出るまで待機する
    delay(5000);
    // 「使いたいコントローラーのL+Rを押してください」を突破する
    selectController();
    // メニューを開いていた場合は閉じる
    pushButton(Button::B, BUTTON_INTERVAL, 5);
    resetPosition();
}

// ここに記述した内容がループされ続ける
void loop() {
    moveBattlePosition();
    startBattle();
    resetPosition();
    repopMonsters();
}
