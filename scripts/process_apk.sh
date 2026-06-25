#!/bin/bash

# --- 設定項目 ---
APK_URL="https://github.com/kakaomames/android-wasm-project/releases/download/Apks/pokemon.apks"
INPUT_APK="pokemon.apks"
TEMP_DIR="tmp_build"
OUTPUT_JAR="app.jar"
DIST_ASSETS="dist/assets"
APK_EDITOR="APKEditor.jar" # ルートに配置されている前提

# --- エラーハンドリング設定 ---
# コマンドが失敗したら即停止、未定義変数はエラー、パイプラインの途中で失敗しても検知する
set -euo pipefail

echo "🚀 [Start] 変換作業を開始するぜ！"

# 1. 準備：ディレクトリ構造の確保
rm -rf "$TEMP_DIR" && mkdir -p "$TEMP_DIR"
mkdir -p "$DIST_ASSETS"

# 2. 補給物資（APK）の調達
echo "📡 [Download] $INPUT_APK を回収中..."
if ! curl -fL "$APK_URL" -o "$INPUT_APK"; then
    echo "❌ [Error] 補給物資の回収に失敗！URLを確認してくれ。"
    exit 1
fi

# 3. APKの正規化（Merge）
echo "🛠 [APKEditor] APKセットを統合中..."
if [ ! -f "$APK_EDITOR" ]; then
    echo "❌ [Error] $APK_EDITOR が見当たらないぞ！"
    exit 1
fi
java -jar "$APK_EDITOR" m -i "$INPUT_APK" -o "$TEMP_DIR/merged.apk"

# 4. アセットの抽出
echo "📦 [Extract] アセットを解凍中..."
unzip -q "$TEMP_DIR/merged.apk" -d "$TEMP_DIR/extracted"

# 5. ZIP圧縮（Web配信用のバンドル作成）
echo "🗜 [Zip] Web用アセットを固めているぜ..."
# assetsフォルダを固める。なければディレクトリごと作る
if [ -d "$TEMP_DIR/extracted/assets" ]; then
    cd "$TEMP_DIR/extracted"
    zip -r "../../$DIST_ASSETS/assets.zip" assets/
    cd ../..
    echo "✅ [Success] $DIST_ASSETS/assets.zip を作成完了！"
else
    echo "⚠️ [Warning] assetsフォルダが見つからなかった。ZIPは作成されなかったぞ。"
fi

# 6. 掃除
echo "🧹 [Cleanup] 一時ファイルを消去..."
rm -rf "$TEMP_DIR" "$INPUT_APK"

echo "🏁 [Finished] 全工程、異常なし！"
