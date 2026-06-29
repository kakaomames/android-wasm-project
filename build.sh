#!/bin/bash
# Gem-OS Build Script (ARM64-v8a Native Target)

set -e

echo "🚩 コンパイル隊、出撃！ (Build for ARM64-v8a)"

# 依存関係の確認とインストール
sudo apt-get update
sudo apt-get install -y build-essential cmake
TIME=$(date)
echo "$TIME" > 2log.txt

# 出力ディレクトリの作成
mkdir -p build_out
rm -rf aosp_core || true
# Emscriptenのパス確認
if [ -z "$EMSDK" ]; then
    echo "⚠️ EMSDKが見つかりません。セットアップを確認してください。"
    exit 1
fi


echo "⚙️ コンパイル処理を実行中..."

echo "emcc start!"

# src/gpu.c を忘れずに追加した完全版コマンド
# 全ユニットを統合するコマンド
EMCC_DEBUG=1 emcc /main.c \
    -o build_out/game_core.js \
    -s WASM=1 \
    -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap','HEAPU8']" \
    -s "EXPORTED_FUNCTIONS=['_main','_run_emulator','_update_gps_from_js']" \
    -s ASSERTIONS=1 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1 \
    -s ALLOW_MEMORY_GROWTH=1
echo "emcc end..."











echo "🔎 コンパイル後のbuild_outの中身:"
ls -la build_out/

echo "必要な関数の一覧を出す（依存関係の確認）"



echo "🔍 ルートディレクトリの中身 (迷子を探す):"
ls -la .

