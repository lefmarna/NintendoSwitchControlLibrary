/**
 * 指定された数のボックスに存在するポケモンをすべて逃がし、空の状態にするスケッチ
 *
 * 18行目の "const int BOX_COUNT = 2;" の箇所に、空にしたいボックス数を指定した状態（必ず半角数値で入力してください）で使用してください。
 * 【例："const int BOX_COUNT = 5;" と指定すると、5ボックス分のポケモンを逃がすコードになる】
 *
 * 初期条件は以下の通り
 * 1.Xボタンを押したときに「タウンマップ」が左上、「ポケモン」がその右にあること
 * 2.30匹フルにポケモンが預けられたボックスが続いた状態であること。（タマゴなど逃がせないポケモンが混じった状態はNG）
 * 3.無線のコントローラーが接続されていないこと
 * 4.「設定」から「話の速さ」を「速い」にしておくこと
 */

// ライブラリを読み込むためのコード
#include <NintendoSwitchControlLibrary.h>

// 何ボックス分逃がすかをここで指定する
const int BOX_COUNT = 2;

// ボタンを押した際の猶予時間
const int PUSH_BUTTON_DELAY = 500;
const int PUSH_HAT_DELAY = 50;

// ポケモンを逃がす関数
void releasePokemon() {
    // 「にがす」を選択
    pushButton(Button::A, PUSH_BUTTON_DELAY);
    pushHat(Hat::UP, PUSH_HAT_DELAY, 2);
    pushButton(Button::A, PUSH_BUTTON_DELAY);
    pushHat(Hat::UP, PUSH_HAT_DELAY);

    // 「本当に 逃がしますか？」
    pushButton(Button::A, 1000);
    pushButton(Button::A, PUSH_BUTTON_DELAY);
}

// 1ボックス分（30匹）ポケモンを逃がす関数
void releaseBox() {
    // 現在のボックスの列（左に移動するか、右に移動するかの判別に使用する）
    int boxline = 1;

    for (int i = 1; i <= 30; i++) {
        // ポケモンを逃がす
        releasePokemon();
        // 次のポケモンにカーソルを合わせる
        if (i % 6 == 0) {
            pushHat(Hat::DOWN, PUSH_HAT_DELAY);
            boxline++;
        } else if (boxline % 2 == 1) {
            pushHat(Hat::RIGHT, PUSH_HAT_DELAY);
        } else {
            pushHat(Hat::LEFT, PUSH_HAT_DELAY);
        }
    }

    // 次のボックスに移動する
    pushButton(Button::R, PUSH_BUTTON_DELAY);
    pushHat(Hat::DOWN, PUSH_HAT_DELAY, 2);
    pushHat(Hat::RIGHT, 500, 2);
}

void setup() {
    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushButton(Button::L, PUSH_BUTTON_DELAY, 5);

    // マイコンを認識したら、メニューの左上にカーソルを持っていく
    pushButton(Button::X, 750);
    holdHat(Hat::UP_LEFT, 1500);

    // ボックスを開く
    pushHat(Hat::RIGHT, PUSH_HAT_DELAY);
    pushButton(Button::A, 1250);
    pushButton(Button::R, 1500);
}

int loopCount = 0;
void loop() {
    // 指定されたボックス分のポケモンを逃し終えたら処理を終了する
    if (loopCount == BOX_COUNT) exit(0);

    releaseBox();
    loopCount++;
}
