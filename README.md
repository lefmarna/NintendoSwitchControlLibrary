# NintendoSwitchControlLibrary

Arduino を使って Nintendo Switch のゲームを自動化する、マイコン用のライブラリです。

![demo](https://user-images.githubusercontent.com/49473970/107502281-d0cc6c80-6bdb-11eb-9928-fb0a29744df6.gif)

## ⭐️ このライブラリについて

このライブラリはcelclow氏の[SwitchControlLibrary](https://github.com/celclow/SwitchControlLibrary)を参考にして作られています。

SwitchControlLibraryは自由度が高いものの、コードが冗長になりやすい点、ArduinoSTLを使用するためコンパイルに時間がかかる点などがネックでした。

そこで、一般的によく使われる入力のパターンを厳選して関数にまとめることにしました。

ボタンを押して離すまでの処理が1行で書けるようになり、より効率的に自動化プログラムを組むことができるようになります。連打や長押しの処理にも対応させ、汎用性の高いプログラムに仕上げました。

そしてなにより、ArduinoSTLを使わずにこれらの処理を実装することに成功しています。これによりコンパイルが高速に行えるほか、依存関係に悩まされなくなっていることも特徴です。

## 🔹 導入方法

### 必要なもの

- Arduino Leonardo
- USBケーブル（Arduino LeonardoとSwitchやPCを接続するのに必要）

### 動作環境

- Arduino IDE（1.8.13推奨）
- Arduino AVR Boards（1.8.3推奨）

詳しい導入の手順については、ブログで解説していますので、そちらをご覧ください。

[マイコンを導入して、ポケモン剣盾を自動化しよう！【Mac・Windows】｜ポケモニット](https://pokemonit.com/micon-introduction/)

## ⚠️ 注意点

Arduino Leonardo については、ブログ内で紹介しているものを推奨しています。その他のArduinoでは動作確認を行っておりません。異なるものを使用している場合には、質問にも一切答えられませんので予めご了承ください。

Arduino IDEやボードのバージョンは、基本的に最新の安定版のものを使って動作確認しています。古いバージョンでも使えるとは思いますが、動作を保証するものではありません。

なお、Nintendo Switchのバージョンには指定がありません。どのバージョンでも問題なく動作するはずです。

## 📄 使い方

ライブラリを使いたいファイルの先頭に以下のように記載してください。

```
#include <NintendoSwitchControlLibrary.h>
```

これでライブラリを読み込み、各種コマンドを使うことができるようになります。

単体で完結しているため、ArduinoSTL や [SwitchControlLibrary](https://github.com/celclow/SwitchControlLibrary) といった別のライブラリを読み込む必要はありません。

**SwitchControlLibrary とは競合するため、同時に読み込むことはできません**が、NintendoSwitchControlLibrary は SwitchControlLibrary（v2 系）を継承して作られているため、SwitchControlLibraryのコマンドも使用することが可能となっています。（ArduinoSTLを使用していない都合で、十字キーのコマンドのみ動作が少し異なりますが、基本的には同じように使うことができます）

## ⌨️ コマンド一覧

### ボタン

- ボタンを押すコマンド（連打にも対応）
  
  - `pushButton(uint16_t button, int delay_time = 0, int loop = 1)`
  
    - button: 押すボタン
    - delay_time: ボタンを押した後の待ち時間（1秒 = 1000）
    - loop: ボタンを押す回数（省略可、デフォルトは1）
  
  - 使用例
  
    ```
    pushButton(Button::HOME);        // HOMEボタンを入力する
    pushButton(Button::A, 500);      // Aボタンを入力後、0.5秒待機する
    pushButton(Button::B, 3000, 10); // 3秒おきにBボタンを入力する、それを10回繰り返す
    ```

- ボタンを長押しするコマンド
  
  - `holdButton(uint16_t button, int hold_time)`
  
    - button: 押し続けるボタン
    - hold_time: ボタンを押す時間の長さ（1秒 = 1000）
  
  - 使用例
  
    ```
    holdButton(Button::L, 2000);       // Lボタンを2秒間押し続けてから離す
    holdButton(Button::CAPTURE, 1500); // キャプチャーボタンを1.5秒間押し続けてから離す
    ```

- `Button` 定義一覧

  ```
  Button::Y
  Button::B
  Button::A
  Button::X
  Button::L
  Button::R
  Button::ZL
  Button::ZR
  Button::MINUS
  Button::PLUS
  Button::LCLICK
  Button::RCLICK
  Button::HOME
  Button::CAPTURE
  ```

### 十字キー（方向ボタン）

- 十字キー（方向ボタン）を押すコマンド（連打にも対応）

  - `pushHat(uint8_t hat, int delay_time = 0, int loop = 1);`
  
    - hat: 押す十字キーのボタン
    - delay_time: ボタンを押した後の待ち時間（1秒 = 1000）
    - loop: ボタンを押す回数（省略可、デフォルトは1）

  - 使用例

    ```
    pushHat(Hat::UP);          // 上キーを1回だけ入力する
    pushHat(Hat::LEFT, 1000);  // 左キーを入力後、1秒待機する
    pushHat(Hat::DOWN, 25, 5); // 0.25秒おきに下キーを入力する、それを5回繰り返す
    ```
    
- 十字キー（方向ボタン）を長押しするコマンド

  - `holdHat(uint8_t hat, int hold_time);`
  
    - hat: 押し続ける十字キーのボタン
    - hold_time: ボタンを押す時間の長さ（1秒 = 1000）

  - 使用例
  
    ```
    holdHat(Hat::RIGHT, 5000);   // 右キーを5秒間押し続けてから離す
    holdHat(Hat::UP_LEFT, 2500); // 十字キーを左上方向に2.5秒間押し続けてから離す
    ```

- `Hat` 定義一覧

    ```
    Hat::UP
    Hat::UP_RIGHT
    Hat::RIGHT
    Hat::DOWN_RIGHT
    Hat::DOWN
    Hat::DOWN_LEFT
    Hat::LEFT
    Hat::UP_LEFT
    Hat::NEUTRAL
    ```

### スティック

スティックの座標は、128を基点として 0〜255 の値を指定します。

0・128・255 の3つの値はStickで定義されているため、置き換えて使用することもできます（0 = MIN, NEUTRAL = 128, MAX = 255）

- 左スティックを操作するコマンド

  - `tiltLeftStick(uint8_t lx, uint8_t ly, int tilt_time);`
  
    - lx: 左スティックのx軸
    - ly: 左スティックのy軸
    - tilt_time: スティックを傾ける時間の長さ

  - 使用例
  
    ```
    tiltLeftStick(0, 128, 5000);                      // 左スティックを左に5秒間倒す
    tiltLeftStick(Stick::NEUTRAL, Stick::MAX, 15000); // 左スティックを下に15秒間倒す
    ```

- 右スティックを操作するコマンド

  - `tiltRightStick(uint8_t rx, uint8_t ry, int tilt_time);`
  
    - rx: 右スティックのx軸
    - ry: 右スティックのy軸
    - tilt_time: スティックを傾ける時間の長さ

  - 使用例
  
    ```
    tiltRightStick(255, 128, 100);                 // 右スティックを右に0.1秒間倒す
    tiltRightStick(Stick::MAX, Stick::MIN, 10000); // 右スティックを右上に10秒間倒す
    ```

- 左右のスティックを同時に操作するコマンド

  - `tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry, int tilt_time);`
  
    - lx: 左スティックのx軸
    - ly: 左スティックのy軸  
    - rx: 右スティックのx軸
    - ry: 右スティックのy軸
    - tilt_time: スティックを傾ける時間の長さ

  - 使用例
  
    ```
    tiltLeftAndRightStick(128, 255, 0, 128, 1000);                                  // 左スティックを下に、右スティックを左に10秒間倒す
    tiltLeftAndRightStick(Stick::MAX, Stick::MAX, Stick::MIN, Stick::MIN, 30000);   // 左スティックを右下に、右スティックは左上に、30秒間倒す
    ```

- `Stick` 定義一覧

  ```
  Stick::MIN
  Stick::NEUTRAL
  Stick::MAX
  ```

### SwitchControlLibraryを使ったその他のコマンド

このライブラリはSwitchControlLibraryのコマンドも内蔵しているため、合わせて使用することもできます。（**v2 系を採用しています。v1 系とは互換性がないことに注意してください**）

上記のもので対応できないものがある場合には、活用してみるといいかもしれません。

サンプルとして、ポケモン剣盾でバックアップデータの読み込みを行うコマンドを用意してみました。

```
SwitchControlLibrary().pressButton(Button::B);
SwitchControlLibrary().pressButton(Button::X);
SwitchControlLibrary().pressHatButton(Hat::UP); // ※SwitchControlLibraryと異なり、moveHatは使えません。 pressHatButtonに統合されています。
SwitchControlLibrary().sendReport();            // B、X、↑ボタンが同時に送信される
delay(100);
SwitchControlLibrary().releaseButton(Button::B);
SwitchControlLibrary().releaseButton(Button::X);
SwitchControlLibrary().releaseHatButton();      // ※SwitchControlLibraryと異なり、引数は指定しません。（十字キーをニュートラルポジションに戻す処理となる）
SwitchControlLibrary().sendReport();            // B、X、↑ボタンを同時に離す
```

## 🎮 サンプルコード

examplesフォルダに、ポケモン剣盾で使えるサンプルコードをまとめています。その中でも選りすぐりのものを紹介します。

### 自動孵化

自動孵化のコードは3つ用意しています。中でも、**auto-hatch-eggs**のコードはかなり研究したものなのですごく自信があります。

1. **auto-hatch-eggs.ino**
   - 一度書き込んでしまえば、どんなポケモンでも効率的に自動孵化が行える汎用的なコード！
   - 詳細はこちら → [【マイコン】どんなポケモンでも効率的に自動孵化させる汎用コードを作ってみた【剣盾】｜ポケモニット](https://pokemonit.com/swsh-auto-hatch-eggs/)
2. **auto-hatch-eggs_shiny.ino**
   - 色違いを狙う際など、特定のポケモンをピンポイントで孵化させるのに最適なコード！
   - 詳細はこちら → [【マイコン】ポケモン剣盾で自動孵化！色違いの厳選に最適なコードを紹介！｜ポケモニット](https://pokemonit.com/swsh-auto-hatch-eggs-2/)
3. **hatch-eggs-in-the-box.ino**
   - タマゴは受け取らずに、ボックスにあるタマゴをひたすら割っていくコード！
   - 詳細はこちら → [【マイコン】ポケモン剣盾のボックスに眠っているタマゴを孵化していくコード！｜ポケモニット](https://pokemonit.com/swsh-hatch-eggs-in-the-box/)

### その他のコード

- **auto-gain-watt.ino**
  - 自動ワット稼ぎのコード！（ランクバトルを行っていない状態での自動化プログラムとなります。）
  - 詳細はこちら → [【マイコン】ポケモン剣盾のワット稼ぎを自動化！スイッチのVer11以降に対応！｜ポケモニット](https://pokemonit.com/swsh-auto-gain-watt/)
- **dracovish.ino**
  - ウオノラゴンの受け取りを自動化するコード！
  - 詳細はこちら → [【マイコン】ウオノラゴンの受け取りを自動化！｜ポケモニット](https://pokemonit.com/swsh-auto-dracovish/)
- **dynamax-adventure**
  - ダイマックスアドベンチャーのエンドレスモードを自動で攻略し、マックスこうせきを稼ぐコード！
  - 詳細はこちら → [【マイコン】ダイマックスアドベンチャーを自動化！エンドレスモードの周回でマックス鉱石稼ぎ！｜ポケモニット](https://pokemonit.com/dynamax-adventure/)
- **battle-tower-automation**
  - バトルタワーでのBP稼ぎを自動化するコード！（『冠の雪原』に対応）
  - 詳細はこちら → [](https://pokemonit.com/swsh-battle-tower-automation/)

## 🎁 さいごに

このライブラリは暫定的なものなので、要望や改善案、追加してほしい機能などありましたら、[Issues](https://github.com/lefmarna/NintendoSwitchControlLibrary/issues)から気軽に投げかけてくださいませ。

画像認識のような高度なものを作るのは難しいかもしれませんが、入力プログラムの応用の範囲でしたら対応できるかと思います。

## ©️ ライセンス

[MIT](https://github.com/lefmarna/NintendoSwitchControlLibrary/blob/master/LICENSE)
