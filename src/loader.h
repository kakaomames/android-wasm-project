#ifndef LOADER_H
#define LOADER_H

#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

// エクスポートする関数をここで定義
void load_library(const char* lib_name);
void load_elf_to_guest(uint8_t *file_data, const char *name);
int adaptive_open(const char *pathname, int flags, mode_t mode);
int ensure_dir_exists(const char *path);

#ifdef __cplusplus
}
#endif

#endif
