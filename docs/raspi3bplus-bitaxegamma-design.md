# Raspberry Pi 3B+ で bitaxe Gamma を制御するための設計書

## 概要
このドキュメントでは、Raspberry Pi 3B+ から bitaxe Gamma を制御するためのシステム構成、ソフトウェア構成、および必要なハードウェア接続について説明します。

## 目標
- Raspberry Pi 3B+ を利用して bitaxe Gamma を制御し、Bitcoin マイニングを行う
- cgminer カスタムビルドを Raspberry Pi 上で実行し、USB 経由で bitaxe Gamma を操作
- ローカルネットワーク経由でマイニングプールに接続

## ハードウェア構成
1. **Raspberry Pi 3B+**
   - Raspbian もしくは Raspberry Pi OS をインストール
   - ネットワーク接続（有線または Wi-Fi）
   - USB ポートから bitaxe Gamma へ接続
2. **bitaxe Gamma**
   - BM1370 ASIC 搭載のシングルチップマイナー
   - 5V/4A 以上の電源を用意
   - 冷却用ヒートシンクおよび PWM ファン必須
3. **接続方法**
   - bitaxe Gamma の USB-C ポートを Raspberry Pi の USB ポートに接続
   - 必要に応じて USB-Hub を使用

## ソフトウェア構成
1. **ビルド環境の準備**
   - `build-essential`, `libusb-1.0-0-dev` などの依存パッケージを Raspberry Pi 上にインストール
   - リポジトリ内の `autogen.sh`、`configure --enable-bitaxe` を実行し、`make` で cgminer をビルド
2. **設定ファイル**
   - 必要に応じて `example.conf` を参考にマイニングプール情報やデバイス設定を `cgminer.conf` として作成
3. **起動方法**
   - `./cgminer -c cgminer.conf` を実行し、bitaxe Gamma が認識されているか確認
   - マイニング状況はコンソール上、または Web インターフェース（必要に応じて設定）から確認

## 運用時の注意点
- 電源は 5V を厳守し、安定した供給を行う
- 冷却ファンが常に動作しているか確認し、温度上昇に注意
- Raspberry Pi の USB 電力供給能力は限られるため、必要に応じてセルフパワー型 USB ハブを使用する
- システムログや cgminer のログは定期的に確認し、エラーやハッシュレートの低下を監視する

## 参考リンク
- [bitaxeGamma リファレンス](../reference/bitaxeGamma/readme.md)
- [ESP-Miner プロジェクト](../reference/ESP-Miner)

## アーキテクチャ概要
システムは以下の構成要素で実装します。
- **cgminer 本体**: bitaxe ドライバを組み込んだマイニングエンジン。
- **設定ファイル (cgminer.conf)**: マイニングプール情報やデバイス設定を保持。
- **管理スクリプト**: cgminer の起動・停止、ログローテーションを行うシェルスクリプト。
- **モニタリングツール**: cgminer の API 機能を用いてハッシュレートや温度を取得し、必要に応じて通知します。

各コンポーネントは Raspberry Pi 上で動作し、USB 接続された bitaxe Gamma へコマンドを送信します。API を有効にすることで外部から状態を取得でき、複数台運用時の集中管理も容易になります。

## cgminer からの直接制御について
bitaxe Gamma は標準では ESP32 上で ESP-Miner が動作しており、Wi-Fi 経由で単体マイニングが可能です。USB ケーブルで Raspberry Pi に接続するだけでは cgminer から ASIC を制御できません。cgminer で利用する場合は専用ドライバーの実装と、USB ブリッジ用のファームウェアが必要となります。詳細は `raspi3bplus-bitaxegamma-driver-tasks.md` を参照してください。
