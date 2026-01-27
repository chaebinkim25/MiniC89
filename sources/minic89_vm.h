#ifndef MINIC89_VM_H   
#define MINIC89_VM_H  

#include <stdint.h>
#include <stdbool.h>

// --- 상수 및 설정 ---
#define MAX_STACK 1024
#define MAX_CALL_STACK 64
#define MAX_LOCALS 256
#define MAX_FUNCTIONS 256

// --- 타입 정의 ---
typedef int16_t  i16;
typedef uint16_t u16;
typedef uint8_t  u8;

// 값의 타입 (런타임 타입 체크용)
typedef enum {
    VAL_UNINIT = 0, // 초기화되지 않음 (UB 감지용)
    VAL_I16,        // 정수
    VAL_FUN         // 함수 참조
} ValType;

// VM에서 다루는 값 (Tagged Union)
typedef struct {
    ValType type;
    union {
        i16 i_val;      // I16 값
        u16 fun_id;     // Function ID
    } as;
} Value;

// 명령어 구조
typedef enum {
    OP_NOP, OP_DBG_LINE,
    OP_PUSH_I16, OP_PUSH_FUN, OP_PUSH_NULL, OP_POP, OP_DUP,
    OP_LOAD, OP_STORE,
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_NEG,
    OP_EQ, OP_NE, OP_LT, OP_LE, OP_GT, OP_GE, OP_LNOT,
    OP_JMP, OP_JZ, OP_JNZ,
    OP_CALL, OP_CALL_IND, OP_RET,
    OP_HALT // 가상 명령어 (종료용)
} Opcode;

typedef struct {
    uint8_t opcode;
    i16 operand; // 상수, 오프셋, 슬롯 인덱스 등
} Instruction;

// 함수 메타데이터
typedef struct {
    const char* name;
    u8 param_count;
    u8 local_count;
    Instruction* code;
    u16 code_size;
} Function;

// 호출 스택 프레임
typedef struct {
    u16 func_id;          // 현재 함수 ID
    u16 return_ip;        // 복귀할 명령어 위치
    u16 prev_fp;          // 이전 프레임 포인터 (필요 시)
    Value locals[MAX_LOCALS]; // 로컬 변수 저장소
} Frame;

// 트랩(오류) 종류
typedef enum {
    TRAP_NONE = 0,
    TRAP_STACK_OVERFLOW, TRAP_STACK_UNDERFLOW,
    TRAP_CALL_STACK_OVERFLOW, TRAP_CALL_STACK_UNDERFLOW,
    TRAP_INT_OVERFLOW, TRAP_DIV_ZERO,
    TRAP_BAD_FUNID, TRAP_BAD_LOCAL, TRAP_BAD_JUMP,
    TRAP_UNINIT_READ, TRAP_TYPE_MISMATCH, TRAP_BAD_SIGNATURE
} TrapReason;

// VM 상태
typedef struct {
    // Code Area
    Function functions[MAX_FUNCTIONS];
    u16 function_count;

    // Registers
    u16 pc_fid;  // 현재 함수 ID
    u16 pc_ip;   // 현재 명령어 인덱스
    
    // Operand Stack
    Value stack[MAX_STACK];
    int sp;      // Stack Pointer (points to next free slot)

    // Call Stack
    Frame frames[MAX_CALL_STACK];
    int fp;      // Frame Pointer (points to current frame)

    // State
    bool running;
    TrapReason trap;
    u16 current_source_line; // 디버깅용
} VM;

#endif
