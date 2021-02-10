/**
 * 育て屋から卵を回収→孵化→ボックスに預けるを繰り返すスケッチ
 * ボックスに空きがある限り、ポケモンを孵化し続ける
 *
 * 初期条件は以下の通り
 * 1.ハシノマはらっぱにいること
 * 2.自転車に乗っていること
 * 3.手持ちが1体のみのこと
 * 4.Xボタンを押したときに「タウンマップ」が左上、「ポケモン」がその右にあること
 * 5.ボックスが空のこと
 * 6.オフライン状態であること
 * 7.無線のコントローラーが接続されていないこと
 * 8.「設定」から「話の速さ」を「速い」に、「手持ち／ボックス」を「自動で送る」に、「ニックネーム登録」を「しない」にしておくこと
 */

// ライブラリを読み込むためのコード
#include <NintendoSwitchControlLibrary.h>

// 孵化サイクル20のポケモンが、孵化するまでにかかる最大時間
const int TIME_TO_HATCHING_SEC = 69;

// 空飛ぶタクシーでハシノマはらっぱに移動する関数
void moveToInitialPlayerPosition() {
    pushButton(Button::A, 2000);
    pushButton(Button::A, 450, 2);
    delay(2200);  // 天候によって読み込み時間がやや異なる(最も重かった砂嵐でも1900で安定していたが、柱の本数や服装などの環境による差異がある可能性も考慮して少し余裕を持たせた)
}

// 初期位置(ハシノマはらっぱ)からぐるぐる走り回る関数
void runAround() {
    for (int egg_num = 0; egg_num < 6; egg_num++) {
        tiltLeftStick(Stick::MAX, Stick::NEUTRAL, 500);
        // delayの秒数がintの最大値を越えないように30秒ごとに実行する
        for (int i = 0; i < TIME_TO_HATCHING_SEC / 30; i++) {
            tiltLeftAndRightStick(Stick::MAX, Stick::MAX, Stick::MIN, Stick::MIN, 30000);
        }
        tiltLeftAndRightStick(Stick::MAX, Stick::MAX, Stick::MIN, Stick::MIN, (TIME_TO_HATCHING_SEC % 30) * 1000);
        waitEggHatching();
        pushButton(Button::X, 500);
        moveToInitialPlayerPosition();
    }
}

// ボックスを開く関数
void openBox() {
    pushButton(Button::X, 500);
    pushHat(Hat::RIGHT, 25);
    pushButton(Button::A, 1250);
    pushButton(Button::R, 1500);
}

// ボックスを閉じる関数
void closeBox() {
    pushButton(Button::B, 25);  // ボックスが空でなかった場合でも、ボックスを閉じてループを実行し続けさせるのに必要な記述
    pushButton(Button::B, 1500);
    pushButton(Button::B, 1250);
    pushHat(Hat::LEFT, 25);
}

// タマゴが孵化するのを待つ関数
void waitEggHatching() {
    pushButton(Button::B, 450, 38);  // 余裕があるように思えるが、色違いのエフェクトを考慮するとこれ以上は厳しい
}

// タマゴをボックスから引き取る関数
void adoptedEggs(int box_line) {
    // 孵化させるタマゴを範囲選択
    pushButton(Button::A, 25);
    pushHat(Hat::DOWN, 50, 4);
    pushButton(Button::A, 25);
    // 手持ちに加える
    pushHat(Hat::LEFT, 100, box_line + 1);
    pushHat(Hat::DOWN, 25);
    pushButton(Button::A, 25);
}

// タマゴを孵化→ボックスのタマゴと入れ替えを繰り返す関数
void withdrawEggs(int box_line) {
    // 空飛ぶタクシーでハシノマはらっぱに移動する
    moveToInitialPlayerPosition();
    // 手持ちのタマゴを全て孵化させる
    runAround();
    // ボックスを開く
    openBox();
    // 手持ちの孵化したポケモンを範囲選択
    pushHat(Hat::LEFT, 25);
    pushHat(Hat::DOWN, 25);
    pushButton(Button::Y, 25);
    pushButton(Button::Y, 25);
    pushButton(Button::A, 25);
    pushHat(Hat::DOWN, 50, 4);
    pushButton(Button::A, 25);
    // ボックスに預ける
    pushHat(Hat::RIGHT, 100, box_line);
    pushHat(Hat::UP, 25);
    pushButton(Button::A, 25);
    // ボックスがいっぱいになったら、次のボックスに移動させる
    if (box_line == 6) {
        pushHat(Hat::UP, 25);
        pushHat(Hat::RIGHT, 25);
        // 新しいボックスの1列目のタマゴを引き取る
        pushHat(Hat::DOWN, 25);
        pushHat(Hat::RIGHT, 100, 2);
        adoptedEggs(0);
    } else {
        // タマゴをボックスから引き取る
        pushHat(Hat::RIGHT, 25);
        adoptedEggs(box_line);
    }
    // ボックスを閉じる
    closeBox();
}

// マイコンのセット時に1度だけ行われる処理
void setup() {
    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushButton(Button::B, 500, 5);

    // マイコンを認識したら、メニューの左上にカーソルを持っていく
    pushButton(Button::X, 600);
    holdHat(Hat::UP_LEFT, 750);

    // ボックスを開く
    pushHat(Hat::RIGHT, 25);
    pushButton(Button::A, 1250);
    pushButton(Button::R, 1500);

    // 孵化させるタマゴを手持ちに加える
    pushButton(Button::Y, 25);
    pushButton(Button::Y, 25);
    adoptedEggs(0);

    // ボックスを閉じる
    closeBox();
}

// ここに記述した内容がループされ続ける
void loop() {
    for (int box_line = 1; box_line < 7; box_line++) {
        withdrawEggs(box_line);
    }
}
