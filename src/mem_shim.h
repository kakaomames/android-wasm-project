// src/mem_shim.h
#ifndef MEM_SHIM_H
#define MEM_SHIM_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h> // ★これが必要だ！off_t を呼ぶために追加する

// ここが設計図だ！
typedef struct {
    uint8_t *base_ptr; 
    size_t current_offset;
    size_t max_size;
} MemoryManager;

// 外部変数として定義（実体は mem_shim.c に置く）
extern MemoryManager guest_mem;

// 関数のプロトタイプ宣言
void init_guest_memory(size_t total_size);
void* guest_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
uint32_t read_memory_u32(uint64_t address);

#endif
