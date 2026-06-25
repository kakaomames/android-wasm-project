#!/bin/bash
set -e

# ダウンロード先とファイル名
APK_URL="https://github.com/kakaomames/android-wasm-project/releases/download/Apks/pokemon.apks"
OUTPUT_FILE="pokemon.apks"

echo "📡 [Download] 補給物資を調達中..."

# -f: 404等のエラー時にcurlを失敗させる
# -L: リダイレクトを追う
# -o: 出力先指定
if curl -fL "$APK_URL" -o "$OUTPUT_FILE"; then
    echo "✅ [Success] 回収完了！"
else
    echo "❌ [Error] 補給物資が見当たらないぞ！（404 Not Found）"
    echo "URLを確認するか、リリースにファイルがあるかチェックだ。"
    exit 1 # ここで処理を止めるのが安全の要！
fi

# 以下、成功した場合の処理を続ける...
# java -jar APKEditor.jar ...
