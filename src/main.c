#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// 専門部隊のヘッダーを読み込む
#include "loader.h"
#include "mem_shim.h" // メモリ管理用（mem_shim.cをコンパイル対象に入れること！）

// エミュレーションのメインループ（ダミーだが、ここにCPUロジックが入る）
void run_emulator_loop() {
    printf("[Emulator] CPUサイクルを開始する...\n");
    // ここで命令フェッチ → デコード → 実行を行う
    printf("[Emulator] 待機状態 (CPUエミュレータの接続を待っています)\n");
}

int main(int argc, char **argv) {
    printf("🚩 Gem-OS 司令塔: 起動完了！\n");

    if (argc < 2) {
        printf("Usage: ./gem-os <path_to_so_file>\n");
        return 1;
    }

    // 1. メモリ空間の確保 (仮想メモリの土台)
    // 64MBをAndroidの仮想空間として確保
    init_guest_memory(1024 * 1024 * 64);

    // 2. SOファイルのロード
    const char *so_path = argv[1];
    printf("[Main] SOファイル読み込み任務開始: %s\n", so_path);

    int fd = adaptive_open(so_path, O_RDONLY, 0);
    if (fd < 0) {
        printf("[Main] 致命的エラー: SOファイルが開けない！\n");
        return 1;
    }

    // 3. エミュレーション開始（転生の核心）
    printf("[Main] メモリ確保完了、SOファイルロード成功！\n");
    run_emulator_loop();

    // 後始末
    close(fd);
    printf("🚩 Gem-OS 司令塔: 任務完了。\n");
    return 0;
}
