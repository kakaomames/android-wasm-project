#ifndef CPU_H
#define CPU_H
#include <stdint.h>

typedef struct {
    uint64_t x[31]; // 汎用レジスタ
    uint64_t pc;    // プログラムカウンタ
    uint64_t sp;    // スタックポインタ
} CPUState;

void cpu_execute_step(CPUState *cpu); // 命令を1つずつ解釈する
#endif
