#include <stdio.h>
#include <dlfcn.h>
#include "loader.h"

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
