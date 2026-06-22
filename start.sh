#!/bin/bash

# --- ターゲット設定 ---
AOSP_BASE_URL="https://android.googlesource.com/platform"
WORK_DIR="./aosp_core"

mkdir -p $WORK_DIR
cd $WORK_DIR

echo "🚀 AOSP公式からコアパーツを収穫開始..."

# 必要なリポジトリだけをピンポイントで取得 (sparse checkout等の技術も使えるが、まずはcloneで)
# 例: libutilsが含まれる system/core
git clone --depth 1 $AOSP_BASE_URL/system/core.git

# もし他のパーツも必要なら追加していく
# git clone --depth 1 $AOSP_BASE_URL/system/libbase.git

echo "✅ 収穫完了！公式最新ソースを確保したぞ。"
