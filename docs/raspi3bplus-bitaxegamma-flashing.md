# bitaxe Gamma ファームウェア書き込み手順

以下の手順は、USB ブリッジ用ファームウェアを ESP32 に書き込む際の一例です。`firmware/usb-bridge` ディレクトリでビルドしたバイナリを使用します。

1. ESP32 を USB ケーブルで PC に接続し、ブートモードに入れます。
2. [esptool.py](https://docs.espressif.com/projects/esptool/en/latest/) をインストールしていることを確認します。
3. ビルド後に生成される `usb-bridge.bin` を 0x0 アドレスに書き込みます。

```bash
esptool.py --chip esp32 --baud 921600 write_flash 0x0 usb-bridge.bin
```

4. 書き込み完了後、ESP32 を再起動して cgminer からの接続を待ちます。
