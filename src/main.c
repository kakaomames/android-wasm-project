#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

// 各ユニットのヘッダー
#include "cpu.h"
#include "gpu.h"
#include "gps.h"
#include "loader.h"
#include "mem_shim.h"

// JSから直接呼べるようにエクスポート
EMSCRIPTEN_KEEPALIVE
void run_emulator() {
    printf("[System] Gem-OS 起動シグナルを受信！\n");

    // 1. メモリ空間の確保
    init_guest_memory(1024 * 1024 * 64);
    printf("[System] メモリ領域: 64MB 確保完了。\n");
    
    // Unityエンジンをロード！
    load_library("./libmain.so");
    load_library("./libunity.so");

    // 2. 全ユニットの初期化 (脳・眼・GPSを起動)
    CPUState my_cpu;
    cpu_init(&my_cpu);
    gpu_init();
    
    // GPSは初期状態として0,0からスタート
    gps_update(35.6895, 139.6917); // 東京の座標を初期値にしてみよう
    
    printf("[System] 全ユニットの初期化完了。\n");

    // 3. エミュレーション・メインループ
    printf("[System] 演算サイクルを開始します...\n");
    
    for(int i = 0; i < 5; i++) {
        cpu_execute_step(&my_cpu);
    }

    printf("[System] 演算サイクル終了。Gem-OSは待機状態です。\n");
}

// GPS更新をJSから受け取るためのラッパー
EMSCRIPTEN_KEEPALIVE
void update_gps_from_js(double lat, double lon) {
    gps_update(lat, lon);
}

int main(int argc, char **argv) {
    printf("🚩 Gem-OS 司令塔: システム準備完了！\n");
    printf("JavaScript環境からの命令を待機しています...\n");
    return 0;
}
