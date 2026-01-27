#ifndef MINIC89_BUILDER_H
#define MINIC89_BUILDER_H

#include "minic89_vm.h"

// --- 상수 정의 ---
#define MAX_LABELS 32       // 함수 당 최대 레이블 수
#define MAX_PATCHES 64      // 함수 당 점프 수정(Patch) 요청 수

// --- 구조체 정의 ---

// 점프 위치를 나중에 채워넣기 위한 정보
typedef struct {
    u16 instruction_index; // 점프 명령어가 있는 위치 (ip)
    int label_id;          // 목표 레이블 ID
} JumpPatch;

typedef struct {
    VM* vm;                // 대상 VM
    u16 current_fid;       // 현재 작성 중인 함수 ID
    
    // 레이블 관리 (함수 단위로 리셋됨)
    int label_targets[MAX_LABELS]; // label_id -> resolved ip mapping (-1이면 미정)
    JumpPatch patches[MAX_PATCHES];
    int patch_count;
    int label_count;
} Builder;

// --- API 함수 프로토타입 ---

// 1. 초기화
void builder_init(Builder* b, VM* vm);

// 2. 함수 시작/종료
// 반환값: 생성된 함수 ID
u16 builder_begin_func(Builder* b, const char* name, u8 params, u8 locals);
void builder_end_func(Builder* b);

// 3. 명령어 방출 (Emit)
void emit_op(Builder* b, Opcode op);
void emit_u8(Builder* b, Opcode op, u8 operand);
void emit_i16(Builder* b, Opcode op, i16 operand);

// 4. 편의용 래퍼 (자주 쓰는 명령)
void emit_push(Builder* b, i16 val);
void emit_load(Builder* b, u8 slot);
void emit_store(Builder* b, u8 slot);
void emit_call(Builder* b, u16 fid);
void emit_ret(Builder* b);

// 5. 제어 흐름 (레이블)
int builder_new_label(Builder* b);           // 새 레이블 ID 발급
void builder_mark_label(Builder* b, int label_id); // 현재 위치를 레이블로 지정
void emit_jmp_label(Builder* b, Opcode op, int label_id); // 레이블로 점프 (JMP, JZ, JNZ)

#endif // MINIC89_BUILDER_H
