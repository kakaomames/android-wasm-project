#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <emscripten.h>

// 各ユニットのヘッダーを読み込む
#include "cpu.h"
#include "gpu.h"
#include "loader.h"
#include "mem_shim.h"

/**
 * JS側から呼び出されるメインの起動関数
 * 司令室のボタン「CPUを起動！」からここに信号が飛ぶ
 */
EMSCRIPTEN_KEEPALIVE
void run_emulator() {
    printf("[System] Gem-OS 起動シグナルを受信！\n");

    // 1. メモリ空間の確保 (血液の循環を開始)
    init_guest_memory(1024 * 1024 * 64); // 64MB確保
    printf("[System] メモリ領域: 64MB 確保完了。\n");

    // 2. ユニットの初期化 (脳と眼を目覚めさせる)
    CPUState my_cpu;
    cpu_init(&my_cpu);
    gpu_init();
    printf("[System] CPU/GPU 初期化完了。\n");

    // 3. エミュレーション・メインループ
    // 本来は終了条件（終了コマンドや例外）まで無限ループする
    printf("[System] 演算サイクルを開始します...\n");
    
    // 動作テスト：まずは5ステップだけ動かしてみる
    for(int i = 0; i < 5; i++) {
        cpu_execute_step(&my_cpu);
        // ここでGPUへの描画指示などが今後入る
    }

    printf("[System] 演算サイクル終了。Gem-OSは待機状態に戻ります。\n");
}

/**
 * プログラムの起動エントリーポイント
 */
int main(int argc, char **argv) {
    printf("🚩 Gem-OS 司令塔: システム準備完了！\n");
    printf("JavaScript環境からの命令を待機しています...\n");

    // コマンドライン引数がある場合（ローカルでのデバッグ用）
    if (argc > 1) {
         printf("[CLI Mode] 引数としてファイル: %s を検出しました。\n", argv[1]);
         // 必要に応じてロード処理をここに実装
    }

    // ブラウザ環境では、この後JS側のボタンイベントで run_emulator() が呼ばれる
    return 0;
}
