#ifndef MEM_SHIM_H
#define MEM_SHIM_H

#include <stddef.h>
#include <sys/types.h>

// main.c から呼び出せるように公開する関数リスト
void init_guest_memory(size_t total_size);
void* guest_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

#endif // MEM_SHIM_H
