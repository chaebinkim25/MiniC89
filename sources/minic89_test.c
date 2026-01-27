#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// ==========================================
// [Part 1] VM & ISA Definitions
// ==========================================

#define MAX_STACK 1024
#define MAX_CALL_STACK 64
#define MAX_LOCALS 16
#define MAX_FUNCTIONS 16

typedef int16_t  i16;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef enum {
    VAL_UNINIT = 0, VAL_I16, VAL_FUN
} ValType;

typedef struct {
    ValType type;
    union { i16 i_val; u16 fun_id; } as;
} Value;

typedef enum {
    OP_NOP, OP_DBG_LINE,
    OP_PUSH_I16, OP_POP, OP_DUP,
    OP_LOAD, OP_STORE,
    OP_ADD, OP_SUB, OP_NEG, // NEG 추가
    OP_LT, // LT 추가
    OP_JMP, OP_JZ, OP_JNZ,
    OP_CALL, OP_RET, OP_HALT
} Opcode;

const char* OP_NAMES[] = {
    "NOP", "DBG_LINE", "PUSH_I16", "POP", "DUP",
    "LOAD", "STORE", "ADD", "SUB", "NEG",
    "LT", "JMP", "JZ", "JNZ",
    "CALL", "RET", "HALT"
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
    u16 return_fid;
    u16 return_ip;
    Value locals[MAX_LOCALS];
} Frame;

typedef struct {
    Function functions[MAX_FUNCTIONS];
    u16 function_count;
    u16 pc_fid;
    u16 pc_ip;
    Value stack[MAX_STACK];
    int sp;
    Frame frames[MAX_CALL_STACK];
    int fp;
    bool running;
    int trap; // 0: None
} VM;

Value VAL_INT(i16 v) { return (Value){ .type = VAL_I16, .as.i_val = v }; }

// ==========================================
// [Part 2] Builder API Definitions & Impl
// ==========================================

#define MAX_LABELS 32
#define MAX_PATCHES 64

typedef struct {
    u16 instruction_index;
    int label_id;
} JumpPatch;

typedef struct {
    VM* vm;
    u16 current_fid;
    int label_targets[MAX_LABELS];
    JumpPatch patches[MAX_PATCHES];
    int patch_count;
    int label_count;
} Builder;

void builder_init(Builder* b, VM* vm) {
    b->vm = vm;
    b->current_fid = 0;
}

u16 builder_begin_func(Builder* b, const char* name, u8 params, u8 locals) {
    b->vm->function_count++;
    u16 fid = b->vm->function_count;
    b->current_fid = fid;

    Function* f = &b->vm->functions[fid];
    f->name = name;
    f->param_count = params;
    f->local_count = locals;
    f->code_size = 0;
    
    // 단순화를 위해 넉넉히 할당 (실제론 free 필요)
    f->code = (Instruction*)malloc(sizeof(Instruction) * 256);

    b->patch_count = 0;
    b->label_count = 0;
    for(int i=0; i<MAX_LABELS; i++) b->label_targets[i] = -1;

    return fid;
}

void builder_end_func(Builder* b) {
    Function* f = &b->vm->functions[b->current_fid];
    // Back-patching: 레이블 위치 연결
    for (int i = 0; i < b->patch_count; i++) {
        JumpPatch p = b->patches[i];
        int target_ip = b->label_targets[p.label_id];
        if (target_ip == -1) {
            printf("[Build Error] Undefined Label %d in %s\n", p.label_id, f->name);
        } else {
            f->code[p.instruction_index].operand = (i16)target_ip;
        }
    }
}

// Instruction Emitters
void emit_op(Builder* b, Opcode op) {
    Function* f = &b->vm->functions[b->current_fid];
    f->code[f->code_size++] = (Instruction){ (u8)op, 0 };
}
void emit_i16(Builder* b, Opcode op, i16 operand) {
    Function* f = &b->vm->functions[b->current_fid];
    f->code[f->code_size++] = (Instruction){ (u8)op, operand };
}

// Wrappers
void emit_push(Builder* b, i16 val) { emit_i16(b, OP_PUSH_I16, val); }
void emit_load(Builder* b, u8 slot) { emit_i16(b, OP_LOAD, slot); }
void emit_store(Builder* b, u8 slot){ emit_i16(b, OP_STORE, slot); }
void emit_call(Builder* b, u16 fid) { emit_i16(b, OP_CALL, fid); }
void emit_ret(Builder* b)           { emit_op(b, OP_RET); }

// Label Control
int builder_new_label(Builder* b) { return b->label_count++; }

void builder_mark_label(Builder* b, int label_id) {
    Function* f = &b->vm->functions[b->current_fid];
    b->label_targets[label_id] = f->code_size;
}

void emit_jmp_label(Builder* b, Opcode op, int label_id) {
    Function* f = &b->vm->functions[b->current_fid];
    b->patches[b->patch_count++] = (JumpPatch){ f->code_size, label_id };
    emit_i16(b, op, 0); // Operand는 나중에 채워짐
}

// ==========================================
// [Part 3] VM Implementation (Minimal)
// ==========================================

void vm_init(VM* vm) {
    memset(vm, 0, sizeof(VM));
    vm->running = true;
    vm->fp = 0;
}

