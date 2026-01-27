#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// ==========================================
// 1. VM 데이터 구조 정의 (Header 내용 포함)
// ==========================================

#define MAX_STACK 1024
#define MAX_CALL_STACK 64
#define MAX_LOCALS 16
#define MAX_FUNCTIONS 16

typedef int16_t  i16;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef enum {
    VAL_UNINIT = 0,
    VAL_I16,
    VAL_FUN
} ValType;

typedef struct {
    ValType type;
    union {
        i16 i_val;
        u16 fun_id;
    } as;
} Value;

typedef enum {
    OP_NOP, OP_DBG_LINE,
    OP_PUSH_I16, OP_PUSH_FUN, OP_PUSH_NULL, OP_POP, OP_DUP,
    OP_LOAD, OP_STORE,
    OP_ADD, OP_RET, OP_CALL, OP_HALT
} Opcode;

// 디버깅용 Opcode 이름 매핑
const char* OP_NAMES[] = {
    "NOP", "DBG_LINE",
    "PUSH_I16", "PUSH_FUN", "PUSH_NULL", "POP", "DUP",
    "LOAD", "STORE",
    "ADD", "RET", "CALL", "HALT"
};

typedef struct {
    u8 opcode;
    i16 operand;
} Instruction;

typedef struct {
    const char* name;
    u8 param_count;
    u8 local_count;
    Instruction* code;
    u16 code_size;
} Function;

typedef struct {
    u16 return_fid; // 호출자의 함수 ID
    u16 return_ip;  // 호출자의 복귀 IP
    Value locals[MAX_LOCALS];
} Frame;

typedef enum {
    TRAP_NONE = 0,
    TRAP_STACK_OVERFLOW, TRAP_STACK_UNDERFLOW,
    TRAP_CALL_STACK_OVERFLOW,
    TRAP_INT_OVERFLOW,
    TRAP_BAD_FUNID, TRAP_BAD_LOCAL, TRAP_BAD_JUMP,
    TRAP_UNINIT_READ, TRAP_TYPE_MISMATCH
} TrapReason;

const char* TRAP_NAMES[] = {
    "NONE", "STACK_OVERFLOW", "STACK_UNDERFLOW", "CALL_STACK_OVERFLOW",
    "INT_OVERFLOW", "BAD_FUNID", "BAD_LOCAL", "BAD_JUMP",
    "UNINIT_READ", "TYPE_MISMATCH"
};

typedef struct {
    Function functions[MAX_FUNCTIONS];
    u16 function_count;

    u16 pc_fid;  // 현재 함수 ID
    u16 pc_ip;   // 현재 명령어 인덱스
    
    Value stack[MAX_STACK];
    int sp;

    Frame frames[MAX_CALL_STACK];
    int fp;

    bool running;
    TrapReason trap;
    u16 current_source_line;
} VM;

// ==========================================
// 2. VM 헬퍼 함수
// ==========================================

Value VAL_INT(i16 v) { return (Value){ .type = VAL_I16, .as.i_val = v }; }

void vm_init(VM* vm) {
    memset(vm, 0, sizeof(VM));
    vm->running = true;
    // fp는 -1에서 시작하지 않고, 0번 프레임을 main용으로 사용한다고 가정
    vm->fp = 0; 
}

// 스택 푸시/팝 매크로 (간소화)
#define PUSH(val) vm->stack[vm->sp++] = (val)
#define POP() vm->stack[--vm->sp]
#define PEEK() vm->stack[vm->sp - 1]

// ==========================================
// 3. 인터프리터 코어 (vm_step)
// ==========================================

