# Raspberry Pi 3B+ と bitaxe Gamma 連携ソフトウェア仕様書

## システム概要
Raspberry Pi 3B+ 上でビルドした cgminer を用い、USB 接続された bitaxe Gamma を制御して Bitcoin マイニングを行います。
基本は USB 接続を想定し、USB が利用できない場合のみ GPIO/SPI 接続を検討します。本書ではビルド手順、設定ファイル、起動方法など実装に必要な詳細仕様をまとめます。

## ビルド手順
1. 依存パッケージのインストール:
   ```bash
   sudo apt-get update
   sudo apt-get install -y build-essential libusb-1.0-0-dev pkg-config
   ```
2. リポジトリ取得後、以下を実行して cgminer をビルドします。
   ```bash
   ./autogen.sh
   ./configure --enable-bitaxe
   make -j"$(nproc)"
   ```
3. ビルド後、`cgminer` バイナリが生成されます。

## 設定ファイル
- サンプルとして `example.conf` が用意されています。これをコピーして `cgminer.conf` を作成し、以下の項目を設定します。
  - `url`: 利用するマイニングプールの stratum URL
  - `user`: プールで登録したユーザー名またはウォレットアドレス
  - `pass`: パスワード (不要な場合は `x`)
  - `bitaxe_freq`: 必要に応じてハードウェアの周波数設定
- 設定例:
  ```json
  {
    "url": "stratum+ssl://pool.example.com:3333",
    "user": "myworker.1",
    "pass": "x",
    "bitaxe_freq": "350"
  }
  ```

## 起動・停止方法
- cgminer の起動:
  ```bash
  ./cgminer -c cgminer.conf
  ```
- 途中で停止する場合は `Ctrl+C` でプロセスを終了します。スクリプト化する場合は `cgminer` をバックグラウンドで起動し、PID 管理を行ってください。

## ログとモニタリング
- 実行時のログは標準出力と `cgminer.log` に記録できます。`--log-file` オプションを利用してください。
- ハッシュレートや温度情報はコンソール表示のほか、API を有効にすることで外部ツールから取得できます。

## エラーハンドリング
- デバイスが認識されない場合は `lsusb` で接続状態を確認します。
- cgminer からのエラーメッセージはログに記録し、再起動スクリプトに組み込むことで自動復旧を目指します。
