// ライブラリを読み込むためのコード
#include <NintendoSwitchControlLibrary.h>

// マイコンのセット時に1度だけ行われる処理
void setup() {
    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushButton(Button::B, 500, 5);
}

// ここに記述した内容がループされ続ける
void loop() {
    pushButton(Button::A, 100);
}
