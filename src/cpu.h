#ifndef CPU_H
#define CPU_H

#include <stdint.h>

// ARM64のレジスタを模倣する
typedef struct {
    uint64_t x[31]; // X0-X30
    uint64_t pc;    // プログラムカウンタ
    uint64_t sp;    // スタックポインタ
    uint32_t nzcv;  // フラグ
} CPUState;

// CPUの状態を初期化する
void cpu_init(CPUState *cpu);

// 1命令だけ実行する（ここが命令解釈のメインになる）
void cpu_execute_step(CPUState *cpu);

#endif
