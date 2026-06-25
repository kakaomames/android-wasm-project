#ifndef LOADER_H
#define LOADER_H

#include <fcntl.h>
#include <sys/stat.h>

// ヘッダーファイル：これを読み込めばloaderの機能が使える
int adaptive_open(const char *pathname, int flags, mode_t mode);
int ensure_dir_exists(const char *path);
void load_library(const char* lib_name);

#endif
