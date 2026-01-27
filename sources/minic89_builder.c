#include <stdio.h>
#include <string.h>
#include "minic89_builder.h"

// --- 내부 헬퍼 ---
static Function* curr_func(Builder* b) {
    return &b->vm->functions[b->current_fid];
}

static void ensure_capacity(Builder* b) {
    // 실제 구현 시에는 동적 할당 체크를 하거나
    // VM의 고정 크기(MAX_CODE_SIZE 등)를 넘지 않는지 확인해야 함
    // 여기서는 생략
}

// --- 구현 ---

void builder_init(Builder* b, VM* vm) {
    b->vm = vm;
    b->current_fid = 0;
    // VM 초기화는 외부에서 이미 되었다고 가정
}

u16 builder_begin_func(Builder* b, const char* name, u8 params, u8 locals) {
    b->vm->function_count++;
    u16 fid = b->vm->function_count;
    b->current_fid = fid;

    Function* f = &b->vm->functions[fid];
    f->name = name; // 주의: 문자열 수명 관리는 호출자 책임 (리터럴 권장)
    f->param_count = params;
    f->local_count = locals;
    f->code_size = 0;
    
    // 레이블/패치 상태 초기화
    b->patch_count = 0;
    b->label_count = 0;
    for(int i=0; i<MAX_LABELS; i++) b->label_targets[i] = -1; // -1: 아직 위치 모름

    // 코드 배열 메모리 할당 (간단히 정적 배열 포인터 연결 또는 malloc)
    // 교육용 단순화를 위해 VM 내부에 큰 정적 배열 풀이 있다고 가정하거나,
    // 여기서는 malloc을 사용하여 힙에 할당
    f->code = (Instruction*)malloc(sizeof(Instruction) * 1024); // 임시 1024개 제한

    return fid;
}

void builder_end_func(Builder* b) {
    Function* f = curr_func(b);
    
    // Back-patching: 미결 점프들의 주소를 실제 레이블 위치로 수정
    for (int i = 0; i < b->patch_count; i++) {
        JumpPatch p = b->patches[i];
        int target_ip = b->label_targets[p.label_id];
        
        if (target_ip == -1) {
            printf("Error: Label %d used but not defined in function %s\n", 
                   p.label_id, f->name);
            // 실제 컴파일러라면 여기서 에러 처리
        } else {
            // 해당 명령어의 operand를 실제 target_ip로 덮어쓰기
            f->code[p.instruction_index].operand = (i16)target_ip;
        }
    }
}

// 기본 명령어 방출
void emit_op(Builder* b, Opcode op) {
    Function* f = curr_func(b);
    f->code[f->code_size++] = (Instruction){ .opcode = (u8)op, .operand = 0 };
}

void emit_u8(Builder* b, Opcode op, u8 operand) {
    Function* f = curr_func(b);
    f->code[f->code_size++] = (Instruction){ .opcode = (u8)op, .operand = (i16)operand };
}

void emit_i16(Builder* b, Opcode op, i16 operand) {
    Function* f = curr_func(b);
    f->code[f->code_size++] = (Instruction){ .opcode = (u8)op, .operand = operand };
}

// 편의 래퍼
void emit_push(Builder* b, i16 val) { emit_i16(b, OP_PUSH_I16, val); }
void emit_load(Builder* b, u8 slot) { emit_u8(b, OP_LOAD, slot); }
void emit_store(Builder* b, u8 slot){ emit_u8(b, OP_STORE, slot); }
void emit_call(Builder* b, u16 fid) { emit_u8(b, OP_CALL, (u8)fid); } // fid가 u16이면 emit_i16 써야함. 수정 필요
void emit_ret(Builder* b)           { emit_op(b, OP_RET); }

// 제어 흐름 (레이블)
int builder_new_label(Builder* b) {
    return b->label_count++;
}

void builder_mark_label(Builder* b, int label_id) {
    Function* f = curr_func(b);
    b->label_targets[label_id] = f->code_size; // 현재 IP를 레이블 타겟으로 등록
}

void emit_jmp_label(Builder* b, Opcode op, int label_id) {
    Function* f = curr_func(b);
    
    // 패치 리스트에 등록
    b->patches[b->patch_count++] = (JumpPatch){
        .instruction_index = f->code_size, // 현재 명령어 위치
        .label_id = label_id
    };

    // 일단 operand 0으로 방출 (나중에 builder_end_func에서 수정됨)
    emit_i16(b, op, 0); 
}
