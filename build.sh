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

# サイドモジュールビルド
emcc src/library.c -s SIDE_MODULE=1 -o library.js

# メインモジュールビルド (サイドモジュールの存在を意識する)
emcc src/main.c -s MAIN_MODULE=1 -s LINKABLE=1 -o index.html


# 【重要】本当にファイルがあるか確認する
echo "🔍 成果物の確認:"
ls -la build_out/