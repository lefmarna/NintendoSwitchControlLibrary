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

// 孵化するまでに自転車で走り回る時間
const int TIME_TO_HATCHING_SEC = 70;  // 完成された値

// 空飛ぶタクシーでハシノマはらっぱに移動する関数
void moveToInitialPlayerPosition() {
    pushButton(Button::A, 2000);
    pushButton(Button::A, 450, 2);
    delay(2200);  // 天候によって読み込み時間がやや異なる(最も重かった砂嵐でも1900で安定していたが、柱の本数や服装などの環境による差異がある可能性も考慮して少し余裕を持たせた)
}

// 初期位置から育て屋さんに移動しタマゴを受け取る関数
void getEggFromBreeder() {
    // 初期位置(ハシノマはらっぱ)から育て屋さんのところまで移動
    pushButton(Button::PLUS, 600);
    tiltRightStick(Stick::MAX, Stick::NEUTRAL, 2000);
    tiltLeftStick(166, Stick::MIN, 800);
    pushButton(Button::PLUS, 450);
    // 育て屋さんから卵をもらう
    pushButton(Button::A, 450, 3);
    delay(750);
    pushButton(Button::B, 450, 10);
    delay(50);
}

// 初期位置(ハシノマはらっぱ)からぐるぐる走り回る関数
void runAround(int run_time_sec) {
    // delayの秒数がintの最大値を越えないように30秒ごとに実行する
    for (int i = 0; i < run_time_sec / 30; i++) {
        tiltLeftAndRightStick(Stick::MAX, Stick::MAX, Stick::MIN, Stick::MIN, 30000);
    }
    tiltLeftAndRightStick(Stick::MAX, Stick::MAX, Stick::MIN, Stick::MIN, (run_time_sec % 30) * 1000);
}

// タマゴが孵化するのを待つ関数
void waitEggHatching() {
    pushButton(Button::B, 450, 38);  // 余裕があるように思えるが、色違いのエフェクトを考慮するとこれ以上は厳しい
}

// 孵化した手持ちのポケモンをボックスに預ける関数
// box_line : 何列目にポケモンを預けるか
void sendHatchedPoemonToBox(int box_line) {
    // ボックスを開く
    pushButton(Button::X, 500);
    pushHat(Hat::RIGHT, 25);
    pushButton(Button::A, 1250);
    pushButton(Button::R, 1500);
    // 手持ちの孵化したポケモンを範囲選択
    pushHat(Hat::LEFT, 25);
    pushHat(Hat::DOWN, 25);
    pushButton(Button::Y, 25);
    pushButton(Button::Y, 25);
    pushButton(Button::A, 25);
    holdHat(Hat::DOWN, 600);
    pushButton(Button::A, 25);
    // ボックスに移動させる
    pushHat(Hat::RIGHT, 100, box_line + 1);
    pushHat(Hat::UP, 25);
    pushButton(Button::A, 25);
    // ボックスがいっぱいになったら、次のボックスに移動させる
    if (box_line == 5) {
        pushHat(Hat::UP, 25);
        pushHat(Hat::RIGHT, 25);
    }
    // ボックスを閉じる
    pushButton(Button::B, 25);  // ボックスが空でなかった場合でも、ボックスを閉じてループを実行し続けさせるのに必要な記述
    pushButton(Button::B, 1500);
    pushButton(Button::B, 1250);
    // メニュー画面のカーソルをタウンマップに戻す
    pushHat(Hat::LEFT, 25);
}

// 実際にループ内で呼び出す関数
void reciveAndHatchEggs(int box_line) {
    // 手持ちが1体の状態から、卵受け取り→孵化を繰り返していく
    for (int egg_num = 0; egg_num < 5; egg_num++) {
        moveToInitialPlayerPosition();
        getEggFromBreeder();
        pushButton(Button::X, 500);
        moveToInitialPlayerPosition();
        // 野生ポケモンとのエンカウントを避けるため初期位置から少し移動する
        tiltLeftStick(Stick::MAX, Stick::NEUTRAL, 500);
        runAround(TIME_TO_HATCHING_SEC);
        waitEggHatching();

        // 手持ちがいっぱいになったときの処理
        if (egg_num == 4) {
            // 孵化歩数の多いポケモンも孵化させてから預けるためのコード(下2行を無効にすると回転は上がるので、好みで削除すると良い)
            runAround(60);
            waitEggHatching();
            // ボックスに預ける処理を呼び出す
            sendHatchedPoemonToBox(box_line);

            // 手持ちがいっぱいでない場合は、メニューを開いてからループに戻る
        } else {
            pushButton(Button::X, 500);
        }
    }
}

// マイコンのセット時に1度だけ行われる処理
void setup() {
    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushButton(Button::B, 500, 5);

    // マイコンを認識したら、メニューの左上にカーソルを持っていく
    pushButton(Button::X, 600);
    holdHat(Hat::UP_LEFT, 750);

    // 空飛ぶを使うことで、位置情報をリセットする
    moveToInitialPlayerPosition();

    // 初めのタマゴが出現するまで走り回る
    tiltLeftStick(Stick::MAX, Stick::NEUTRAL, 500);
    runAround(25);

    // メニューを開く動作をループに含めてしまうと、毎回メニューを閉じないといけなくなってしまうため、ループから外すことにした
    pushButton(Button::X, 500);
}

// ここに記述した内容がループされ続ける
void loop() {
    for (int box_line = 0; box_line < 6; box_line++) {
        reciveAndHatchEggs(box_line);
    }
}
