/**
 * 訓練場で警備隊のタキとの連戦を行い、レベル上げと早業・力業のタスクを埋めていくスケッチ
 *
 * ※2匹のポケモンが倒される or PP切れで技が使えなくなるとループが止まってしまうので注意！
 *
 *
 * 初期条件は以下の通り
 * 1.ストーリークリア済であること（クリア前でも環境が揃っていれば可能かと思いますが、動作は未検証です）
 * 2.コトブキムラ訓練場前のノボリの前にいること
 * 3.手持ちの1匹目に強力なポケモンを配置し、初手のポケモンは別のポケモンであること
 * 4.2匹のポケモンそれぞれの一番上の技に使用する技を配置しておくこと
 * 5.無線のコントローラーが接続されていないこと
 * 6.「設定」から「話の速さ」を「速い」にしておくこと
 */

// ライブラリを読み込むためのコード
#include <NintendoSwitchControlLibrary.h>

// 早業・力業のパターンを決める（0: ランダム, 1: 早業のみ, 2: 力業のみ）
const int PATTERN = 0;

// ボタン入力の間隔（個人で調整してOK。早すぎると早業・力業の切り替えができないことがある）
const int INTERVAL = 400;

// PATTERNの値を元に打ちこむコマンドを決める
int hats[2];
void decideCommands() {
    switch (PATTERN) {
        // 早業のみ
        case 1:
            hats[0] = Hat::LEFT;
            hats[1] = Hat::LEFT;
            break;

        // 力業のみ
        case 2:
            hats[0] = Hat::RIGHT;
            hats[1] = Hat::LEFT; /* NOTE ポケモン交換時に右入力すると技を選択してしまうことがあるため、脱却するために力業のみの場合も左入力が必要 */
            break;

        // ランダム
        default:
            hats[0] = Hat::LEFT;
            hats[1] = Hat::RIGHT;
    }
}

// マイコンのセット時に1度だけ行われる処理
void setup() {
    // ループ内で打ち込むコマンドを反映する（Switchの操作に関わらないため、認識前でも問題なく動作する）
    decideCommands();

    // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
    pushHat(Hat::LEFT, 500, 5);
}

// ここに記述した内容がループされ続ける
void loop() {
    pushButton(Button::A, INTERVAL);
    pushHat(hats[0], INTERVAL);
    pushButton(Button::A, INTERVAL);
    pushHat(hats[1], INTERVAL);

    // 2番（力業のみ）を選択したときは、早業経由で力業を選択する
    if (PATTERN == 2) {
        pushHat(Hat::LEFT, INTERVAL);
    }
}
