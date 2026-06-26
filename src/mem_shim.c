#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include "mem_shim.h"
#include <string.h>

// dlopen の代わりに使うモック
void* dlopen(const char *filename, int flags) {
    printf("[Shim] dlopen が呼ばれた: %s\n", filename);
    
    // ここで君のローダーを呼び出す！
    // 例: load_library_into_guest_memory(filename);
    
    // 成功したと仮定して、擬似的なハンドルを返す
    return (void*)0x12345678; 
}

void* dlsym(void *handle, const char *symbol) {
    printf("[Shim] dlsym が呼ばれた: %s\n", symbol);
    // ここでメモリマップからシンボルのアドレスを検索する関数を呼ぶ
    return NULL; // アドレスが見つかったらそれを返す
}

int dlclose(void *handle) {
    printf("[Shim] dlclose が呼ばれた\n");
    return 0;
}


MemoryManager guest_mem = {0};

void init_guest_memory(size_t total_size) {
    guest_mem.base_ptr = malloc(total_size);
    guest_mem.current_offset = 0;
    guest_mem.max_size = total_size;
    printf("[Memory] APK用仮想メモリを %zu バイト確保した！\n", total_size);
}

// 簡易的な mmap 模擬関数
void* guest_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
    // 境界チェック
    if (guest_mem.current_offset + length > guest_mem.max_size) {
        printf("[Memory] エラー: メモリ不足！これ以上割り当てられない！\n");
        return MAP_FAILED;
    }

    void *allocated_ptr = guest_mem.base_ptr + guest_mem.current_offset;
    guest_mem.current_offset += length;

    printf("[Memory] 割り当て成功: %zu バイト (開始アドレス: %p)\n", length, allocated_ptr);
    
    // ここでメモリをゼロクリアしておく（セキュリティ対策）
    // memset(allocated_ptr, 0, length);
    
    return allocated_ptr;
}