void vm_step(VM* vm) {
    if (!vm->running || vm->trap) return;

    Function* func = &vm->functions[vm->pc_fid];
    Instruction inst = func->code[vm->pc_ip++];

    switch (inst.opcode) {
        case OP_NOP: break;
        case OP_HALT: vm->running = false; break;
        
        case OP_PUSH_I16: vm->stack[vm->sp++] = VAL_INT(inst.operand); break;
        case OP_POP: vm->sp--; break;
        
        case OP_LOAD: 
            vm->stack[vm->sp++] = vm->frames[vm->fp].locals[inst.operand]; 
            break;
            
        case OP_STORE: // 대입식: 값 복사만 하고 스택 pop 안 함
            vm->frames[vm->fp].locals[inst.operand] = vm->stack[vm->sp-1]; 
            break;

        case OP_ADD: {
            i16 b = vm->stack[--vm->sp].as.i_val;
            i16 a = vm->stack[--vm->sp].as.i_val;
            vm->stack[vm->sp++] = VAL_INT(a + b);
            break;
        }
        
        case OP_NEG: {
            i16 a = vm->stack[--vm->sp].as.i_val;
            vm->stack[vm->sp++] = VAL_INT(-a);
            break;
        }

        case OP_LT: {
            i16 b = vm->stack[--vm->sp].as.i_val;
            i16 a = vm->stack[--vm->sp].as.i_val;
            vm->stack[vm->sp++] = VAL_INT(a < b ? 1 : 0);
            break;
        }

        case OP_JZ: {
            i16 cond = vm->stack[--vm->sp].as.i_val;
            if (cond == 0) vm->pc_ip = inst.operand;
            break;
        }
        
        case OP_JMP: vm->pc_ip = inst.operand; break;

        case OP_CALL: {
            u16 target_fid = inst.operand;
            Function* target_func = &vm->functions[target_fid];
            vm->fp++;
            Frame* f = &vm->frames[vm->fp];
            f->return_fid = vm->pc_fid;
            f->return_ip = vm->pc_ip;
            // 인자 전달 (역순)
            for(int i=target_func->param_count-1; i>=0; i--) {
                f->locals[i] = vm->stack[--vm->sp];
            }
            vm->pc_fid = target_fid;
            vm->pc_ip = 0;
            break;
        }

        case OP_RET: {
            Value ret_val = vm->stack[--vm->sp];
            if (vm->fp == 0) {
                vm->running = false; // Main return
                vm->stack[vm->sp++] = ret_val;
            } else {
                Frame* f = &vm->frames[vm->fp];
                vm->pc_fid = f->return_fid;
                vm->pc_ip = f->return_ip;
                vm->fp--;
                vm->stack[vm->sp++] = ret_val;
            }
            break;
        }
    }
}

void print_state(VM* vm, int step, Instruction inst) {
    printf("[Step %02d] FID:%-2d IP:%-2d | INST: %-10s %5d | STACK: [ ", 
           step, vm->pc_fid, vm->pc_ip, OP_NAMES[inst.opcode], inst.operand);
    for (int i=0; i<vm->sp; i++) printf("%d ", vm->stack[i].as.i_val);
    printf("]\n");
}

// ==========================================
// [Part 4] Main & Test Logic
// ==========================================

int main() {
    VM vm;
    Builder b;

    vm_init(&vm);
    builder_init(&b, &vm);

    printf("=== 1. Compiling Functions using Builder ===\n");

    // -------------------------------------------------
    // Function 1: int abs(int x)
    // -------------------------------------------------
    // if (x < 0) return -x;
    // return x;
    u16 fid_abs = builder_begin_func(&b, "abs", 1, 1);
    
    int L_else = builder_new_label(&b);

    emit_load(&b, 0);       // Load x
    emit_push(&b, 0);       // Push 0
    emit_op(&b, OP_LT);     // x < 0 ?
    emit_jmp_label(&b, OP_JZ, L_else); // False -> goto L_else

    // Then Block (x < 0)
    emit_load(&b, 0);
    emit_op(&b, OP_NEG);    // -x
    emit_ret(&b);

    // Else Block
    builder_mark_label(&b, L_else); // <--- Label Here
    emit_load(&b, 0);       // Load x
    emit_ret(&b);

    builder_end_func(&b);
    printf("Compiled 'abs' (FID: %d)\n", fid_abs);


    // -------------------------------------------------
    // Function 2: int main()
    // -------------------------------------------------
    // return abs(-42);
    u16 fid_main = builder_begin_func(&b, "main", 0, 0);
    
    emit_push(&b, -42);     // Arg: -42
    emit_call(&b, fid_abs); // Call abs
    emit_op(&b, OP_HALT);   // Stop

    builder_end_func(&b);
    printf("Compiled 'main' (FID: %d)\n", fid_main);


    // -------------------------------------------------
    // Execution
    // -------------------------------------------------
    printf("\n=== 2. Running VM ===\n");
    
    vm.pc_fid = fid_main;
    vm.pc_ip = 0;

    int step = 0;
    while(vm.running && !vm.trap) {
        Instruction curr = vm.functions[vm.pc_fid].code[vm.pc_ip];
        print_state(&vm, step++, curr);
        vm_step(&vm);
    }

    if (vm.trap) {
        printf("Runtime Trap: %d\n", vm.trap);
    } else {
        Value res = vm.stack[vm.sp - 1];
        printf("==============================\n");
        printf("Program Finished.\n");
        printf("Result: %d (Expected: 42)\n", res.as.i_val);
    }

    // Cleanup (메모리 해제는 생략함)
    return 0;
}
