#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unicorn/unicorn.h> // 武器：Unicorn Engine

// 専門部隊のヘッダー
#include "loader.h"
#include "mem_shim.h"

// エミュレーションのメインループ
void run_emulator_loop() {
    uc_engine *uc;
    uc_err err;

    printf("[Emulator] 脳(CPU)を起動する...\n");

    // 1. ARM64モードでUnicornエンジンを初期化
    err = uc_open(UC_ARCH_ARM64, UC_MODE_ARM, &uc);
    if (err) {
        printf("[Emulator] 致命的エラー: Unicornエンジンが起動しない! (Error: %u)\n", err);
        return;
    }

    // 2. メモリ空間のリンク
    // mem_shimで確保した領域をUnicornにマッピングする (仮のアドレス 0x10000000)
    // ※実際にはAPKのベースアドレスをELF解析で特定してマッピングする
    uint64_t mem_addr = 0x10000000;
    size_t mem_size = 64 * 1024 * 1024; // 64MB
    uc_mem_map(uc, mem_addr, mem_size, UC_PROT_ALL);

    printf("[Emulator] メモリ空間(64MB)をCPUに接続完了。\n");

    // 3. CPUの実行開始 (まずはPCをエントリーポイントへ設定)
    printf("[Emulator] CPUサイクルを開始する...\n");
    // ※本来はここにloaderから読み込んだバイナリを書き込む処理が必要
    // err = uc_emu_start(uc, mem_addr, mem_addr + 0x1000, 0, 0);

    printf("[Emulator] エミュレーション待機中。プログラムをロードせよ！\n");

    uc_close(uc);
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
