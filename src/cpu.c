#include "cpu.h"
#include <stdio.h>

void cpu_init(CPUState *cpu) {
    for(int i=0; i<31; i++) cpu->x[i] = 0;
    cpu->pc = 0x400000; // 仮のエントリーポイント
    cpu->sp = 0;
    cpu->nzcv = 0;
}

void cpu_execute_step(CPUState *cpu) {
    // 1. Fetch: メモリから命令を読み込む（今はダミーのログのみ）
    printf("[CPU] 実行中... PC: 0x%lx\n", cpu->pc);
    
    // 2. Decode/Execute: ここで命令を判定して分岐する
    // 例: if (opcode == 0x...) { ... }
    
    // 3. PCを更新 (基本は4バイト進める)
    cpu->pc += 4;
}
