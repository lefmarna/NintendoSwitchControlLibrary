/**
 * 育て屋から卵を回収→孵化→ボックスに預けるを繰り返すスケッチ
 * ボックスに空きがある限り、ポケモンを孵化し続ける
 *
 * 初期条件は以下の通り
 * 1.ズイタウンにいること
 * 2.ショートカットに自転車のみが登録された状態であること（＋ボタンで自転車に乗れること）
 * 3.自転車を4速にしておくこと
 * 4.手持ちが「ほのおのからだ」の特性持ちの1体のみのこと
 * 5.「まるいおまもり」を所持していること
 * 6.Xボタンを押したときに「タウンマップ」が左上、「ポケモン」がその右にあること
 * 7.空のボックスが続いた状態であること
 * 8.無線のコントローラーが接続されていないこと
 * 9.「設定」から「話の速さ」を「速い」に、「手持ち／ボックス」を「自動で送る」に、「ニックネーム登録」を「しない」にしておくこと
 */

// ライブラリを読み込むためのコード
#include <NintendoSwitchControlLibrary.h>

// 孵化サイクルを設定する
const int EGG_CYCLE = 40;

// 孵化するまでに自転車で走り回る時間（試行錯誤の末にこのような形となったが、まだ練りきれていないところがある）
const int TIME_TO_HATCHING_SEC = (EGG_CYCLE * 10) - 10;

// 空飛ぶでズイタウンに移動する関数
void moveToInitialPlayerPosition() {
    pushButton(Button::A, 2000);
    pushButton(Button::A, 1000, 2);
    delay(7000);
}

// 初期位置から育て屋さんに移動しタマゴを受け取る関数
void getEggFromBreeder() {
    // 初期位置(ズイタウンのポケモンセンター)から育て屋さんのところまで移動
    tiltLeftStick(Stick::MIN, Stick::NEUTRAL, 735);
    tiltLeftStick(Stick::NEUTRAL, Stick::MIN, 1250);
    tiltLeftStick(Stick::MIN, Stick::NEUTRAL, 735);
    // 育て屋さんから卵をもらう
    pushButton(Button::A, 500);
    pushButton(Button::B, 500, 2);
    pushButton(Button::A, 500, 2);
    pushButton(Button::B, 500, 2);
    pushButton(Button::A, 500);
    pushButton(Button::B, 500, 10);
}

// 初期位置(ズイタウンのポケモンセンター)からタマゴが孵化するまで走り回る関数
void runAround(int run_time_sec) {
    tiltLeftStick(Stick::MIN, Stick::NEUTRAL, 560);
    pushButton(Button::PLUS, 600);
    tiltLeftStick(Stick::NEUTRAL, Stick::MIN, 5900);
    // 孵化サイクル分の走行（チェック周期を考慮して-1からスタート）
    for (int i = -1; i < run_time_sec / 21; i++) {
        tiltLeftStick(Stick::NEUTRAL, Stick::MAX, 10400);
        tiltLeftStick(Stick::NEUTRAL, Stick::MIN, 10400);
    }
    tiltLeftStick(Stick::NEUTRAL, Stick::MAX, (run_time_sec % 21) * 1000);
}

// タマゴが孵化するのを待つ関数
void waitEggHatching() {
    pushButton(Button::B, 500, 30);
    delay(4000);
}

// 孵化した手持ちのポケモンをボックスに預ける関数
// box_line : 何列目にポケモンを預けるか
void sendHatchedPokemonToBox(int box_line) {
    // ボックスを開く
    pushButton(Button::X, 500);
    pushHat(Hat::RIGHT, 50);
    pushButton(Button::A, 1250);
    pushButton(Button::R, 1500);
    // 手持ちの孵化したポケモンを範囲選択
    pushHat(Hat::LEFT, 50);
    pushHat(Hat::DOWN, 50);
    pushButton(Button::Y, 50);
    pushButton(Button::Y, 50);
    pushButton(Button::A, 50);
    holdHat(Hat::DOWN, 1200);
    pushButton(Button::A, 50);
    // ボックスに移動させる
    pushHat(Hat::RIGHT, 100, box_line + 1);
    pushHat(Hat::UP, 50);
    pushButton(Button::A, 50);
    // ボックスがいっぱいになったら、次のボックスに移動させる
    if (box_line == 5) {
        pushHat(Hat::UP, 50);
        pushHat(Hat::RIGHT, 500);
    }
    // ボックスを閉じる
    pushButton(Button::B, 50);  // ボックスが空でなかった場合でも、ボックスを閉じてループを実行し続けさせるのに必要な記述
    pushButton(Button::B, 1500);
    pushButton(Button::B, 1250);
    // メニュー画面のカーソルをタウンマップに戻す
    pushHat(Hat::LEFT, 50);
}

// 実際にループ内で呼び出す関数
void receiveAndHatchEggs(int box_line) {
    // 手持ちが1体の状態から、卵受け取り→孵化を繰り返していく
    for (int egg_num = 0; egg_num < 5; egg_num++) {
        moveToInitialPlayerPosition();
        getEggFromBreeder();
        pushButton(Button::X, 500);
        moveToInitialPlayerPosition();
        runAround(TIME_TO_HATCHING_SEC);
        waitEggHatching();
        // 「そらをとぶ」を使う前に、ズイタウンにいることを確定させる
        tiltLeftStick(Stick::NEUTRAL, Stick::MIN, 10400);
        tiltLeftStick(Stick::NEUTRAL, Stick::MAX, 4800);
        // 手持ちがいっぱいになったときの処理
        if (egg_num == 4) {
            // ボックスに預ける処理を呼び出す
            sendHatchedPokemonToBox(box_line);
            // 手持ちがいっぱいでない場合は、メニューを開いてからループに戻る
        } else {
            pushButton(Button::X, 500);
        }
    }
}

// マイコンのセット時に1度だけ行われる処理
void setup() {
    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushButton(Button::A, 500, 5);
    
    // マイコンを認識したら、メニューの左上にカーソルを持っていく
    pushButton(Button::X, 750);
    holdHat(Hat::UP_LEFT, 1500);

    // 「そらをとぶ」を使うことで、位置情報をリセットする
    moveToInitialPlayerPosition();

    // 初めのタマゴが出現するまで走り回る
    tiltLeftStick(Stick::MIN, Stick::NEUTRAL, 560);
    pushButton(Button::PLUS, 600);
    tiltLeftStick(Stick::NEUTRAL, Stick::MIN, 5900);
    tiltLeftStick(Stick::NEUTRAL, Stick::MAX, 10400);
    tiltLeftStick(Stick::NEUTRAL, Stick::MIN, 10400);
    tiltLeftStick(Stick::NEUTRAL, Stick::MAX, 4800);

    // メニューを開く動作をループに含めてしまうと、毎回メニューを閉じないといけなくなってしまうため、ループから外すことにした
    pushButton(Button::X, 500);
}

// ここに記述した内容がループされ続ける
void loop() {
     for (int box_line = 0; box_line < 6; box_line++) {
         receiveAndHatchEggs(box_line);
     }
}
