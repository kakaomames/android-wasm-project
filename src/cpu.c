#include "cpu.h"
#include <stdio.h>

void cpu_init(CPUState *cpu) {
    for(int i=0; i<31; i++) cpu->x[i] = 0;
    cpu->pc = 0x400000; // 仮のエントリーポイント
    cpu->sp = 0;
    cpu->nzcv = 0;
}

void cpu_execute_step(CPUState *cpu) {
    // 1. Fetch: メモリから命令を取得 (今はメモリマップから直接読む)
    uint32_t opcode = read_memory_u32(cpu->pc); 
    printf("[CPU] 実行中... PC: 0x%llx, Opcode: 0x%08x\n", cpu->pc, opcode);

    // 2. Decode & Execute: 命令を判定して実行
    // ここでビット演算をして命令の「種類」を判別する
    if ((opcode & 0xFF000000) == 0x52000000) {
        // 例えば、MOV命令のバイナリパターンなら...
        execute_mov(cpu, opcode);
    } else if ((opcode & 0xFF000000) == 0x8B000000) {
        // ADD命令なら...
        execute_add(cpu, opcode);
    } else {
        printf("[CPU] 未知の命令です！ 0x%08x\n", opcode);
    }
    
    // 3. PCを更新
    cpu->pc += 4;
}
