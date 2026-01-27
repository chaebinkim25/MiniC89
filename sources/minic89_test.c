#include <stdio.h>
#include "minic89_vm.h"
#include "minic89_builder.h"

// 디버깅 출력을 위한 Opcode 이름 배열 (테스트 파일 전용)
static const char* OP_NAMES[] = {
    "NOP", "DBG_LINE",
    "PUSH_I16", "PUSH_FUN", "PUSH_NULL", "POP", "DUP",
    "LOAD", "STORE",
    "ADD", "SUB", "MUL", "DIV", "MOD", "NEG",
    "EQ", "NE", "LT", "LE", "GT", "GE", "LNOT",
    "JMP", "JZ", "JNZ",
    "CALL", "CALL_IND", "RET",
    "HALT"
};

// 현재 상태 출력 헬퍼 함수
void print_state(VM* vm, int step, Instruction inst) {
    // 1. Step, FID, IP 출력
    printf("[Step %02d] FID:%-2d IP:%-2d | ", step, vm->pc_fid, vm->pc_ip);
    
    // 2. 명령어 출력
    // Opcode 범위 체크
    const char* op_name = (inst.opcode <= OP_HALT) ? OP_NAMES[inst.opcode] : "UNKNOWN";
    printf("INST: %-10s %5d | ", op_name, inst.operand);

    // 3. 스택 출력
    printf("STACK: [ ");
    for (int i = 0; i < vm->sp; i++) {
        Value v = vm->stack[i];
        if (v.type == VAL_I16)
            printf("%d ", v.as.i_val);
        else if (v.type == VAL_FUN)
            printf("F%d ", v.as.fun_id);
        else
            printf("? ");
    }
    printf("]\n");
}

int main() {
    VM vm;
    Builder b;

    // 1. 초기화
    vm_init(&vm);         // minic89_vm.c 에 정의됨
    builder_init(&b, &vm); // minic89_builder.c 에 정의됨

    printf("=== 1. Building Bytecode ===\n");

    // -------------------------------------------------
    // 시나리오: int abs(int x) { if (x<0) return -x; return x; }
    // -------------------------------------------------
    u16 fid_abs = builder_begin_func(&b, "abs", 1, 1); // arg:1, local:1
    
    int L_else = builder_new_label(&b);

    emit_load(&b, 0);       // Load x
    emit_push(&b, 0);       // Push 0
    emit_op(&b, OP_LT);     // x < 0 ?
    emit_jmp_label(&b, OP_JZ, L_else); // False(0)이면 L_else로 점프

    // [Then Block] (x < 0)
    emit_load(&b, 0);
    emit_op(&b, OP_NEG);    // -x
    emit_ret(&b);

    // [Else Block]
    builder_mark_label(&b, L_else); // 레이블 위치 마킹
    emit_load(&b, 0);       // Load x
    emit_ret(&b);

    builder_end_func(&b);
    printf("Compiled function 'abs' -> ID: %d\n", fid_abs);

    // -------------------------------------------------
    // 시나리오: int main() { return abs(-99); }
    // -------------------------------------------------
    u16 fid_main = builder_begin_func(&b, "main", 0, 0);
    
    emit_push(&b, -99);     // 인자: -99
    emit_call(&b, fid_abs); // abs 호출
    emit_op(&b, OP_HALT);   // 종료

    builder_end_func(&b);
    printf("Compiled function 'main' -> ID: %d\n", fid_main);


    // 2. VM 실행
    printf("\n=== 2. Running VM ===\n");
    
    // Entry Point 설정
    vm.pc_fid = fid_main;
    vm.pc_ip = 0;

    int step = 0;
    while (vm.running && vm.trap == TRAP_NONE) {
        // 현재 명령어를 미리 가져옴 (출력용)
        Instruction curr = vm.functions[vm.pc_fid].code[vm.pc_ip];
        
        print_state(&vm, step++, curr);
        
        // 실제 실행 (vm_step은 내부에서 pc_ip를 증가시킴)
        vm_step(&vm);
    }

    // 3. 결과 확인
    printf("==============================\n");
    if (vm.trap != TRAP_NONE) {
        printf("RUNTIME ERROR (TRAP): %d\n", vm.trap);
    } else {
        Value res = (vm.sp > 0) ? vm.stack[vm.sp - 1] : (Value){0};
        printf("Execution Finished Successfully.\n");
        printf("Result: %d (Expected: 99)\n", res.as.i_val);
    }

    // (참고: 실제 구현 시에는 생성된 functions[].code 메모리 해제 필요)
    return 0;
}
