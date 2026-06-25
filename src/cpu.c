#include "cpu.h"
#include "mem_shim.h"
#include <stdio.h>


// mem_shim.c で定義されたメモリ管理構造体を参照するための宣言
extern MemoryManager guest_mem; 

// --- ここにプロトタイプ宣言を追加して紹介状を渡す ---
uint32_t read_memory_u32(uint64_t address); // mem_shim.h にも書くべきだが、とりあえずここで宣言
void execute_mov(CPUState *cpu, uint32_t opcode);
void execute_add(CPUState *cpu, uint32_t opcode);
// --------------------------------------------------
// src/mem_shim.c に追加
uint32_t read_memory_u32(uint64_t address) {
    // 境界チェックは後回しにして、まずは動かす！
    // guest_mem.base_ptr は前回作った構造体の中にあるはずだ
    // 実際のアドレスを計算して返す
    return *(uint32_t*)(guest_mem.base_ptr + address);
}


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

// --- 命令の実体（魂）を実装 ---

void execute_mov(CPUState *cpu, uint32_t opcode) {
    // 簡易MOV: 下位16ビットをX0レジスタに入れる
    uint64_t imm = opcode & 0xFFFF;
    cpu->x[0] = imm;
    printf("[CPU] MOV 命令実行: X0 に 0x%llx をロード\n", cpu->x[0]);
}

void execute_add(CPUState *cpu, uint32_t opcode) {
    // 簡易ADD: X0 = X0 + 1 (デバッグ用)
    cpu->x[0] += 1;
    printf("[CPU] ADD 命令実行: X0 が 0x%llx になった\n", cpu->x[0]);
}

