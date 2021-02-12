/**
 * 初期条件は以下の通り
 * 1.エキスパンションパスを購入済みであること
 * 2.ダイマックスアドベンチャーの「エンドレスモード」を解放済みであること
 * 3.「マックスダイ巣穴」内の清掃員前で待機していること
 * 4.オフライン状態であること
 * 5.無線のコントローラーが接続されていないこと
 * 6.「設定」から「話の速さ」を「速い」にしておくこと
 * 7.モンスターボールを大量に用意し、ボールの先頭に設定しておくこと
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
    pushHat(Hat::DOWN, 2000);
    pushButton(Button::A, 2000, 5);
    delay(2000);
    pushHat(Hat::DOWN, 2000);
    pushButton(Button::A, 2000);
    pushHat(Hat::DOWN, 2000);
    pushButton(Button::A, 2000, 2);
    pushHat(Hat::DOWN, 2000);
    pushButton(Button::A, 2000, 2);
    pushButton(Button::B, 3000);
    holdButton(Button::B, 1500);
}
