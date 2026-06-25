#include <stdio.h>
#include <unistd.h> // これが必要だ！
#include <fcntl.h>  // open() を使うならこれも重要だ
#include "loader.h" // ローダーの機能も忘れずに


int main(int argc, char **argv) {
    printf("🚩 Gem-OS 司令塔: 起動！\n");

    if (argc < 2) {
        printf("Usage: ./gem-os <path_to_so_file>\n");
        return 1;
    }

    const char *so_path = argv[1];
    printf("[Main] SOファイル読み込み任務開始: %s\n", so_path);

    // 専門部隊の adaptive_open を通してSOファイルにアクセス
    int fd = adaptive_open(so_path, O_RDONLY, 0);
    
    if (fd < 0) {
        printf("[Main] 致命的エラー: SOファイルが開けない！調査せよ！\n");
        return 1;
    }

    printf("[Main] SOファイルのロード成功！エミュレーションを開始する。\n");

    // ここに将来的にELF解析やCPUエミュレーションのコードを追加していく
    
    close(fd);
    printf("🚩 Gem-OS 司令塔: 任務完了。\n");
    return 0;
}
