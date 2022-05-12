/**
 * パッチルドンの受け取りを自動化するスケッチ
 *
 * 初期条件は以下の通り
 * 1.無線のコントローラーが接続されていないこと
 * 2.「設定」から「話の速さ」を「速い」に、「手持ち／ボックス」を「自動で送る」に、「ニックネーム登録」を「しない」にしておくこと
 * 3.ちょいらくモードが「しない」であること
 */

// ライブラリを読み込むためのコード
#include <NintendoSwitchControlLibrary.h>

// マイコンのセット時に1度だけ行われる処理
void setup() {
    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushButton(Button::B, 500, 5);
}

// ここに記述した内容がループされ続ける
void loop() {
    pushButton(Button::A, 650, 2);
    pushButton(Button::A, 800);
    pushHat(Hat::DOWN, 25);
    pushButton(Button::A, 800);
    pushButton(Button::A, 650, 2);
    delay(2350);
    pushButton(Button::B, 200, 35);
}