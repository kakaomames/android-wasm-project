#include "loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <libgen.h>

// --- 自己修復機能: 階層を再帰的に作る ---
int ensure_dir_exists(const char *path) {
    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);
    if (tmp[len - 1] == '/') tmp[len - 1] = 0;
    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            mkdir(tmp, S_IRWXU);
            *p = '/';
        }
    }
    return mkdir(tmp, S_IRWXU);
}

// --- 罠（ハニーポット）: ファイルオープンをフック ---
int adaptive_open(const char *pathname, int flags, mode_t mode) {
    int fd = open(pathname, flags, mode);

    // ファイルがなくてエラーになった場合、自動修復を試みる
    if (fd < 0 && errno == ENOENT) {
        printf("[Shim] トラップ発動: %s が見つからない。ディレクトリを自動構築する...\n", pathname);
        
        char *path_copy = strdup(pathname);
        char *dir = dirname(path_copy);
        ensure_dir_exists(dir);
        free(path_copy);

        // 再度オープンを試みる
        fd = open(pathname, flags, mode);
        if (fd >= 0) {
            printf("[Shim] 自動修復成功: %s を構築したぞ！\n", pathname);
        }
    }
    return fd;
}
