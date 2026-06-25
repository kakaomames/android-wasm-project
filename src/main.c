#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unicorn/unicorn.h> // 武器：Unicorn Engine

// 専門部隊のヘッダー
#include "loader.h"
#include "mem_shim.h"
// エミュレーションのメインループ
#include "cpu.h"

void run_emulator_loop() {
    CPUState my_cpu;
    cpu_init(&my_cpu);
    
    printf("[Emulator] Gem-CPU 起動！命令の解釈を開始する...\n");
    
    // 10ステップだけ試しに動かしてみるテスト
    for(int i=0; i<10; i++) {
        cpu_execute_step(&my_cpu);
    }
    
    printf("[Emulator] 試運転完了！\n");
}


int main(int argc, char **argv) {
    printf("🚩 Gem-OS 司令塔: 起動完了！\n");

    if (argc < 2) {
        printf("Usage: ./gem-os <path_to_so_file>\n");
        return 1;
    }

    // 1. メモリ空間の確保
    init_guest_memory(1024 * 1024 * 64);

    // 2. SOファイルのロード
    const char *so_path = argv[1];
    printf("[Main] SOファイル読み込み任務開始: %s\n", so_path);

    int fd = adaptive_open(so_path, O_RDONLY, 0);
    if (fd < 0) {
        printf("[Main] 致命的エラー: SOファイルが開けない！\n");
        return 1;
    }

    // 3. エミュレーション開始
    printf("[Main] メモリ確保完了、SOファイルロード成功！エミュレータへ引き継ぐ。\n");
    run_emulator_loop();

    // 後始末
    close(fd);
    printf("🚩 Gem-OS 司令塔: 任務完了。\n");
    return 0;
}
