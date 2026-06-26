#ifndef LOADER_H
#define LOADER_H

#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h> // uint8_t のために必要

#ifdef __cplusplus
extern "C" {
#endif

int adaptive_open(const char *pathname, int flags, mode_t mode);
int ensure_dir_exists(const char *path);
void load_library(const char* lib_name);
// 追記：これがないと main.c から呼べない
void load_elf_to_guest(uint8_t *file_data, const char *name);

#ifdef __cplusplus
}
#endif

#endif
