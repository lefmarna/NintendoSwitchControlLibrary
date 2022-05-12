/**
 * 孵化はせずにタマゴだけをひたすら受け取っていくスケッチ
 *
 * 初期条件は以下の通り
 * 1.ハシノマはらっぱにいること
 * 2.自転車に乗っていること
 * 3.手持ち6匹全てがポケモンで埋まっていること
 * 4.Xボタンを押したときに「タウンマップ」が左上、「ポケモン」がその右にあること
 * 5.オフライン状態であること
 * 6.無線のコントローラーが接続されていないこと
 * 7.「設定」から「話の速さ」を「速い」に、「手持ち／ボックス」を「自動で送る」に、「ニックネーム登録」を「しない」にしておくこと
 * 8.ちょいらくモードが「しない」であること
 * 9.まるいおまもりを所持していること
 */

// ライブラリを読み込むためのコード
#include <NintendoSwitchControlLibrary.h>

// タマゴを受け取るまでの間隔(数値が大きいほど間隔が長くなる)
const int INTERVAL = 15;

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

// 実際にループ内で呼び出す関数
void receiveEggs(int box_line) {
    // 手持ちが1体の状態から、卵受け取り→孵化を繰り返していく
    for (int egg_num = 0; egg_num < 5; egg_num++) {
        moveToInitialPlayerPosition();
        getEggFromBreeder();
        pushButton(Button::X, 500);
        moveToInitialPlayerPosition();
        // 野生ポケモンとのエンカウントを避けるため初期位置から少し移動する
        tiltLeftStick(Stick::MAX, Stick::NEUTRAL, 500);
        runAround(INTERVAL);
        pushButton(Button::X, 500);
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
    runAround(INTERVAL);

    // メニューを開く動作をループに含めてしまうと、毎回メニューを閉じないといけなくなってしまうため、ループから外すことにした
    pushButton(Button::X, 500);
}

// ここに記述した内容がループされ続ける
void loop() {
    for (int box_line = 0; box_line < 6; box_line++) {
        receiveEggs(box_line);
    }
}