#!/bin/bash
# Gem-OS Build Script (ARM64-v8a Native Target)

set -e

echo "🚩 コンパイル隊、出撃！ (Build for ARM64-v8a)"

# 依存関係の確認とインストール
sudo apt-get update
sudo apt-get install -y build-essential cmake

# 出力ディレクトリの作成
mkdir -p build_out
rm -rf aosp_core || true
# Emscriptenのパス確認
if [ -z "$EMSDK" ]; then
    echo "⚠️ EMSDKが見つかりません。セットアップを確認してください。"
    exit 1
fi


echo "⚙️ コンパイル処理を実行中..."
mkdir -p build_out
curl -Lv "https://github.com/kakaomames/android-wasm-project/releases/download/Apks/pokemon.apks" -o pokemon.apks && mkdir pokemon && unzip pokemon.apks -d pokemon
APK=$(ls -F ./pokemon/ | grep arm64) || APK=""  || true
echo "$APK"  || true
rm -rf "arm64" || true
mkdir arm64 || true
ls -F . | grep .apk
echo "mkdir"
rm -rf pokemon.apks || true
echo "rm pokemon.apks"
unzip pokemon/$APK -d arm64 || true
echo "unzip"
ls -F
rm -rf pokemon/ || true
echo "rm pokemon/"
cp -rfv arm64/lib/arm64-v8a lib/ || true
ls -F
echo "cp"
rm -rf arm64 || true
echo "rm arm64"
cp -rfvT lib/ build_out/ || true
ls -F
sed -i 's|</body>|<script src="js.js"></script>\n</body>|' build_out/1.html

# src/gpu.c を忘れずに追加した完全版コマンド
# 全ユニットを統合するコマンド
emcc src/main.c src/loader.c src/mem_shim.c src/cpu.c src/gpu.c src/gps.c src/media.c \
    -o build_out/1.html \
    -s WASM=1 \
    -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap','HEAPU8']" \
    -s "EXPORTED_FUNCTIONS=['_main','_run_emulator','_update_gps_from_js']" \
    -s ALLOW_MEMORY_GROWTH=1










echo "🔎 コンパイル後のbuild_outの中身:"
ls -la build_out/

echo "🔍 ルートディレクトリの中身 (迷子を探す):"
ls -la .