void vm_step(VM* vm) {
    if (!vm->running || vm->trap != TRAP_NONE) return;

    // 1. Fetch
    if (vm->pc_fid < 1 || vm->pc_fid > vm->function_count) {
        vm->trap = TRAP_BAD_FUNID; return;
    }
    Function* func = &vm->functions[vm->pc_fid];
    
    if (vm->pc_ip >= func->code_size) {
        vm->trap = TRAP_BAD_JUMP; return;
    }
    Instruction inst = func->code[vm->pc_ip];
    
    // PC 증가
    vm->pc_ip++;

    // 2. Decode & Execute
    switch (inst.opcode) {
        case OP_NOP: break;
        case OP_DBG_LINE: vm->current_source_line = inst.operand; break;

        case OP_HALT: 
            vm->running = false; 
            break;

        case OP_PUSH_I16:
            PUSH(VAL_INT(inst.operand));
            break;

        case OP_POP:
            if (vm->sp > 0) vm->sp--;
            else vm->trap = TRAP_STACK_UNDERFLOW;
            break;

        case OP_LOAD: {
            int slot = inst.operand;
            Value v = vm->frames[vm->fp].locals[slot];
            if (v.type == VAL_UNINIT) { vm->trap = TRAP_UNINIT_READ; return; }
            PUSH(v);
            break;
        }

        case OP_STORE: {
            // STORE는 값을 팝하지 않고(표현식 결과), 로컬에 복사만 함
            int slot = inst.operand;
            if (vm->sp == 0) { vm->trap = TRAP_STACK_UNDERFLOW; return; }
            vm->frames[vm->fp].locals[slot] = PEEK();
            break;
        }

        case OP_ADD: {
            if (vm->sp < 2) { vm->trap = TRAP_STACK_UNDERFLOW; return; }
            Value b = POP();
            Value a = POP();
            // 타입 체크 생략 (단순화)
            PUSH(VAL_INT(a.as.i_val + b.as.i_val));
            break;
        }

        case OP_CALL: {
            u16 target_fid = inst.operand;
            Function* target_func = &vm->functions[target_fid];

            // 새 프레임 준비
            vm->fp++;
            if (vm->fp >= MAX_CALL_STACK) { vm->trap = TRAP_CALL_STACK_OVERFLOW; return; }
            Frame* new_frame = &vm->frames[vm->fp];

            // 복귀 주소 저장 (PC는 이미 증가된 상태)
            new_frame->return_fid = vm->pc_fid;
            new_frame->return_ip = vm->pc_ip;

            // 인자 전달 (역순 POP)
            for (int i = target_func->param_count - 1; i >= 0; i--) {
                new_frame->locals[i] = POP();
            }
            
            // 나머지 로컬 초기화
            for (int i = target_func->param_count; i < target_func->local_count; i++) {
                new_frame->locals[i].type = VAL_UNINIT;
            }

            // 점프
            vm->pc_fid = target_fid;
            vm->pc_ip = 0;
            break;
        }

        case OP_RET: {
            Value ret_val = POP();
            
            if (vm->fp == 0) {
                // Main 함수 종료
                vm->running = false;
                PUSH(ret_val); // 최종 결과 스택에 남김
            } else {
                // 복귀
                Frame* curr = &vm->frames[vm->fp];
                vm->pc_fid = curr->return_fid;
                vm->pc_ip = curr->return_ip;
                vm->fp--;
                PUSH(ret_val);
            }
            break;
        }

        default:
            printf("Unknown Opcode: %d\n", inst.opcode);
            vm->running = false;
            break;
    }
}

// ==========================================
// 4. 테스트 드라이버 (시각화 및 실행)
// ==========================================

void print_state(VM* vm, int step_count, Instruction next_inst) {
    // 1. 메타 정보 (FID, IP도 2자리 고정 너비로 확보)
    printf("[Step %02d] FID:%-2d IP:%-2d | ", step_count, vm->pc_fid, vm->pc_ip);
    
    // 2. 명령어 출력 (탭 대신 고정 너비 사용)
    // %-10s : 문자열을 왼쪽 정렬하고 최소 10칸 확보 (PUSH_I16이 8글자이므로 여유있음)
    // %5d   : 숫자를 오른쪽 정렬하고 최소 5칸 확보
    printf("INST: %-10s %5d | ", OP_NAMES[next_inst.opcode], next_inst.operand);

    // 3. 스택 출력
    printf("STACK: [ ");
    for (int i = 0; i < vm->sp; i++) {
        if (vm->stack[i].type == VAL_I16)
            printf("%d ", vm->stack[i].as.i_val);
        else if (vm->stack[i].type == VAL_FUN)
            printf("F%d ", vm->stack[i].as.fun_id);
    }
    printf("]\n");
}

int main() {
    VM vm;
    vm_init(&vm);

    // --- 시나리오 설정 ---
    // Function 1: int add1(int a) { return a + 1; }
    // param: 1, local: 1
    Instruction code_add1[] = {
        {OP_DBG_LINE, 2},
        {OP_LOAD, 0},      // Load a
        {OP_PUSH_I16, 1},  // Push 1
        {OP_ADD, 0},       // Add
        {OP_RET, 0}        // Return result
    };

    vm.functions[1] = (Function){
        .name = "add1",
        .param_count = 1, .local_count = 1,
        .code = code_add1, .code_size = 5
    };

    // Function 2: int main() { return add1(10); }
    // param: 0, local: 0
    Instruction code_main[] = {
        {OP_DBG_LINE, 5},
        {OP_PUSH_I16, 10}, // Arg: 10
        {OP_CALL, 1},      // Call add1
        {OP_HALT, 0}       // Stop (explicit halt)
    };

    vm.functions[2] = (Function){
        .name = "main",
        .param_count = 0, .local_count = 0,
        .code = code_main, .code_size = 4
    };
    
    vm.function_count = 2;

    // --- 실행 시작 (Entry Point: main 함수 ID 2) ---
    printf("=== MiniC89 VM Trace Start ===\n");
    vm.pc_fid = 2; 
    vm.pc_ip = 0;

    int step = 0;
    while (vm.running && vm.trap == TRAP_NONE) {
        // 현재 실행할 명령어 미리 보기 (출력용)
        Instruction current_inst = vm.functions[vm.pc_fid].code[vm.pc_ip];
        
        print_state(&vm, step++, current_inst);
        vm_step(&vm);
    }

    printf("==============================\n");
    if (vm.trap != TRAP_NONE) {
        printf("RUNTIME ERROR: %s\n", TRAP_NAMES[vm.trap]);
    } else {
        Value result = (vm.sp > 0) ? vm.stack[vm.sp - 1] : (Value){0};
        printf("Program Halted Correctly.\n");
        printf("Final Result: %d\n", result.as.i_val);
    }

    return 0;
}
