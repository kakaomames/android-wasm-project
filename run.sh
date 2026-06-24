#!/bin/bash

# これを run.sh の一番上に追加！
export PATH=$PATH:/home/runner/work/android-wasm-project/android-wasm-project/retdec/bin
ls -F ./retdec/
git config user.name "github-actions[bot]"
git config user.email "github-actions[bot]@users.noreply.github.com"
# --- 初期設定 ---
# どこかで失敗したら即座に停止する設定
set -e

# ログ出力関数
missionLog() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] [MISSION LOG] $1: $2"
}

SOURCE_DIR="./libs"
OUTPUT_DIR="./output"

# ディレクトリがない場合は作成
if [ ! -d "$OUTPUT_DIR" ]; then
    missionLog "ACTION" "出力ディレクトリを作成中..."
    mkdir -p "$OUTPUT_DIR"
fi

# ファイルが存在するか確認
files=("$SOURCE_DIR"/*.so)
if [ ! -e "${files[0]}" ]; then
    missionLog "ERROR" "変換対象の.soファイルが見当たりません！"
    exit 1
fi

missionLog "START" "全20個（もしくはそれ以上）のバイナリ変換作戦を開始します！"

# --- ループ処理 ---
for lib in "${files[@]}"; do
    filename=$(basename "$lib" .so)
    
    missionLog "ACTION" "ターゲット [$filename] の攻略を開始します。"

    # 1. 逆コンパイル (RetDec)
    missionLog "INFO" "[$filename] をCコードへ逆コンパイル中..."
    if retdec-decompiler -a arm64 "$lib" -o "$OUTPUT_DIR/$filename.c"; then
        # git add ./$OUTPUT_DIR || true
        # git commit -m "build: update generated source code" || true
        # git push || true
        missionLog "SUCCESS" "[$OUTPUT_DIR/$filename.c] のCコード生成完了！"
        ls -F ./output/ | grep "/" || true
        ls -F $OUTPUT_DIR/ | grep ".c" || true 
    else
        missionLog "FAILURE" "[$filename] の逆コンパイルでエラー発生。"
        continue
    fi


    # 2. Wasmコンパイル (Emscripten)
    missionLog "INFO" "[$filename] をWasmへコンパイル中..."
    if emcc "$OUTPUT_DIR/$filename.c" -o "$OUTPUT_DIR/$filename.js" -s WASM=1 -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'; then
        missionLog "SUCCESS" "[$filename] のWasm化成功！"
    else
        missionLog "FAILURE" "[$filename] のコンパイルでエラー発生。"
        continue
    fi

    missionLog "COMPLETE" "[$filename] の全工程終了。"
done

missionLog "FINISH" "全ターゲットの変換作戦が完了しました！乾杯！🥂"
