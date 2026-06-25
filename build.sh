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
mkdir -p build_out
# ビルドコマンドを修正してHTMLを生成する
emcc src/main.c src/loader.c -o build_out/index.html -s WASM=1 -s MAIN_MODULE=1


echo "🔎 コンパイル後のbuild_outの中身:"
ls -la build_out/

echo "🔍 ルートディレクトリの中身 (迷子を探す):"
ls -la .

# もしbuild_outが空なら、エラーで止めて原因を特定しやすくする
if [ ! -f "build_out/index.html" ]; then
    echo "❌ 警告: index.html が build_out/ に見当たらない！"
    exit 1
fi