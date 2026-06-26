#include <stdio.h>
#include <string.h>
#include <elf.h>
#include "loader.h"
#include "mem_shim.h"

// dlopenは使わない。ELFを直接パースする
void load_elf_to_guest(uint8_t *file_data, const char *name) {
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)file_data;

    // ELFヘッダー確認
    if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0) {
        printf("[Error] %s はELFファイルではない\n", name);
        return;
    }

    printf("[Loader] ELFパース開始: %s\n", name);

    Elf32_Phdr *phdr = (Elf32_Phdr *)(file_data + ehdr->e_phoff);

    for (int i = 0; i < ehdr->e_phnum; i++) {
        // ロード可能なセグメントのみ処理
        if (phdr[i].p_type == PT_LOAD) {
            size_t mem_size = phdr[i].p_memsz;
            size_t file_size = phdr[i].p_filesz;
            
            // guest_mmapを叩く
            void *dest = guest_mmap(NULL, mem_size, 0, 0, 0, 0);
            
            if (dest == (void*)-1) {
                printf("[Error] メモリ配置失敗 (Segment %d)\n", i);
                return;
            }

            // データコピー
            memcpy(dest, file_data + phdr[i].p_offset, file_size);
            
            // BSS領域がある場合、残りをゼロクリア
            if (mem_size > file_size) {
                memset(dest + file_size, 0, mem_size - file_size);
            }
            
            printf("[Loader] Segment %d 配置完了: %p (Size: %zu)\n", i, dest, mem_size);
        }
    }
    printf("[Loader] %s 展開完了\n", name);
}
