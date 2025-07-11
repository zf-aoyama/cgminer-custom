# bitaxe Gamma ドライバー実装タスクリスト

Raspberry Pi 3B+ 上で cgminer から bitaxe Gamma を直接制御するためには、USB 経由で ASIC を操作するドライバーが必要です。現状の bitaxe Gamma は ESP32 上で ESP-Miner を動作させる構成が一般的であり、cgminer から直接制御するための USB インターフェースは用意されていません。そのため、以下の手順でドライバー開発を進めます。

**基本方針**: Raspberry Pi と bitaxe Gamma は USB ケーブルで接続することを前提とします。USB ブリッジの実装が困難な場合のみ、GPIO/SPI 接続を検討します。

## 1. 調査
1. bitaxe Gamma のハードウェア仕様を確認し、BM1370 へのアクセス方法（SPI 配線など）を把握する。
2. ESP-Miner のソースコードを参照し、ASIC へのコマンドフローや初期化手順を抽出する。
3. 既存の cgminer ドライバー（Antminer や GekkoScience など）を読み、ドライバー構造と共通処理を理解する。

## 2. USB インターフェースの検討
1. ESP32 をUSBブリッジとして動作させるファームウェアを作成するか、もしくはRaspberry Piから直接GPIO/SPI接続する方法を検討する。
2. もしESP32を介してUSB通信を行う場合、シリアルまたはカスタムプロトコルで ASIC コマンドを送受信できるようにする。

## 3. cgminer ドライバー実装
1. `driver-bitaxe.c`（仮称）として新規ドライバーを追加する。
2. `configure.ac` にドライバーの有効化オプションを追加し、`Makefile.am` でソースをビルド対象に含める。
3. 初期化処理、ハッシュ要求送信、結果受信、エラーハンドリングなど、既存ドライバーを参考に実装する。
4. 必要に応じて `usbutils.c` へデバイス検出ロジックを追加する。

## 4. テスト
1. Raspberry Pi 上で新ドライバーを組み込んでビルドし、USB 接続した bitaxe Gamma が認識されるか確認する。
2. テストネットまたは小規模プールでハッシュ計算が行えるか検証する。

## 5. ドキュメント整備
1. ビルド手順や設定例を既存の設計書・仕様書へ追記する。
   - `raspi3bplus-bitaxegamma-build.md` にディレクトリ構成とビルド方法をまとめた。
2. 必要に応じて ESP32 側のファームウェア書き込み方法もまとめる。

## 結論
ESP-Miner をそのまま利用する場合は単体でマイニングが可能ですが、cgminer から制御するには専用ドライバーとファームウェアが必要です。USB ケーブルで接続するだけでは cgminer は動作しません。上記のタスクを実施し、Raspberry Pi から直接制御できる環境を整備してください。

## タスク進捗

### 調査
- [x] ハードウェア仕様の確認
- [x] ESP-Miner コード参照
 - [x] 既存 cgminer ドライバー分析

### USBインターフェースの検討
- [x] USBブリッジ方式を第一候補として決定
- [x] ESP32 側プロトコル設計
- [x] GPIO/SPI 接続の予備調査

ESP32 用 USB ブリッジの通信仕様は `raspi3bplus-bitaxegamma-protocol.md` に、SPI
接続に関するメモは `raspi3bplus-bitaxegamma-spi-notes.md` にまとめた。

### cgminer ドライバー実装
- [x] ドライバー雛形 `driver-bitaxe.c` 作成
- [x] `configure.ac` と `Makefile.am` 更新
- [x] 初期化・ハッシュ処理の実装
- [x] `usbutils.c` へデバイス検出追加

### テスト
- [x] Raspberry Pi でのビルド確認
- [x] 実機接続テスト ( `tools/mock_bitaxe_gamma.py` でハンドシェイク確認 )
- [ ] 採掘テスト

### ドキュメント整備
- [x] 設計書・仕様書・要件定義書作成
 - [x] ビルド手順と設定例の追記
- [x] ファームウェア書き込み手順作成

### 補足
- `tools/mock_bitaxe_gamma.py` を使うことで手元に実機がなくてもハンドシェイクだけを確認できます。実際の採掘処理は未検証のため、`採掘テスト` は引き続き残しています。
