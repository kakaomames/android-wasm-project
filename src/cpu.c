#include "cpu.h"
#include <stdio.h>

void cpu_execute_step(CPUState *cpu) {
    // 1. Fetch: メモリから命令を取得 (今はダミー)
    // uint32_t insn = memory_read(cpu->pc);
    
    // 2. Decode & Execute: 簡易的なディスパッチャー
    // 実際にはここのswitch文に、ARM64の命令セットを少しずつ増やしていく！
    printf("[CPU] PC: %lx を実行中...\n", cpu->pc);
    
    // PCを進める
    cpu->pc += 4;
}
