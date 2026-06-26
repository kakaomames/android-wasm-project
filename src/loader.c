#include <stdio.h>
#include <dlfcn.h>
#include "loader.h"
#include <string.h>
#include "mem_shim.h"

void* lib_handle = NULL;

void load_library(const char* lib_name) {
    printf("[Loader] ライブラリのロードを開始: %s\n", lib_name);
    
    // dlopen でロードを試みる
    // RTLD_LAZY: 必要になるまでシンボルを解決しない（高速起動用）
    lib_handle = dlopen(lib_name, RTLD_LAZY);
    
    if (!lib_handle) {
        // ロード失敗！ここが勝負の分かれ目だ
        fprintf(stderr, "[Error] ロード失敗: %s\n", dlerror());
        return;
    }
    
    printf("[Loader] ロード成功！ハンドルアドレス: %p\n", lib_handle);
}
void copy_so_to_guest_memory(uint8_t *buffer, size_t size, const char *name) {
    // 1. guest_mmap で君のOS内の領域を確保
    void *dest = guest_mmap(NULL, size, 0, 0, 0, 0);
    
    if (dest != (void*)-1) {
        // 2. メモリコピー！
        memcpy(dest, buffer, size);
        printf("[Loader] %s をアドレス %p に配置した！\n", name, dest);
    } else {
        printf("[Loader] エラー: メモリ確保失敗！\n");
    }
}
