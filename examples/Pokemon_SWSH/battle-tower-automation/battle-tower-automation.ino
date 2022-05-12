/**
 * バトルタワーでのBP稼ぎを自動化するスケッチ
 *
 * 初期条件は以下の通り
 * 1.バトルタワーの受付の前で待機していること
 * 2.レンタルチームに 0000 0003 M4XW JG をレンタルしておくこと
 * 3.上記のチームがバトルチーム選択で最初に来るようにすること
 * 4.無線のコントローラーが接続されていないこと
 * 5.「設定」から「話の速さ」を「速い」に、「戦闘アニメ」を「みない」にしておくこと
 * 6.ちょいらくモードが「しない」であること
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
    pushButton(Button::ZL, 2800);
    pushButton(Button::A, 800);
    pushButton(Button::A, 800);
    pushButton(Button::B, 800);
    pushHat(Hat::UP);
    pushButton(Button::ZL, 2800);
    pushButton(Button::A, 1050);  // ここは少し長めにとらないと、参加画面で詰んでしまう
    pushButton(Button::ZL, 2800);
    pushButton(Button::A, 800);
    pushHat(Hat::UP);
    pushButton(Button::ZL, 2800);
    pushButton(Button::A, 800);
    pushHat(Hat::UP);
    pushButton(Button::ZL, 3300);
}