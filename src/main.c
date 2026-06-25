#include <stdio.h>
#include <dlfcn.h>

int main() {
    // コンパイル時に指定したライブラリをロード
    void *handle = dlopen("library.wasm", RTLD_NOW);
    if (!handle) {
        printf("Error: Could not load library\n");
        return 1;
    }

    // 関数ポインタを取得
    int (*add_func)(int, int) = dlsym(handle, "add");
    
    // 実行
    int result = add_func(10, 20);
    printf("Result from dynamic library: %d\n", result);

    dlclose(handle);
    return 0;
}
