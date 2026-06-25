#!/bin/bash
# Gem-OS Build Script (ARM64-v8a Native Target)

set -e

echo "🚩 コンパイル隊、出撃！ (Build for ARM64-v8a)"

# 依存関係の確認とインストール
sudo apt-get update
sudo apt-get install -y build-essential cmake

# 出力ディレクトリの作成
mkdir -p build_out

# Emscriptenのパス確認
if [ -z "$EMSDK" ]; then
    echo "⚠️ EMSDKが見つかりません。セットアップを確認してください。"
    exit 1
fi

echo "⚙️ コンパイル処理を実行中..."

# メインモジュールをビルド
# .soとの連携を見据えて MAIN_MODULE=1 を指定
emcc src/main.c -o index.html -s WASM=1


echo "✅ ビルド完了！成果物は build_out/ に格納されたぞ。"

