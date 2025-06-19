# USB ブリッジファームウェア設計書

## 概要
本ファームウェアは ESP32 を USB ブリッジとして動作させ、ホスト上の cgminer から BM1370 ASIC へ SPI 経由でハッシュ計算を指示するものです。通信プロトコルは `raspi3bplus-bitaxegamma-protocol.md` で定義したバイナリパケットを用います。

## システム構成
- **ホスト (Raspberry Pi など)**
  - cgminer が USB CDC 経由でファームウェアと通信
- **ESP32 (USB ブリッジファームウェア)**
  - tinyusb の CDC-ACM クラスでシリアルデバイスを実装
  - SPI 経由で BM1370 を制御
- **BM1370 ASIC**
  - 1 チップ構成のため SPI 配線は MOSI/MISO/SCLK/CS の 4 本

## ソフトウェア構成
1. **main.c / app_main**
   - 初期化処理を行い、USB タスクと ASIC タスクを生成
2. **usb_bridge.c**
   - CDC からの受信データを解析し、パケットごとに処理
   - `HELLO`、`WORK`、`RESULT`、`ERROR` の各パケット処理を提供
3. **bm1370_driver.c**
   - SPI 通信をラップし、ASIC へのコマンド送信と結果取得を行う
   - 既存の `reference/ESP-Miner` から必要な関数を流用
4. **task 管理**
   - FreeRTOS キューで WORK データを受け渡しし、ASIC 処理の完了を通知
5. **設定項目**
   - SPI クロック周波数やリセットピン番号は `menuconfig` で変更可能とする

## 処理フロー
1. 電源投入後、USB デバイスとして認識されるまで待機
2. cgminer から `HELLO` を受信するとバージョン文字列を応答
3. `WORK` パケット受信時に ASIC へデータを書き込み、計算結果を `RESULT` で送信
4. エラー発生時は `ERROR` パケットで通知し、必要に応じて ASIC をリセット

## ログ出力
- 開発時は `ESP_LOGI/ESP_LOGE` を利用して USB シリアルへログを出力
- 量が多い場合はビルドオプションでレベルを調整

## ビルド方法
`firmware/usb-bridge` で以下を実行します。
```bash
idf.py build
```
生成された `usb-bridge.bin` を ESP32 に書き込み、ホストから `/dev/ttyACM*` 経由で接続します。

