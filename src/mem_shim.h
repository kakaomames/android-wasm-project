#ifndef MEM_SHIM_H
#define MEM_SHIM_H
#ifndef MAP_FAILED
#define MAP_FAILED ((void *)-1)
#endif

#include <stddef.h>
#include <sys/types.h>

// main.c から呼び出せるように公開する関数リスト
void init_guest_memory(size_t total_size);
void* guest_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

void init_guesttt_memory(size_t total_size);
void* guest_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

#endif
