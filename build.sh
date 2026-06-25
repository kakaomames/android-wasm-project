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
# 出力先を明示的に指定（もしディレクトリを作っていないならここで作る）
mkdir -p build_out

emcc src/main.c \
    -O3 \
    -s WASM=1 \
    -s MAIN_MODULE=1 \
    -o build_out/index.html  # index.htmlにすればJSとWasmも一緒にできる
# サイドモジュールのコンパイル (SIDE_MODULE=1)
emcc library.c -s SIDE_MODULE=1 -o library.wasm

# メインモジュールのコンパイルはそのまま
# 実行時にライブラリをロードするJSコードが必要になる


# 【重要】本当にファイルがあるか確認する
echo "🔍 成果物の確認:"
ls -la build_out/