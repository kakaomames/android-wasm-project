#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
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
        
        // ディレクトリパスを抽出して生成
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

// --- メイン処理: SOファイルのロード準備 ---
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <path_to_so_file>\n", argv[0]);
        return 1;
    }

    const char *so_path = argv[1];
    printf("[Loader] SOファイル読み込み開始: %s\n", so_path);

    // まずはバイナリとして開いてみる（テスト）
    int fd = adaptive_open(so_path, O_RDONLY, 0);
    if (fd < 0) {
        printf("[Loader] 致命的エラー: SOファイルが見つからない\n");
        return 1;
    }

    // ここでELFのヘッダーチェック等を行うのが次の任務だ
    printf("[Loader] SOファイルをメモリに展開する準備OK！\n");

    close(fd);
    return 0;
}
