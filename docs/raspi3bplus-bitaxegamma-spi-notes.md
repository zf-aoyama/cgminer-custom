# GPIO/SPI 接続メモ

USB ブリッジが利用できない場合に備え、Raspberry Pi 3B+ から bitaxe Gamma の BM1370 へ直接 SPI 接続する方法の予備調査結果をまとめます。

## 想定配線
- Raspberry Pi GPIO10 (MOSI) → bitaxe Gamma MOSI
- Raspberry Pi GPIO9  (MISO) → bitaxe Gamma MISO
- Raspberry Pi GPIO11 (SCLK) → bitaxe Gamma SCLK
- Raspberry Pi 任意の GPIO → bitaxe Gamma CS (チップセレクト)
- 3.3V レベルで接続し、必要に応じてレベルシフタを利用

## ソフトウェア側
- `spidev` ドライバーを有効にし `/dev/spidev0.*` を使用
- cgminer ドライバーでは libspi などを利用して ASIC へのコマンドを送信する実装が必要

現状は USB 接続を優先するため詳細実装は未定ですが、ハードウェアトラブル時の回避策として検討します。

